#include "defines.h"
#include "led.h"




#ifdef __AVR__

////////////////////////////////////////////////////////////////////////////////
// THE MAGIC FUNCTION - THIS ALLOWS RENDERING TO THE LED ARRAY
// THIS IS A MODIFIED VERSION OF THE FOLLOWING CODE:
// github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.cpp#L152
////////////////////////////////////////////////////////////////////////////////
void ws2812b::pixel(const color_t &color) {
	const		uint8_t	pin		= this->_pin;
	volatile	uint8_t	*port	= portOutputRegister(digitalPinToPort(pin));

	volatile	uint8_t	i		= 3;
	volatile	uint8_t	*ptr	= (uint8_t*)&color;
	volatile	uint8_t	b		= *ptr++;
	volatile	uint8_t	hi		= PORTB |  (1 << pin);
	volatile	uint8_t	lo		= PORTB & ~(1 << pin);
	volatile	uint8_t	n1		= (b & 0x80) ? hi : lo;
	volatile	uint8_t	n2		= 0;

	asm volatile(
		"headB:"                  "\n\t"
		"out  %[port] , %[hi]"    "\n\t"
		"mov  %[n2]   , %[lo]"    "\n\t"
		"out  %[port] , %[n1]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"sbrc %[byte] , 6"        "\n\t"
		 "mov %[n2]   , %[hi]"    "\n\t"
		"out  %[port] , %[lo]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"out  %[port] , %[hi]"    "\n\t"
		"mov  %[n1]   , %[lo]"    "\n\t"
		"out  %[port] , %[n2]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"sbrc %[byte] , 5"        "\n\t"
		 "mov %[n1]   , %[hi]"    "\n\t"
		"out  %[port] , %[lo]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"out  %[port] , %[hi]"    "\n\t"
		"mov  %[n2]   , %[lo]"    "\n\t"
		"out  %[port] , %[n1]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"sbrc %[byte] , 4"        "\n\t"
		 "mov %[n2]   , %[hi]"    "\n\t"
		"out  %[port] , %[lo]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"out  %[port] , %[hi]"    "\n\t"
		"mov  %[n1]   , %[lo]"    "\n\t"
		"out  %[port] , %[n2]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"sbrc %[byte] , 3"        "\n\t"
		 "mov %[n1]   , %[hi]"    "\n\t"
		"out  %[port] , %[lo]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"out  %[port] , %[hi]"    "\n\t"
		"mov  %[n2]   , %[lo]"    "\n\t"
		"out  %[port] , %[n1]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"sbrc %[byte] , 2"        "\n\t"
		 "mov %[n2]   , %[hi]"    "\n\t"
		"out  %[port] , %[lo]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"out  %[port] , %[hi]"    "\n\t"
		"mov  %[n1]   , %[lo]"    "\n\t"
		"out  %[port] , %[n2]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"sbrc %[byte] , 1"        "\n\t"
		 "mov %[n1]   , %[hi]"    "\n\t"
		"out  %[port] , %[lo]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"out  %[port] , %[hi]"    "\n\t"
		"mov  %[n2]   , %[lo]"    "\n\t"
		"out  %[port] , %[n1]"    "\n\t"
		"rjmp .+0"                "\n\t"
		"sbrc %[byte] , 0"        "\n\t"
		 "mov %[n2]   , %[hi]"    "\n\t"
		"out  %[port] , %[lo]"    "\n\t"
		"subi %[count], 1"        "\n\t"
		"out  %[port] , %[hi]"    "\n\t"
		"mov  %[n1]   , %[lo]"    "\n\t"
		"out  %[port] , %[n2]"    "\n\t"
		"ld   %[byte] , %a[ptr]+" "\n\t"
		"sbrc %[byte] , 7"        "\n\t"
		 "mov %[n1]   , %[hi]"    "\n\t"
		"out  %[port] , %[lo]"    "\n\t"
		"brne headB"              "\n"
	: [byte] "+r" (b), [n1] "+r" (n1), [n2] "+r" (n2), [count] "+w" (i)
	: [port] "I" (_SFR_IO_ADDR(PORTB)), [ptr] "e" (ptr), [hi] "r" (hi),
		[lo] "r" (lo));
}


#endif //__AVR__




#if defined(TEENSYDUINO) && defined(__MKL26Z64__) // Teensy-LC

