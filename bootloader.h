#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__



#include "defines.h"



#define SCROLL_DELAY 100



class bootloader : public spidergame  {
public:
	bootloader(bool load=false) :
		x_offset(GRID_WIDTH),
		loaded(load) {}

	virtual void loop(pixelArray *strip, WII **wii);

private:
	int16_t	x_offset;
	bool	loaded;
};




#endif //__BOOTLOADER_H__
