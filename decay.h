#ifndef __DECAY_H__
#define __DECAY_H__



#include "defines.h"



class decay : public spidergame {
public:
	decay(uint8_t decay_rate=4) : rate(decay_rate) {}

protected:
	virtual void loop(pixelArray **strip, WII **wii) {
		uint8_t *data;

		data = (uint8_t*) strip[0]->getPixels();
		for (uint16_t i=0; i<GRID_TOTAL*3; i++) {
			if (data[i] > rate) data[i] -= rate;
			else data[i] = 0;
		}

		data = (uint8_t*) strip[1]->getPixels();
		for (uint16_t i=0; i<GRID_TOTAL*3; i++) {
			if (data[i] > rate) data[i] -= rate;
			else data[i] = 0;
		}

		draw(strip[0]);
		draw(strip[1]);
	}

	virtual void draw(pixelArray *strip) {
		strip->setPixelColor(
			random(255),
			pix_colorx[ random(0, 6) ]
		);
	}

private:
	uint8_t rate;
};



class decayPew : public decay {
public:
	decayPew() : decay(8) {}

protected:
	virtual void draw(pixelArray *strip) {
		if (elapsed < 250) return;
		elapsed -= 250;

		strip->string(
			"PEW",
			random(0, 3),
			random(1, 12),
			pix_colorx[ random(0, 6) ]
		);
	}
};



#endif //__DECAY_H__
