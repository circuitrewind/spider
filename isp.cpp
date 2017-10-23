#ifdef TEENSYDUINO



// ArduinoISP
// Copyright (c) 2008-2011 Randall Bohn
// If you require a license, see
//     http://www.opensource.org/licenses/bsd-license.php
//
// This sketch turns the Arduino into a AVRISP
// using the following arduino pins:
//
// Pin 10 is used to reset the target microcontroller.
//
// By default, the hardware SPI pins MISO, MOSI and SCK pins are used
// to communicate with the target. On all Arduinos, these pins can be found
// on the ICSP/SPI header:
//
//               MISO °. . 5V (!) Avoid this pin on Due, Zero...
//               SCK   . . MOSI
//                     . . GND
//
// On some Arduinos (Uno,...), pins MOSI, MISO and SCK are the same pins
// as digital pin 11, 12 and 13, respectively. That is why many tutorials
// instruct you to hook up the target to these pins. If you find this wiring
// more practical, have a define USE_OLD_STYLE_WIRING. This will work even
// even when not using an Uno. (On an Uno this is not needed).
//
// Alternatively you can use any other digital pin by configuring software ('BitBanged')
// SPI and having appropriate defines for PIN_MOSI, PIN_MISO and PIN_SCK.
//
// IMPORTANT: When using an Arduino that is not 5V tolerant (Due, Zero, ...)
// as the programmer, make sure to not expose any of the programmer's pins to 5V.
// A simple way to accomplish this is to power the complete system (programmer
// and target) at 3V3.
//
// Put an LED (with resistor) on the following pins:
// 9: Heartbeat   - shows the programmer is running
// 8: Error       - Lights up if something goes wrong (use red if that makes sense)
// 7: Programming - In communication with the slave
//


#include "defines.h"
#include "isp.h"



// Configure SPI clock (in Hz).
// E.g. for an attiny @128 kHz: the datasheet states that both the high
// and low spi clock pulse must be > 2 cpu cycles, so take 3 cycles i.e.
// divide target f_cpu by 6:
//     #define SPI_CLOCK            (128000/6)
//
// A clock slow enough for an attiny85 @ 1MHz, is a reasonable default:

#define SPI_CLOCK 		(1000000/6)



// Configure which pins to use:

// The standard pin configuration.


#define HWVER 2
#define SWMAJ 1
#define SWMIN 18

// STK Definitions
#define STK_OK      0x10
#define STK_FAILED  0x11
#define STK_UNKNOWN 0x12
#define STK_INSYNC  0x14
#define STK_NOSYNC  0x15
#define CRC_EOP     0x20 //ok it is a space...

#define EECHUNK (32)

#define beget16(addr) (*addr * 256 + *(addr+1) )



void isp::frame(pixelArray **strip, WII **wii) {
	for (int i=0; i<PLAYERS; i++) {
		if (!wii[i]->wiimoteConnected) continue;

		if (wii[i]->getButtonClick(UP)  ||  wii[i]->getButtonClick(DOWN)) {
			if (!pmode) side = !side;
		}
	}

	strip[0]->clear();
	strip[0]->string(
		side ? "85R" : "85L",
		1,
		GRID_HEIGHT-6,
		side ? color_t::yellow() : color_t::teal()
	);
}



void isp::loop(pixelArray **strip, WII **wii) {
	if (!Serial.available()) return;

	uint8_t ch = getch();
	switch (ch) {

		case '0': // signon
			error = 0;
			empty_reply();
			break;


		case '1':
			if (getch() == CRC_EOP) {
				Serial.print((char) STK_INSYNC);
				Serial.print("AVR ISP");
				Serial.print((char) STK_OK);
			} else {
				error++;
				Serial.print((char) STK_NOSYNC);
			}
			break;


		case 'A':
			get_version(getch());
			break;


		case 'B':
			fill(20);
			set_parameters();
			empty_reply();
			break;


		case 'E': // extended parameters - ignore for now
			fill(5);
			empty_reply();
			break;


		case 'P':
			if (!pmode) start_pmode();
			empty_reply();
			break;


		case 'U': // set address (word)
			here = getch();
			here += 256 * getch();
			empty_reply();
			break;


		case 0x60: //STK_PROG_FLASH
			getch(); // low addr
			getch(); // high addr
			empty_reply();
			break;


		case 0x61: //STK_PROG_DATA
			getch(); // data
			empty_reply();
			break;


		case 0x64: //STK_PROG_PAGE
			program_page();
			break;


		case 0x74: //STK_READ_PAGE 't'
			read_page();
			break;


		case 'V': //0x56
			universal();
			break;


		case 'Q': //0x51
			error = 0;
			end_pmode();
			empty_reply();
			break;


		case 0x75: //STK_READ_SIGN 'u'
			read_signature();
			break;


		// expecting a command, not CRC_EOP
		// this is how we can get back in sync
		case CRC_EOP:
			error++;
			Serial.print((char) STK_NOSYNC);
			break;


		// anything else we will return STK_UNKNOWN
		default:
			error++;
			if (CRC_EOP == getch()) {
				Serial.print((char)STK_UNKNOWN);
			} else {
				Serial.print((char)STK_NOSYNC);
			}
	}
}




