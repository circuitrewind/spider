#ifdef __AVR__


#include "led.h"


////////////////////////////////////////////////////////////////////////////////
// THE MAGIC FUNCTION - THIS ALLOWS RENDERING TO THE LED ARRAY
// THIS IS A MODIFIED VERSION OF THE FOLLOWING CODE:
// github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.cpp#L152
////////////////////////////////////////////////////////////////////////////////
void ws2812b::pixel(const color_t &color) {
	const    uint8_t	pin		= this->_pin;
	volatile uint8_t	*port	= portOutputRegister(digitalPinToPort(pin));

	volatile uint8_t	i		= 3;
	volatile uint8_t	*ptr	= (uint8_t*)&color;
	volatile uint8_t	b		= *ptr++;
	volatile uint8_t	hi		= PORTB |  (1 << pin);
	volatile uint8_t	lo		= PORTB & ~(1 << pin);
	volatile uint8_t	n1		= (b & 0x80) ? hi : lo;
	volatile uint8_t	n2		= 0;

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
