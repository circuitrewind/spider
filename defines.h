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

#ifdef CORE_TEENSY
#include <WProgram.h>
#endif //CORE_TEENSY

#include "elapsedMillis.h"
#include "inline.h"
#include "binary.h"
#include "color.h"
#include "pixel_array.h"


#ifdef CORE_TEENSY
#include "games.h"
#endif //CORE_TEENSY




#endif //__defines_h__
