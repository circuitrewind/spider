#ifndef __SPIDER_CONFIG_H__
#define __SPIDER_CONFIG_H__




#ifdef TEENSYDUINO
#include <Wii.h>
#define PLAYERS 4
#else //ARDUINO_AVR_NANO
#include "wiipad.h"
#define PLAYERS 1
#endif //TEENSYDUINO/ARDUINO_AVR_NANO


#ifdef TEENSYDUINO
#define GRID_WIDTH	12
#define GRID_HEIGHT	23
#else
#define GRID_WIDTH	16
#define GRID_HEIGHT	16
#endif


#define GRID_TOTAL	((GRID_WIDTH)*(GRID_HEIGHT))
#define GRID_MAX	((GRID_WIDTH)>(GRID_HEIGHT)?(GRID_WIDTH):(GRID_HEIGHT))
#define GRID_MIN	((GRID_WIDTH)<(GRID_HEIGHT)?(GRID_WIDTH):(GRID_HEIGHT))


#define SCROLL_DELAY 70



#endif //__SPIDER_CONFIG_H__
