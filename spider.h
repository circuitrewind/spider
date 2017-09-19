#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
	#include <avr/power.h>
#endif



//PRIMARY LED STRIP
//USED ON ATTINY85 AND TEENSY
extern Adafruit_NeoPixel strip;

//SECONDARY LED STRIP
//ONLY THE TEENSY HAS TWO STRIPS
#ifndef __AVR_ATtiny85__
	extern Adafruit_NeoPixel strip1;
#endif
