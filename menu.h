#ifndef __MENU_H__
#define __MENU_H__



#include "defines.h"



class menu : public animation {
public:
	menu() : selected(0) {
		ledstrip[0]->fifoWrite(0x010016L);
		ledstrip[1]->fifoWrite(0x010016L);
		ledstrip[0]->fifoWrite(0x020040L);
		ledstrip[1]->fifoWrite(0x020040L);
		ledstrip[0]->fifoWrite(0x030001L);
		ledstrip[1]->fifoWrite(0x030001L);
	}
	virtual void frame(pixelArray **strip, WII **wii);

private:
	int8_t selected;
};



#endif //__MENU_H__