void ws2812b::pixel(const color_t &color) {
	const		uint8_t	pin		= this->_pin;
	volatile	uint8_t	*reg	= portSetRegister(pin);
	volatile	uint8_t	bitmask	= digitalPinToBitMask(pin);

	volatile	uint8_t	*p		= (uint8_t*)&color;
	volatile	uint8_t	num		= 3;
	volatile	uint8_t	pix;
	volatile	uint8_t	count;
	volatile	uint8_t	dly;

	asm volatile(
		"L%=_begin:"						"\n\t"
		"ldrb	%[pix], [%[p], #0]"			"\n\t"
		"lsl	%[pix], #24"				"\n\t"
		"movs	%[count], #7"				"\n\t"
		"L%=_loop:"							"\n\t"
		"lsl	%[pix], #1"					"\n\t"
		"bcs	L%=_loop_one"				"\n\t"
		"L%=_loop_zero:"
		"strb	%[bitmask], [%[reg], #0]"	"\n\t"
		"movs	%[dly], #4"					"\n\t"
		"L%=_loop_delay_T0H:"				"\n\t"
		"sub	%[dly], #1"					"\n\t"
		"bne	L%=_loop_delay_T0H"			"\n\t"
		"strb	%[bitmask], [%[reg], #4]"	"\n\t"
		"movs	%[dly], #13"				"\n\t"
		"L%=_loop_delay_T0L:"				"\n\t"
		"sub	%[dly], #1"					"\n\t"
		"bne	L%=_loop_delay_T0L"			"\n\t"
		"b	L%=_next"						"\n\t"
		"L%=_loop_one:"
		"strb	%[bitmask], [%[reg], #0]"	"\n\t"
		"movs	%[dly], #13"				"\n\t"
		"L%=_loop_delay_T1H:"				"\n\t"
		"sub	%[dly], #1"					"\n\t"
		"bne	L%=_loop_delay_T1H"			"\n\t"
		"strb	%[bitmask], [%[reg], #4]"	"\n\t"
		"movs	%[dly], #4"					"\n\t"
		"L%=_loop_delay_T1L:"				"\n\t"
		"sub	%[dly], #1"					"\n\t"
		"bne	L%=_loop_delay_T1L"			"\n\t"
		"nop"								"\n\t"
		"L%=_next:"							"\n\t"
		"sub	%[count], #1"				"\n\t"
		"bne	L%=_loop"					"\n\t"
		"lsl	%[pix], #1"					"\n\t"
		"bcs	L%=_last_one"				"\n\t"
		"L%=_last_zero:"
		"strb	%[bitmask], [%[reg], #0]"	"\n\t"
		"movs	%[dly], #4"					"\n\t"
		"L%=_last_delay_T0H:"				"\n\t"
		"sub	%[dly], #1"					"\n\t"
		"bne	L%=_last_delay_T0H"			"\n\t"
		"strb	%[bitmask], [%[reg], #4]"	"\n\t"
		"movs	%[dly], #10"				"\n\t"
		"L%=_last_delay_T0L:"				"\n\t"
		"sub	%[dly], #1"					"\n\t"
		"bne	L%=_last_delay_T0L"			"\n\t"
		"b	L%=_repeat"						"\n\t"
		"L%=_last_one:"
		"strb	%[bitmask], [%[reg], #0]"	"\n\t"
		"movs	%[dly], #13"				"\n\t"
		"L%=_last_delay_T1H:"				"\n\t"
		"sub	%[dly], #1"					"\n\t"
		"bne	L%=_last_delay_T1H"			"\n\t"
		"strb	%[bitmask], [%[reg], #4]"	"\n\t"
		"movs	%[dly], #1"					"\n\t"
		"L%=_last_delay_T1L:"				"\n\t"
		"sub	%[dly], #1"					"\n\t"
		"bne	L%=_last_delay_T1L"			"\n\t"
		"nop"								"\n\t"
		"L%=_repeat:"						"\n\t"
		"add	%[p], #1"					"\n\t"
		"sub	%[num], #1"					"\n\t"
		"bne	L%=_begin"					"\n\t"
		"L%=_done:"							"\n\t"
		: [p] "+r" (p),
		[pix] "=&r" (pix),
		[count] "=&r" (count),
		[dly] "=&r" (dly),
		[num] "+r" (num)
		: [bitmask] "r" (bitmask),
		[reg] "r" (reg)
	);
}

#endif //defined(TEENSYDUINO) && defined(__MKL26Z64__) // Teensy-LC
