#include "defines.h"
#include "menu.h"
#include "bootloader.h"
#include "paint.h"
#include "decay.h"
#include "host.h"



#define TOTAL_GAMES 4



void menu::loop(pixelArray **strip, WII **wii) {
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
			}

			return;

		} else if (wii[i]->getButtonClick(B)) {
			delete game;
			strip[0]->clear();
			game = new bootloader(true);
			return;
		}
	}


	const char *text = NULL;

	switch (selected) {
		case 0: text = "Paint";	break;
		case 1: text = "PEW";	break;
		case 2: text = "Fade";	break;
		case 3: text = "Host";	break;
	}

	strip[0]->clear();
	strip[0]->string(text, 0, 0, pix_colorx[selected]);
}
