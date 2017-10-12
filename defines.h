/*----------------------------------------------------------------------------*\
| a collection of common defines, structs, values which will be used           |
| everywhere within the Spider Board project and future projects.              |
\*----------------------------------------------------------------------------*/




#ifndef __defines_h__
#define __defines_h__




#ifndef INLINE
#define INLINE		inline __attribute__ ((always_inline))
#endif




#include <arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <WProgram.h>
#include "binary.h"
#include "color.h"




#endif //__defines_h__
