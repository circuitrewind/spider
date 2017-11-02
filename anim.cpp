#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



#include "defines.h"
#include "anim.h"
#include "pixel_dual.h"



void anim::frame(pixelArray **strip, WII **wii) {
	for (int i=0; i<PLAYERS; i++) {
		if (!wii[i]->wiimoteConnected) continue;

		if (wii[i]->getButtonClick(ONE)) {
			dual->clear();
			reset(0, dual->width());
		}


		if (wii[i]->getButtonClick(TWO)) {
			dual->clear();
			reset(1);
		}


		if (wii[i]->getButtonClick(PLUS)) {
			dual->clear();
			reset(2);
		}
	}




	switch (mode) {
		case 0:
			pixelArray::animation(PR_LEFT);

			if (elapsed >= SCROLL_DELAY) {
				elapsed -= SCROLL_DELAY;
				cycle--;
				if (cycle < 0-pixelArray::stringWidth("KAEATRI")) {
					cycle = (dual->width()) + 5;
				}
			}

			dual->clear();
			dual->string("KAEATRI", cycle, strip[0]->height()-5);
		break;




		////////////////////////////////////////////////////////////////////////
		// Custom "heart" animation for YOU KNOW WHO ;)
		////////////////////////////////////////////////////////////////////////
		case 1: {
			pixelArray::animation(PR_BOTTOM_ANIM);

			pixel_command current = command_list[cycle];
			while (elapsed >= current.delay) {
				elapsed -= current.delay;

				cycle++;
				if (cycle >= (sizeof(command_list)/sizeof(pixel_command))) {
					cycle = 0;
				}

				current = command_list[cycle];
			}

			for (int x=0; x<=cycle; x++) {
				pixel_command painting = command_list[x];
				if (painting.x == 255  &&  painting.y == 255) {
					strip[0]->clear();
				} else {
					strip[0]->draw(painting.x, painting.y);
				}
			}

		} break;




		////////////////////////////////////////////////////////////////////////
		// LUV DVA
		////////////////////////////////////////////////////////////////////////
		case 2:
			pixelArray::animation(PR_TOP_ANIM);

			strip[0]->string("L",  0,  0);
			strip[0]->string("U",  4,  5);
			strip[0]->string("V",  0, 10);

			strip[0]->string("D",  9,  0);
			strip[0]->string("V", 13,  5);
			strip[0]->string("A",  9, 10);
		break;
	}

}




#endif //TEENSYDUINO || ARDUINO_AVR_NANO
