#ifndef __FADEOUT_H__
#define __FADEOUT_H__



#include "defines.h"


#define FADE_LEFT	1
#define FADE_RIGHT	2
#define FADE_BOTH	3



class fadeout : public animation {
public:
	fadeout(uint8_t grid, uint8_t fadeout_rate=4)
	: rate(fadeout_rate) {
		player = grid;
	}

	void faderate(uint8_t amount) { rate=amount; }
	uint8_t faderate() { return rate; }


protected:
	virtual void frame(pixelArray **strip, WII **wii) {
		uint8_t *data;

		if (player == 0  ||  player == FADE_BOTH) {
			data = (uint8_t*) strip[0]->getPixels();
			for (uint16_t i=0; i<GRID_TOTAL*3; i++) {
				if (data[i] > rate) data[i] -= rate;
				else data[i] = 0;
			}
		}

		if (player == 1  ||  player == FADE_BOTH) {
			data = (uint8_t*) strip[1]->getPixels();
			for (uint16_t i=0; i<GRID_TOTAL*3; i++) {
				if (data[i] > rate) data[i] -= rate;
				else data[i] = 0;
			}
		}
	}


protected:
	uint8_t rate;
	uint8_t player;
};




#endif //__FADEOUT_H__
