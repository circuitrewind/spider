#include "spider.h"
#include "spidergames.h"


#define SCROLL_DELAY 100


void spiderBootscreen::loop(pixelArray *strip, WII *wii) {
	if (!loaded) {
		if (elapsed < 2000) return;
		elapsed -= 2000;
		loaded = true;
	}



	if (elapsed < SCROLL_DELAY) return;
	elapsed -= SCROLL_DELAY;



	strip->clear();

	x_offset--;
	if (x_offset <  -strip->stringWidth("PRESS 1+2")) {
		x_offset = GRID_WIDTH + 5;
	}

	strip->string("PRESS SYNC", x_offset, 0, color_t::purple().right(4));


	for (int i=0; i<PLAYERS; i++) {
		if (wii[i].wiimoteConnected) {
			char str[3] = {'P', '\0', '\0'};
			str[1] = i + '1';
			strip->string(str, i*8, GRID_HEIGHT-6, pix_colorz[i+1]);

			if (wii[i].getButtonClick(A)) {
				delete game;
				game = new spiderPaint();
				return;
			}
		}
	}
}
