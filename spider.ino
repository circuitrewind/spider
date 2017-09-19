#include "spider.h"


#ifndef __AVR__ //TEENSY --- PIN 17: LEFT  --- PIN 9: RIGHT
	Adafruit_NeoPixel strip		= Adafruit_NeoPixel(10, 17, NEO_GRB + NEO_KHZ800);
	Adafruit_NeoPixel strip1	= Adafruit_NeoPixel(10,  9, NEO_GRB + NEO_KHZ800);
#else
	Adafruit_NeoPixel strip		= Adafruit_NeoPixel(0, 5, NEO_GRB + NEO_KHZ800);
#endif



void setup() {
	#ifdef __AVR_ATtiny85__
		if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
	#else //TEENSY
		strip1.begin();
		strip1.show();
	#endif

	strip.begin();
	strip.show();
}



void loop() {
	rainbowCycle(20);
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
	uint16_t i, j;

	for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
		for(i=0; i< strip.numPixels(); i++) {
			unsigned long color = color_wheel(((i*256*3) / strip.numPixels()) + j);
			strip.setPixelColor(i, color);
			#ifndef __AVR_ATtiny85__
				strip1.setPixelColor(i, color);
			#endif
		}

		strip.show();

		#ifndef __AVR_ATtiny85__
			strip1.show();
		#endif

		delay(wait);
	}
}



////////////////////////////////////////////////////////////////////////////////
// Input a hue value 0 to 767 to get a RGB color value.
// The colors are a transition r - g - b - back to r.
////////////////////////////////////////////////////////////////////////////////
uint32_t color_wheel(uint16_t hue) {
	uint8_t step = hue & 0xff;

	if (hue >= (256*3)) hue = hue % (256*3);

	switch (hue >> 8) {
		case 0: return RGB(~step,	step,	0);
		case 1: return RGB(0,		~step,	step);
		case 2: return RGB(step,	0,		~step);
	}
	return 0;
}
