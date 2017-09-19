// Source:
// https://github.com/darkain/SimpleNeoPixelDemo


#ifdef __AVR__


#include "led.h"
#include <avr/io.h>


inline void led_bit(unsigned char bit) {

	// 0 bit
	if (bit) {

		asm volatile (
			"sbi	%[port],	%[bit]		\n\t"
			".rept	%[onCycles]				\n\t"
			"nop							\n\t"
			".endr							\n\t"
			"cbi	%[port],	%[bit]		\n\t"
			".rept	%[offCycles]			\n\t"
			"nop							\n\t"
			".endr							\n\t"
			::
			[port]		"I" (_SFR_IO_ADDR(LED_PORT)),
			[bit]		"I" (LED_BIT),
			[onCycles]	"I" (NS_TO_CYCLES(T1H) - 2),
			[offCycles]	"I" (NS_TO_CYCLES(T1L) - 2)
		);


	// 1 bit
	} else {

		asm volatile (
			"sbi %[port], %[bit] \n\t"
			".rept %[onCycles] \n\t"
			"nop \n\t"
			".endr \n\t"
			"cbi %[port], %[bit] \n\t"
			".rept %[offCycles] \n\t"
			"nop \n\t"
			".endr \n\t"
			::
			[port]		"I" (_SFR_IO_ADDR(LED_PORT)),
			[bit]		"I" (LED_BIT),
			[onCycles]	"I" (NS_TO_CYCLES(T0H) - 2),
			[offCycles]	"I" (NS_TO_CYCLES(T0L) - 2)
		);

	}
}


inline void led_byte(unsigned char byte) {
	for(char bit = 0; bit < 8; bit++) {
		led_bit(bitRead(byte ,7));
		byte <<= 1;
	}
}



inline void led_setup() {
	bitSet(LED_DDR, LED_BIT);
}



inline void led_show() {
	// Round up since the delay must be _at_least_
	// this long (too short might not work, too long not a problem)
	_delay_us((RES / 1000UL) + 1);
}



inline void led_pixel(unsigned char r, unsigned char g, unsigned char b) {
	sendByte(g);
	sendByte(r);
	sendByte(b);
}


#endif
