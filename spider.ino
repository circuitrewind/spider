#include "spider.h"


//ATTINY --- PIN 4
#ifdef __AVR_ATtiny85__
	Adafruit_NeoPixel strip		= Adafruit_NeoPixel(10,  4, NEO_GRB + NEO_KHZ800);

#else //TEENSY --- PIN 17: LEFT  --- PIN 9: RIGHT
	Adafruit_NeoPixel strip		= Adafruit_NeoPixel(10, 17, NEO_GRB + NEO_KHZ800);
	Adafruit_NeoPixel strip1	= Adafruit_NeoPixel(10,  9, NEO_GRB + NEO_KHZ800);
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
			unsigned long color = Wheel(((i * 256 / strip.numPixels()) + j) & 255);
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



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if(WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if(WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
