#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



#include "defines.h"
#include "bootloader.h"
#include "paint.h"
#include "pixel_dual.h"



void bootloader::frame(pixelArray **strip, WII **wii) {
	if (!loaded) {
		if (elapsed < 2000) return;
		elapsed -= 2000;
		loaded = true;
	}



	if (elapsed < SCROLL_DELAY) return;
	elapsed -= SCROLL_DELAY;


	const char *sync_text = "SYNC WII REMOTES AND THEN PRESS HOME";


	dual->clear();

	x_offset--;
	if (x_offset < -pixelArray::stringWidth(sync_text)) {
		x_offset = (dual->width()) + 5;
	}

	dual->string(sync_text, x_offset, dual->height()-5, color_t::purple().right(4));


	for (int i=0; i<PLAYERS; i++) {
		if (wii[i]->wiimoteConnected) {
			char str[3] = {'P', '\0', '\0'};
			str[1] = i + '1';

			dual->string(
				str,
				(i & 0x01) * 8,
				(((i & 0x02) >> 1) * 6) + (dual->height()-11),
				pix_colorz[i+1]
			);
		}
	}
}




#endif //TEENSYDUINO || ARDUINO_AVR_NANO
