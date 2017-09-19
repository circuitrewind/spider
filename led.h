////////////////////////////////////////////////////////////////////////////////
// FAST ASM BASED WS2812B ADDRESSABLE LED LED LIBRARY
////////////////////////////////////////////////////////////////////////////////


#ifdef __AVR__


//TOTAL NUMBER OF LEDS
#define LED_TOTAL 20


#define LED_PORT	PORTB
#define LED_DDR		DDRB
#define LED_BIT		4


#define T1H			900		// Width of a 1 bit in ns
#define T1L			600		// Width of a 1 bit in ns

#define T0H			400		// Width of a 0 bit in ns
#define T0L			900		// Width of a 0 bit in ns

#define RES			6000	// Width of the low gap between bits to cause a frame to latch

#define NS_TO_CYCLES(n) ((n) / (1000000000L / (F_CPU)))


// SETUP THE LED STRIP
inline void led_setup();

// FINALIZ AND SHOW LED STRIP
inline void led_show();

// SEND A SINGLE BIT TO THE LED STRIP
inline void led_bit(unsigned char bit);

// SEND A SINGLE BYTE TO THE LED STRIP
inline void led_byte(unsigned char byte);

// SEND A SINGLE PIXEL TO THE LED STRIP
inline void led_pixel(unsigned char r, unsigned char g, unsigned char b);


#endif
