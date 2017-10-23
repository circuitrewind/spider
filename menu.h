#ifndef __MENU_H__
#define __MENU_H__



#include "defines.h"



class menu : public spidergame {
public:
	menu() : selected(0) {
		LED_LEFT.fifoWrite(0x0101);
		LED_RIGHT.fifoWrite(0x0101);
		LED_LEFT.fifoWrite(0x0240);
		LED_RIGHT.fifoWrite(0x0240);
		LED_LEFT.fifoWrite(0x0300);
		LED_RIGHT.fifoWrite(0x0300);
	}
	virtual void frame(pixelArray **strip, WII **wii);

private:
	int8_t selected;
};



#endif //__MENU_H__