void isp::reset_target(bool reset) {
	digitalWrite(
		reset_pin(),
		((reset && reset_high) || (!reset && !reset_high))
			? HIGH
			: LOW
	);
}




uint8_t isp::getch() {
	while (!Serial.available());
	return Serial.read();
}




void isp::fill(int n) {
	for (int x = 0; x < n; x++) {
		buff[x] = getch();
	}
}




uint8_t isp::spi_transaction(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	SPI.transfer(a);
	SPI.transfer(b);
	SPI.transfer(c);
	return SPI.transfer(d);
}




void isp::empty_reply() {
	if (CRC_EOP == getch()) {
		Serial.print((char)STK_INSYNC);
		Serial.print((char)STK_OK);
	} else {
		error++;
		Serial.print((char)STK_NOSYNC);
	}
}




void isp::breply(uint8_t b) {
	if (CRC_EOP == getch()) {
		Serial.print((char)STK_INSYNC);
		Serial.print((char)b);
		Serial.print((char)STK_OK);
	} else {
		error++;
		Serial.print((char)STK_NOSYNC);
	}
}




void isp::get_version(uint8_t c) {
	switch (c) {
		case 0x80:
			breply(HWVER);
			break;
		case 0x81:
			breply(SWMAJ);
			break;
		case 0x82:
			breply(SWMIN);
			break;
		case 0x93:
			breply('S'); // Serial programmer
			break;
		default:
			breply(0);
	}
}




void isp::set_parameters() {
	// call this after reading paramter packet into buff[]
	param.devicecode = buff[0];
	param.revision   = buff[1];
	param.progtype   = buff[2];
	param.parmode    = buff[3];
	param.polling    = buff[4];
	param.selftimed  = buff[5];
	param.lockbytes  = buff[6];
	param.fusebytes  = buff[7];
	param.flashpoll  = buff[8];
	// ignore buff[9] (= buff[8])
	// following are 16 bits (big endian)
	param.eeprompoll = beget16(&buff[10]);
	param.pagesize   = beget16(&buff[12]);
	param.eepromsize = beget16(&buff[14]);

	// 32 bits flashsize (big endian)
	param.flashsize = buff[16] * 0x01000000
										+ buff[17] * 0x00010000
										+ buff[18] * 0x00000100
										+ buff[19];

	// avr devices have active low reset, at89sx are active high
	reset_high = (param.devicecode >= 0xe0);
}




void isp::start_pmode() {

	// Reset target before driving PIN_SCK or PIN_MOSI

	// SPI.begin() will configure SS as output,
	// so SPI master mode is selected.
	// We have defined RESET as pin 10,
	// which for many arduino's is not the SS pin.
	// So we have to configure RESET as output here,
	// (reset_target() first sets the correct level)
	reset_target(true);
	pinMode(reset_pin(), OUTPUT);
	SPI.begin();
	SPI.beginTransaction(SPI_CLOCK);

	// See avr datasheets, chapter "Serial_PRG Programming Algorithm":

	// Pulse RESET after PIN_SCK is low:
	digitalWrite(PIN_SCK, LOW);
	delay(20); // discharge PIN_SCK, value arbitrally chosen
	reset_target(false);
	// Pulse must be minimum 2 target CPU clock cycles
	// so 100 usec is ok for CPU speeds above 20KHz
	delayMicroseconds(100);
	reset_target(true);

	// Send the enable programming command:
	delay(50); // datasheet: must be > 20 msec
	spi_transaction(0xAC, 0x53, 0x00, 0x00);
	pmode = 1;
}




void isp::end_pmode() {
	SPI.end();
	// We're about to take the target out of reset
	// so configure SPI pins as input
	pinMode(PIN_MOSI, INPUT);
	pinMode(PIN_SCK, INPUT);
	reset_target(false);
	pinMode(reset_pin(), INPUT);
	pmode = 0;
}




void isp::universal() {
	uint8_t ch;

	fill(4);
	ch = spi_transaction(buff[0], buff[1], buff[2], buff[3]);
	breply(ch);
}




void isp::flash(uint8_t hilo, unsigned int addr, uint8_t data) {
	spi_transaction(0x40 + 8 * hilo,
									addr >> 8 & 0xFF,
									addr & 0xFF,
									data);
}




