#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



#include "defines.h"
#include "anim.h"



void anim::frame(pixelArray **strip, WII **wii) {
	for (int i=0; i<PLAYERS; i++) {
		if (!wii[i]->wiimoteConnected) continue;

		if (wii[i]->getButtonClick(ONE)) {
			reset(0, GRID_WIDTH);
		}


		if (wii[i]->getButtonClick(TWO)) {
			reset(1);
		}
	}


	strip[0]->clear();


	switch (mode) {
		case 0:
			const char *text = "KAEATRI";

			if (elapsed >= SCROLL_DELAY) {
				elapsed -= SCROLL_DELAY;
				cycle--;
				if (cycle < 0-pixelArray::stringWidth(text)) {
					cycle = (strip[0]->width()) + 5;
				}
			}

			strip[0]->string(text, cycle, strip[0]->height()-5);
		break;
	}

}




#endif //TEENSYDUINO || ARDUINO_AVR_NANO
