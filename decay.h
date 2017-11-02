#ifndef __DECAY_H__
#define __DECAY_H__



#include "fadeout.h"
#include "pixel_dual.h"



class decay : public fadeout {
public:
	decay(uint8_t decay_rate=4) : fadeout(FADE_BOTH, decay_rate) {
		new fadeout(0);
	}

protected:
	virtual void frame(pixelArray **strip, WII **wii) {
		fadeout::frame(strip, wii);
		draw(strip[0]);
		#ifdef TEENSYDUINO
		draw(strip[1]);
		#endif
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



class decayPew : public fadeout {
public:
	decayPew() : fadeout(FADE_BOTH, 8) {}

protected:
	virtual void frame(pixelArray **strip, WII **wii) {
		fadeout::frame(strip, wii);

		if (elapsed < 250) return;
		elapsed -= 250;

		dual->string(
			"PEW",
			random(0, GRID_WIDTH),
			random(6, GRID_HEIGHT),
			pix_colorx[ random(0, 6) ]
		);
	}
};



#endif //__DECAY_H__
