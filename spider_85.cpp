#if defined ARDUINO_attiny || defined ARDUINO_AVR_DIGISPARK




////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////
#include "spider.h"
#include "coms.h"
#include "progmem.h"





////////////////////////////////////////////////////////////////////////////////
// MAIN CONFIGURATION AND DEFAULTS
////////////////////////////////////////////////////////////////////////////////
#define				TOTAL		  10
#define				BRIGHT		  0xff
uint16_t			offset		= 0;
volatile uint8_t	pause		= 20;
volatile uint8_t	mode		= 0;
volatile uint8_t	direction	= 0;
volatile color_t	color		= color_t::white();




////////////////////////////////////////////////////////////////////////////////
// LIST OF COLORS
////////////////////////////////////////////////////////////////////////////////
CONST color_t color_table[] = {
	color_t::white(),
	color_t::red(),
	color_t::yellow(),
	color_t::lime(),
	color_t::aqua(),
	color_t::blue(),
	color_t::fuchsia(),
	color_t::orange(),
	color_t::gray(),
	color_t::silver(),
	color_t::maroon(),
	color_t::olive(),
	color_t::green(),
	color_t::teal(),
	color_t::navy(),
	color_t::purple(),
	color_t::black(),
};




////////////////////////////////////////////////////////////////////////////////
// MAIN OBJECTS
////////////////////////////////////////////////////////////////////////////////
ws2812b	strip(4, TOTAL);
coms	spi(0, 1, 2, 3);




////////////////////////////////////////////////////////////////////////////////
// INTERRUPT HANDLER
////////////////////////////////////////////////////////////////////////////////
ISR(PCINT0_vect) {
	uint16_b data = spi.process();
	switch (data.byte_1) {
		case 0x01:	mode		=	data.byte_0;	break;
		case 0x02:	pause		=	data.byte_0;	break;
		case 0x03:	direction	= !!data.byte_0;	break;
		case 0x04:	offset		=	data.byte_0;	break;

		case 0x05:
			color = PROGMEM_getAnything(&color_table[data.byte_0 & 0x0F]);
		break;
	}
}




////////////////////////////////////////////////////////////////////////////////
// MAIN SETUP ROUTINE
////////////////////////////////////////////////////////////////////////////////
void setup_avr() {
	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
	strip.clear();
	spi.enable();
}




////////////////////////////////////////////////////////////////////////////////
// rainbow equally distributed throughout
////////////////////////////////////////////////////////////////////////////////
void rainbowCycle() {
	uint16_t segments = (256*3) / strip.total();
	for(uint16_t i=0; i<strip.total(); i++) {
		strip.pixel(
			color_t::hue((i * segments) + offset)
		);
	}
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
void wave(uint8_t r, uint8_t g, uint8_t b) {
	r = r ? 0xff : 0x00;
	g = g ? 0xff : 0x00;
	b = b ? 0xff : 0x00;

	for (uint16_t i=0; i<strip.total(); i++) {
		switch ((i+offset) & 0x000F) {
			case 0x00:	strip.pixel((BRIGHT>>7)&r, (BRIGHT>>7)&g, (BRIGHT>>7)&b);	break;
			case 0x01:	strip.pixel((BRIGHT>>6)&r, (BRIGHT>>6)&g, (BRIGHT>>6)&b);	break;
			case 0x02:	strip.pixel((BRIGHT>>5)&r, (BRIGHT>>5)&g, (BRIGHT>>5)&b);	break;
			case 0x03:	strip.pixel((BRIGHT>>4)&r, (BRIGHT>>4)&g, (BRIGHT>>4)&b);	break;

			case 0x04:	strip.pixel((BRIGHT>>3)&r, (BRIGHT>>3)&g, (BRIGHT>>3)&b);	break;
			case 0x05:	strip.pixel((BRIGHT>>2)&r, (BRIGHT>>2)&g, (BRIGHT>>2)&b);	break;
			case 0x06:	strip.pixel((BRIGHT>>1)&r, (BRIGHT>>1)&g, (BRIGHT>>1)&b);	break;
			case 0x07:	strip.pixel((BRIGHT>>0)&r, (BRIGHT>>0)&g, (BRIGHT>>0)&b);	break;

			case 0x08:	strip.pixel((BRIGHT>>1)&r, (BRIGHT>>1)&g, (BRIGHT>>1)&b);	break;
			case 0x09:	strip.pixel((BRIGHT>>2)&r, (BRIGHT>>2)&g, (BRIGHT>>2)&b);	break;
			case 0x0A:	strip.pixel((BRIGHT>>3)&r, (BRIGHT>>3)&g, (BRIGHT>>3)&b);	break;
			case 0x0B:	strip.pixel((BRIGHT>>4)&r, (BRIGHT>>4)&g, (BRIGHT>>4)&b);	break;

			case 0x0C:	strip.pixel((BRIGHT>>5)&r, (BRIGHT>>5)&g, (BRIGHT>>5)&b);	break;
			case 0x0D:	strip.pixel((BRIGHT>>6)&r, (BRIGHT>>6)&g, (BRIGHT>>6)&b);	break;
			case 0x0E:	strip.pixel((BRIGHT>>7)&r, (BRIGHT>>7)&g, (BRIGHT>>7)&b);	break;
			case 0x0F:	strip.pixel(0, 0, 0); break;
		}
	}
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
void rgbwcmyk() {
	for (uint16_t i=0; i<strip.total(); i++) {
		switch ((i+offset) & 0x0007) {
			case 0: strip.pixel(BRIGHT, 0, 0); break;
			case 1: strip.pixel(0, BRIGHT, 0); break;
			case 2: strip.pixel(0, 0, BRIGHT); break;
			case 3: strip.pixel(BRIGHT>>1, BRIGHT>>1, BRIGHT>>1); break;

			case 4: strip.pixel(0, BRIGHT, BRIGHT); break;
			case 5: strip.pixel(BRIGHT, 0, BRIGHT); break;
			case 6: strip.pixel(BRIGHT, BRIGHT, 0); break;
			case 7: strip.pixel(0, 0, 0); break;
		}
	}
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
void loop_avr() {
	direction ? offset++ : offset--;

	strip.begin();

	switch (mode) {
		case 0x00:	strip.clear();	break;
		case 0x01:	rgbwcmyk();		break;
		case 0x02:	rainbowCycle();	break;

		case 0x10:	wave(1, 0, 0);	break;
		case 0x11:	wave(0, 1, 0);	break;
		case 0x12:	wave(0, 0, 1);	break;
		case 0x13:	wave(0, 1, 1);	break;
		case 0x14:	wave(1, 0, 1);	break;
		case 0x15:	wave(1, 1, 0);	break;
		case 0x16:	wave(1, 1, 1);	break;
	}

	strip.end();
	delay(pause);
}




#endif //ARDUINO_attiny || ARDUINO_AVR_DIGISPARK
