#include "defines.h"
#include "paint.h"



color_t pix_colorz[7] = {
	color_t(32,  0,  0),
	color_t( 0, 32,  0),
	color_t( 0,  0, 32),
	color_t( 0, 32, 32),
	color_t(32,  0, 32),
	color_t(32, 32,  0),
	color_t(32, 32, 32),
};



color_t pix_colorx[7] = {
	color_t(255,   0,   0),
	color_t( 0,  255,   0),
	color_t( 0,    0, 255),
	color_t( 0,  255, 255),
	color_t(255,   0, 255),
	color_t(255, 255,   0),
	color_t(255, 255, 255),
};




void paint::loop(pixelArray **strip, WII **wii) {
	for (int i=0; i<PLAYERS; i++) {
		if (!wii[i]->wiimoteConnected) continue;


		if (wii[i]->getButtonClick(LEFT)) {
			Serial.print(F("\r\nLeft"));
			if (pix_y[i] < GRID_HEIGHT-1) {
				strip[0]->swap(pix_x[i], pix_y[i], pix_z[i]);
				pix_y[i]++;
				pix_z[i] = strip[0]->swap(pix_x[i], pix_y[i], pix_c[i]);
			}
		}


		if (wii[i]->getButtonClick(RIGHT)) {
			Serial.print(F("\r\nRight"));
			if (pix_y[i] > 0) {
				strip[0]->swap(pix_x[i], pix_y[i], pix_z[i]);
				pix_y[i]--;
				pix_z[i] = strip[0]->swap(pix_x[i], pix_y[i], pix_c[i]);
			}
		}


		if (wii[i]->getButtonClick(DOWN)) {
			Serial.print(F("\r\nDown"));
			if (pix_x[i] < GRID_WIDTH-1) {
				strip[0]->swap(pix_x[i], pix_y[i], pix_z[i]);
				pix_x[i]++;
				pix_z[i] = strip[0]->swap(pix_x[i], pix_y[i], pix_c[i]);
			}
		}


		if (wii[i]->getButtonClick(UP)) {
			Serial.print(F("\r\nUp"));
			if (pix_x[i] > 0) {
				strip[0]->swap(pix_x[i], pix_y[i], pix_z[i]);
				pix_x[i]--;
				pix_z[i] = strip[0]->swap(pix_x[i], pix_y[i], pix_c[i]);
			}
		}


		if (wii[i]->getButtonClick(PLUS)) {
			Serial.print(F("\r\nPlus"));
			if (pix_cycle[i] == 6) {
				pix_cycle[i] = 0;
			} else {
				pix_cycle[i]++;
			}
			pix_c[i] = pix_colorz[pix_cycle[i]];
			strip[0]->swap(pix_x[i], pix_y[i], pix_c[i]);
		}


		if (wii[i]->getButtonClick(MINUS)) {
			Serial.print(F("\r\nMinus"));
			if (pix_cycle[i] == 0) {
				pix_cycle[i] = 6;
			} else {
				pix_cycle[i]--;
			}
			pix_c[i] = pix_colorz[pix_cycle[i]];
			strip[0]->swap(pix_x[i], pix_y[i], pix_c[i]);
		}


		if (wii[i]->getButtonClick(ONE)) {
			Serial.print(F("\r\nOne"));
			pix_z[i] = color_t::black();
		}


		if (wii[i]->getButtonClick(TWO)) {
			Serial.print(F("\r\nTwo"));
			pix_z[i] = pix_c[i];
		}


		if (wii[i]->getButtonClick(A)) {
			Serial.print(F("\r\nA"));
		}


		if (wii[i]->getButtonClick(B)) {
//			wii[i]->setAllOff();
//			wii[i]->setLedOn(WII_LED::P3);
//			wii[i]->setRumbleToggle();
			Serial.print(F("\r\nB"));
		}
	}
}
