#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



#include "defines.h"
#include "anim.h"



void anim::frame(pixelArray **strip, WII **wii) {
	for (int i=0; i<PLAYERS; i++) {
		if (!wii[i]->wiimoteConnected) continue;

		if (wii[i]->getButtonClick(ONE)) {
			strip[0]->clear();
			reset(0, GRID_WIDTH);
		}


		if (wii[i]->getButtonClick(TWO)) {
			strip[0]->clear();
			reset(1);
		}


		if (wii[i]->getButtonClick(PLUS)) {
			strip[0]->clear();
			reset(2);
		}
	}




	switch (mode) {
		case 0:
			if (elapsed >= SCROLL_DELAY) {
				elapsed -= SCROLL_DELAY;
				cycle--;
				if (cycle < 0-pixelArray::stringWidth("KAEATRI")) {
					cycle = (strip[0]->width()) + 5;
				}
			}

			strip[0]->clear();
			strip[0]->string("KAEATRI", cycle, strip[0]->height()-5);
		break;




		////////////////////////////////////////////////////////////////////////
		// Custom "heart" animation for YOU KNOW WHO ;)
		////////////////////////////////////////////////////////////////////////
		case 1: {
			pixel_command current = command_list[cycle];
			while (elapsed >= current.delay) {
				elapsed -= current.delay;

				if (current.x == 255  &&  current.y == 255) {
					strip[0]->clear();
				} else {
					strip[0]->draw(current.x, current.y, color_t::red());
				}

				cycle++;
				if (cycle >= (sizeof(command_list)/sizeof(pixel_command))) {
					cycle = 0;
				}

				current = command_list[cycle];
			}
		} break;




		////////////////////////////////////////////////////////////////////////
		// LUV DVA
		////////////////////////////////////////////////////////////////////////
		case 2:
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
