#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO




#include "defines.h"
#include "menu.h"
#include "bootloader.h"
#include "paint.h"
#include "decay.h"
#include "host.h"
#include "isp.h"
#include "tiny.h"
#include "tetris.h"
#include "pong.h"




#ifdef TEENSYDUINO
#define TOTAL_GAMES 7
#else
#define TOTAL_GAMES 6
#endif




CONST char game_name_0[] = "Paint";
CONST char game_name_1[] = "PEW";
CONST char game_name_2[] = "Fade";
CONST char game_name_3[] = "Host";
CONST char game_name_4[] = "Tiny";
CONST char game_name_5[] = "Tetris";
CONST char game_name_6[] = "Pong";
CONST char game_name_7[] = "ISP";

CONST char* const game_name_table[] = {
	game_name_0,
	game_name_1,
	game_name_2,
	game_name_3,
	game_name_4,
	game_name_5,
	game_name_6,
	game_name_7,
};




void menu::frame(pixelArray **strip, WII **wii) {
	for (int i=0; i<PLAYERS; i++) {
		if (!wii[i]->wiimoteConnected) continue;


		if (wii[i]->getButtonClick(DOWN)) {
			selected++;
			if (selected >= TOTAL_GAMES) selected = 0;

		} else if (wii[i]->getButtonClick(UP)) {
			selected--;
			if (selected < 0) selected = TOTAL_GAMES-1;

		} else if (wii[i]->getButtonClick(TWO)) {
			delete game;
			strip[0]->clear();

			switch (selected) {
				case 0: game = new paint();		break;
				case 1: game = new decayPew();	break;
				case 2: game = new decay();		break;
				case 3: game = new host();		break;
				case 4: game = new tiny();		break;
				case 5: game = new tetris();	break;
				case 6: game = new pong();		break;
				#ifdef TEENSYDUINO
					case 7: game = new isp();	break;
				#endif
			}

			return;

		} else if (wii[i]->getButtonClick(B)) {
			delete game;
			strip[0]->clear();
			game = new bootloader(true);
			return;
		}
	}

	#ifdef TEENSYDUINO
		const char *text = game_name_table[selected];
	#else
		char text[10] = {0};
		strcpy_P(text, (char*)pgm_read_word(&(game_name_table[selected])));
	#endif


	strip[0]->clear();
	strip[0]->string(text, 1, GRID_HEIGHT-5, pix_colorx[selected]);
}




#endif //TEENSYDUINO || ARDUINO_AVR_NANO
