#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



#include "defines.h"
#include "bootloader.h"
#include "paint.h"
#include "pixel_dual.h"


#ifdef TEENSYDUINO
#define RENDERER	dual
#define BOOT_DELAY	2000
#else
#define RENDERER	strip[0]
#define BOOT_DELAY	10
#endif



void bootloader::frame(pixelArray **strip, WII **wii) {
	if (!loaded) {
		if (elapsed < BOOT_DELAY) return;
		elapsed -= BOOT_DELAY;
		loaded = true;
	}



	if (elapsed < SCROLL_DELAY) return;
	elapsed -= SCROLL_DELAY;


	const char *sync_text = "SYNC WII REMOTES AND THEN PRESS HOME";

	RENDERER->clear();


	x_offset--;
	if (x_offset < 0-pixelArray::stringWidth(sync_text)) {
		x_offset = (RENDERER->width()) + 5;
	}

	RENDERER->string(sync_text, x_offset, RENDERER->height()-5, color_t::purple().right(4));


	for (int i=0; i<PLAYERS; i++) {
		if (wii[i]->wiimoteConnected) {
			char str[3] = {'P', '\0', '\0'};
			str[1] = i + '1';

			RENDERER->string(
				str,
				(i & 0x01) * 8,
				(((i & 0x02) >> 1) * 6) + (RENDERER->height()-11),
				pix_colorz[i+1]
			);
		}
	}
}




#endif //TEENSYDUINO || ARDUINO_AVR_NANO
