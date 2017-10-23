#ifdef __AVR__




////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////
#include "spider.h"
#include "coms.h"




////////////////////////////////////////////////////////////////////////////////
// MAIN CONFIGURATION AND DEFAULTS
////////////////////////////////////////////////////////////////////////////////
#define				TOTAL		  50
#define				BRIGHT		  0xff
uint16_t			offset		= 0;
volatile uint8_t	pause		= 20;
volatile uint8_t	mode		= 0;
volatile uint8_t	direction	= 0;




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
	for(uint16_t i=0; i<strip.total(); i++) {
		strip.pixel(
			color_t::hue(((i*256*3) / strip.total()) + offset)
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

	for (uint16_t i=0; i<TOTAL; i++) {
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
	for (uint16_t i=0; i<TOTAL; i++) {
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




#endif //__AVR__
