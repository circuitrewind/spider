#include "defines.h"
#include "bootloader.h"
#include "paint.h"



void bootloader::loop(pixelArray **strip, WII **wii) {
	if (!loaded) {
		if (elapsed < 2000) return;
		elapsed -= 2000;
		loaded = true;
	}



	if (elapsed < SCROLL_DELAY) return;
	elapsed -= SCROLL_DELAY;



	strip[0]->clear();

	x_offset--;
	if (x_offset <  -strip[0]->stringWidth("PRESS 1+2")) {
		x_offset = GRID_WIDTH + 5;
	}

	strip[0]->string("PRESS SYNC", x_offset, 0, color_t::purple().right(4));


	for (int i=0; i<PLAYERS; i++) {
		if (wii[i]->wiimoteConnected) {
			char str[3] = {'P', '\0', '\0'};
			str[1] = i + '1';

			strip[0]->string(
				str,
				(i & 0x01) * 8,
				(((i & 0x02) >> 1) * 6) + (GRID_HEIGHT-11),
				pix_colorz[i+1]
			);
		}
	}
}
