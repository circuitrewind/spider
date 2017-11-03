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
#include "anim.h"




#ifdef TEENSYDUINO
#define TOTAL_GAMES 9
#else
#define TOTAL_GAMES 8
#endif




CONST char game_name_0[] = "Anim";
CONST char game_name_1[] = "Blck";
CONST char game_name_2[] = "Pong";
CONST char game_name_3[] = "Draw";
CONST char game_name_4[] = "PEW";
CONST char game_name_5[] = "Fade";
CONST char game_name_6[] = "Host";
CONST char game_name_7[] = "Tiny";
CONST char game_name_8[] = "ISP";

CONST char* const game_name_table[] = {
	game_name_0,
	game_name_1,
	game_name_2,
	game_name_3,
	game_name_4,
	game_name_5,
	game_name_6,
	game_name_7,
	game_name_8,
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
			animation::delete_all();
			strip[0]->clear();

			switch (selected) {
				case 0: new anim();		break;
				case 1: new tetris();	break;
				case 2: new pong();		break;
				case 3: new paint();	break;
				case 4: new decayPew();	break;
				case 5: new decay();	break;
				case 6: new host();		break;
				case 7: new tiny();		break;
				#ifdef TEENSYDUINO
				case 8: new isp();		break;
				#endif
			}

			return;

		} else if (wii[i]->getButtonClick(B)) {
			animation::delete_all();
			strip[0]->clear();
			new bootloader(true);
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
