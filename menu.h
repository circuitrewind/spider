#ifndef __MENU_H__
#define __MENU_H__



#include "defines.h"



class menu : public spidergame {
public:
	menu() : selected(0) {
		LED_LEFT.fifoWrite( 0x010001L);
		LED_RIGHT.fifoWrite(0x010001L);
		LED_LEFT.fifoWrite( 0x020040L);
		LED_RIGHT.fifoWrite(0x020040L);
		LED_LEFT.fifoWrite( 0x030000L);
		LED_RIGHT.fifoWrite(0x030000L);
	}
	virtual void frame(pixelArray **strip, WII **wii);

private:
	int8_t selected;
};



#endif //__MENU_H__
