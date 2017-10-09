#include "spidergames.h"


#define SCROLL_DELAY 100


void spiderBootscreen::loop(pixelArray *strip, WII *wii) {
	if (!loaded) {
		if (elapsed < 2000) return;
		elapsed -= 2000;
		loaded = true;
	}

	for (int i=0; i<PLAYERS; i++) {
		if (wii[i].wiimoteConnected) {
			delete game;
			game = new spiderDecay();
			return;
		}
	}

	if (elapsed < SCROLL_DELAY) return;
	elapsed -= SCROLL_DELAY;

	strip->clear();

	x_offset--;
	if (x_offset <  -strip->stringWidth("PRESS 1+2")) {
		x_offset = GRID_WIDTH + 5;
	}

	strip->string("PRESS 1+2", x_offset, 0, pix_colorz[4]);
}
