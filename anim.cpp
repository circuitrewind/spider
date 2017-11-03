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


		if (wii[i]->getButtonClick(MINUS)) {
			dual->clear();
			reset(3);
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
				if (cycle >= (int)(sizeof(command_list)/sizeof(pixel_command))) {
					cycle = 0;
				}

				current = command_list[cycle];
			}

			for (int x=0; x<=cycle; x++) {
				pixel_command painting = command_list[x];
				if (painting.x == 255  &&  painting.y == 255) {
					dual->clear();
				} else {
					dual->draw_mirror(painting.x, painting.y);
				}
			}

		} break;




		////////////////////////////////////////////////////////////////////////
		// LUV DVA
		////////////////////////////////////////////////////////////////////////
		case 2:
			pixelArray::animation(PR_BOTTOM_ANIM);

			strip[0]->string("L",  4,  3);
			strip[0]->string("U",  4,  9);
			strip[0]->string("V",  4, 15);

			strip[1]->string("D",  4,  3);
			strip[1]->string("V",  4,  9);
			strip[1]->string("A",  4, 15);
		break;




		////////////////////////////////////////////////////////////////////////
		// BUNNY EARS!!
		////////////////////////////////////////////////////////////////////////
		case 3:
			for (int y=0; y<GRID_HEIGHT; y++) {
				for (int x=0; x<GRID_WIDTH; x++) {
//					dual->draw_clone(x, y, color_t(200,10,50));
					dual->draw_clone(x, y, color_t(150,10,30));
				}
			}

			for (int y=3; y<GRID_HEIGHT; y++) {
				for (int x=5; x<=6; x++) {
//					dual->draw_clone(x, y, color_t(220,0,10));
					dual->draw_clone(x, y, color_t(160,0,10));
				}
			}

			for (int y=6; y<GRID_HEIGHT; y++) {
				for (int x=4; x<=7; x++) {
//					dual->draw_clone(x, y, color_t(220,0,10));
					dual->draw_clone(x, y, color_t(160,0,10));
				}
			}

			for (int y=10; y<GRID_HEIGHT; y++) {
				for (int x=3; x<=8; x++) {
//					dual->draw_clone(x, y, color_t(220,0,10));
					dual->draw_clone(x, y, color_t(160,0,10));
				}
			}

			for (int y=16; y<GRID_HEIGHT; y++) {
				for (int x=2; x<=9; x++) {
//					dual->draw_clone(x, y, color_t(220,0,10));
					dual->draw_clone(x, y, color_t(160,0,10));
				}
			}
		break;
	}

}




#endif //TEENSYDUINO || ARDUINO_AVR_NANO
