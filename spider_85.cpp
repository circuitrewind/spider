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
volatile uint8_t	mode		= 3;
volatile uint8_t	direction	= 0;
volatile color_t	color		= color_t::blue();




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
#ifdef ARDUINO_AVR_DIGISPARK
ws2812b	strip(2, TOTAL);
coms	spi(0, 1, 4, 3);
#else
ws2812b	strip(4, TOTAL);
coms	spi(0, 1, 2, 3);
#endif




////////////////////////////////////////////////////////////////////////////////
// INTERRUPT HANDLER
////////////////////////////////////////////////////////////////////////////////
ISR(PCINT0_vect) {
	uint32_b data = spi.process();

	uint8_t xor_0 = data.byte_1 ^ data.byte_2 ^ data.byte_3 ^ 0b10101010;
	if (xor_0 != data.byte_0) return;

	switch (data.byte_1) {
		case 0x01:	mode		=	data.word_1;	break;
		case 0x02:	pause		=	data.word_1;	break;
		case 0x03:	direction	= !!data.word_1;	break;
		case 0x04:	offset		=	data.word_1;	break;

		case 0x05:
			color = PROGMEM_getAnything(&color_table[data.word_1 & 0x0F]);
		break;

		case 0x06:
			color = color_t(data.word_1);
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
void chase() {
	color_t cx = (color_t) color;

	uint16_t total = strip.total() << 2;
	color_t cl;

	for(uint16_t i=0; i<total; i+=4) {
		cl = (color_t) (uint32_t) color;
		switch ((i+offset) & 0x1f) {
			case 0x00:
			case 0x0c:
				strip.pixel(cl.right(6));
			break;

			case 0x01:
			case 0x0b:
				strip.pixel(cl.right(5));
			break;

			case 0x02:
			case 0x0a:
				strip.pixel(cl.right(4));
			break;

			case 0x03:
			case 0x09:
				strip.pixel(cl.right(3));
			break;

			case 0x04:
			case 0x08:
				strip.pixel(cl.right(2));
			break;

			case 0x05:
			case 0x07:
				strip.pixel(cl.right(1));
			break;

			case 0x06:
				strip.pixel(cl);
			break;

			default:
				strip.pixel(color_t::black());
		}
	}


/*

	uint16_t segments = (256*3) / strip.total();
	for(uint16_t i=0; i<strip.total(); i++) {
		strip.pixel(
			color_t::hue((i * segments) + offset)
		);
	}

	static color_t hue(uint16_t hue) {
		uint8_t step = hue & 0xff;

		switch ((hue >> 8) & 0x03) {
			case 0x01:	return color_t(    0, ~step,  step);
			case 0x02:	return color_t( step,     0, ~step);
			default:	return color_t(~step,  step,     0);
		}
	}
/ *
	for (uint16_t i=0; i<strip.total(); i++) {
		if (((i+offset) & 0x03) == 0x00) {
			strip.pixel(color);
		} else {
			strip.pixel(color_t::black());
		}
	}
*/
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
		case 0x03:	chase();		break;

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
