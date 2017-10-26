/*----------------------------------------------------------------------------*\
| a collection of common defines, structs, values which will be used           |
| everywhere within the Spider Board project and future projects.              |
\*----------------------------------------------------------------------------*/




#ifndef __defines_h__
#define __defines_h__




#include <arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#ifdef ARDUINO_AVR_NANO
#include <avr/pgmspace.h>
#include "progmem.h"
#endif //

//#ifdef TEENSYDUINO
//#include <WProgram.h>
//#endif //TEENSYDUINO

#include "elapsedMillis.h"
#include "inline.h"
#include "binary.h"
#include "color.h"
#include "pixel_array.h"


#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO
#include "com_master.h"
#include "games.h"
#endif //TEENSYDUINO || ARDUINO_AVR_NANO



#define SCROLL_DELAY 70



extern int freeRam ();
extern void print_ram();



#endif //__defines_h__
