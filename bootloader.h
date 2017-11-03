#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__



#include "defines.h"



class bootloader : public animation  {
public:
	bootloader(bool load=false) :
		x_offset(GRID_WIDTH*2),
		loaded(load) {

		//INITIALIZE THE ATTINY85 LED STRIPS
		ledstrip[0]->fifoWrite(0x010000L);
		ledstrip[1]->fifoWrite(0x010000L);
	}

	virtual void frame(pixelArray **strip, WII **wii);

private:
	int16_t	x_offset;
	bool	loaded;
};




#endif //__BOOTLOADER_H__