void isp::commit(unsigned int addr) {
	spi_transaction(0x4C, (addr >> 8) & 0xFF, addr & 0xFF, 0);
}




unsigned int isp::current_page() {
	if (param.pagesize == 32) {
		return here & 0xFFFFFFF0;
	}
	if (param.pagesize == 64) {
		return here & 0xFFFFFFE0;
	}
	if (param.pagesize == 128) {
		return here & 0xFFFFFFC0;
	}
	if (param.pagesize == 256) {
		return here & 0xFFFFFF80;
	}
	return here;
}




void isp::write_flash(int length) {
	fill(length);
	if (CRC_EOP == getch()) {
		Serial.print((char) STK_INSYNC);
		Serial.print((char) write_flash_pages(length));
	} else {
		error++;
		Serial.print((char) STK_NOSYNC);
	}
}




uint8_t isp::write_flash_pages(int length) {
	int x = 0;
	unsigned int page = current_page();
	while (x < length) {
		if (page != current_page()) {
			commit(page);
			page = current_page();
		}
		flash(LOW, here, buff[x++]);
		flash(HIGH, here, buff[x++]);
		here++;
	}

	commit(page);

	return STK_OK;
}




uint8_t isp::write_eeprom(unsigned int length) {
	// here is a word address, get the byte address
	unsigned int start = here * 2;
	unsigned int remaining = length;
	if (length > param.eepromsize) {
		error++;
		return STK_FAILED;
	}
	while (remaining > EECHUNK) {
		write_eeprom_chunk(start, EECHUNK);
		start += EECHUNK;
		remaining -= EECHUNK;
	}
	write_eeprom_chunk(start, remaining);
	return STK_OK;
}




// write (length) bytes, (start) is a byte address
uint8_t isp::write_eeprom_chunk(unsigned int start, unsigned int length) {
	// this writes byte-by-byte,
	// page writing may be faster (4 bytes at a time)
	fill(length);

	for (unsigned int x = 0; x < length; x++) {
		unsigned int addr = start + x;
		spi_transaction(0xC0, (addr >> 8) & 0xFF, addr & 0xFF, buff[x]);
		delay(45);
	}

	return STK_OK;
}




void isp::program_page() {
	char result = (char) STK_FAILED;
	unsigned int length = 256 * getch();
	length += getch();
	char memtype = getch();

	// flash memory @here, (length) bytes
	if (memtype == 'F') {
		write_flash(length);
		return;
	}

	if (memtype == 'E') {
		result = (char)write_eeprom(length);
		if (CRC_EOP == getch()) {
			Serial.print((char) STK_INSYNC);
			Serial.print(result);
		} else {
			error++;
			Serial.print((char) STK_NOSYNC);
		}
		return;
	}

	Serial.print((char)STK_FAILED);
	return;
}




uint8_t isp::flash_read(uint8_t hilo, unsigned int addr) {
	return spi_transaction(
		0x20 + hilo * 8,
		(addr >> 8) & 0xFF,
		addr & 0xFF,
		0
	);
}




char isp::flash_read_page(int length) {
	for (int x = 0; x < length; x += 2) {
		uint8_t low = flash_read(LOW, here);
		Serial.print((char) low);
		uint8_t high = flash_read(HIGH, here);
		Serial.print((char) high);
		here++;
	}
	return STK_OK;
}




char isp::eeprom_read_page(int length) {
	// here again we have a word address
	int start = here * 2;
	for (int x = 0; x < length; x++) {
		int addr = start + x;
		uint8_t ee = spi_transaction(0xA0, (addr >> 8) & 0xFF, addr & 0xFF, 0xFF);
		Serial.print((char) ee);
	}
	return STK_OK;
}




void isp::read_page() {
	char result = (char)STK_FAILED;
	int length = 256 * getch();
	length += getch();
	char memtype = getch();
	if (CRC_EOP != getch()) {
		error++;
		Serial.print((char) STK_NOSYNC);
		return;
	}
	Serial.print((char) STK_INSYNC);
	if (memtype == 'F') result = flash_read_page(length);
	if (memtype == 'E') result = eeprom_read_page(length);
	Serial.print(result);
}




void isp::read_signature() {
	if (CRC_EOP != getch()) {
		error++;
		Serial.print((char) STK_NOSYNC);
		return;
	}
	Serial.print((char) STK_INSYNC);
	uint8_t high = spi_transaction(0x30, 0x00, 0x00, 0x00);
	Serial.print((char) high);
	uint8_t middle = spi_transaction(0x30, 0x00, 0x01, 0x00);
	Serial.print((char) middle);
	uint8_t low = spi_transaction(0x30, 0x00, 0x02, 0x00);
	Serial.print((char) low);
	Serial.print((char) STK_OK);
}




#endif //TEENSYDUINO
