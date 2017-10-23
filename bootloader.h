#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__



#include "defines.h"



#define SCROLL_DELAY 100



class bootloader : public spidergame  {
public:
	bootloader(bool load=false) :
		x_offset(GRID_WIDTH*2),
		loaded(load) {

		//INITIALIZE THE ATTINY85 LED STRIPS
		Serial.println("ATTiny85");
		LED_LEFT.fifoWrite(0x0100);
		LED_RIGHT.fifoWrite(0x0100);
	}

	virtual void frame(pixelArray **strip, WII **wii);

private:
	int16_t	x_offset;
	bool	loaded;
};




#endif //__BOOTLOADER_H__
