#include "spider.h"




////////////////////////////////////////////////////////////////////////////////
// AVR CODE - USED BY ATTINY85 MICROCONTROLLER
////////////////////////////////////////////////////////////////////////////////
#if defined ARDUINO_attiny || defined ARDUINO_AVR_DIGISPARK
void setup()	{ setup_avr();	}
void loop()		{ loop_avr();	}
#endif //ARDUINO_attiny || ARDUINO_AVR_DIGISPARK




////////////////////////////////////////////////////////////////////////////////
// ARM CODE - USED BY TEENSY-LC MICROCONTROLLER
////////////////////////////////////////////////////////////////////////////////
#ifdef TEENSYDUINO
void setup()	{ setup_arm();	}
void loop()		{ loop_arm();	}
#endif //TEENSYDUINO || ARDUINO_AVR_NANO




////////////////////////////////////////////////////////////////////////////////
// AVR CODE - USED BY ARDUINO NANO MICROCONTROLLER
////////////////////////////////////////////////////////////////////////////////
#ifdef ARDUINO_AVR_NANO
void setup()	{ setup_nano();	}
void loop()		{ loop_nano();	}
#endif //ARDUINO_AVR_NANO
