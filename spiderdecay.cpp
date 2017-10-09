#include "spidergames.h"




void spiderDecay::loop(pixelArray *strip, WII *wii) {
	uint8_t *data = strip->getPixels();
	for (uint16_t i=0; i<256*3; i++) {
		if (data[i] > 1) data[i] -= 2;
	}

	static uint16_t counter = 0;
	counter++;
	for (int i=0; i<16; i++) {
		if (counter & (1<<i)) {
			strip->draw(i, 0, RGB(255, 255, 255));
		} else {
			strip->draw(i, 0, RGB(0, 0, 0));
		}
	}


	//AN EXTRA CALL TO RANDOM, BECAUSE WHY NOT?
	random(10);

	if (elapsed > 250) {
		strip->string(
			"PEW",
			random(0, 3),
			random(1, 12),
			pix_colorx[ random(0, 6) ]
		);

		elapsed -= 250;
	}

/*
	strip->setPixelColor(
		random(255),
		pix_colorx[ random(0, 6) ]
	);
*/
}
