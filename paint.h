#ifndef __PAINT_H__
#define __PAINT_H__



#include "defines.h"



class paint : public spidergame {
public:
	paint() {
		for (int i=0; i<PLAYERS; i++) {
			pix_x[i]		= 7;
			pix_y[i]		= i+8;
			pix_z[i]		= 0;
			pix_c[i]		= pix_colorz[i+1];
			pix_cycle[i]	= i+1;
		}
	}

	virtual void loop(pixelArray *strip, WII **wii);

private:
	int8_t		pix_x[PLAYERS];
	int8_t		pix_y[PLAYERS];
	uint32_t	pix_z[PLAYERS];
	uint32_t	pix_c[PLAYERS];
	int8_t		pix_cycle[PLAYERS];
};


#endif //__PAINT_H__
