#ifndef __TINY_H__
#define __TINY_H__



#include "defines.h"



class tiny : public spidergame {
public:
	virtual void frame(pixelArray **strip, WII **wii) {
		for (int i=0; i<PLAYERS; i++) {
			if (!wii[i]->wiimoteConnected) continue;

			if (wii[i]->getButtonClick(ONE)) {
				LED_LEFT.fifoWrite(0x010001);
			}

			if (wii[i]->getButtonClick(TWO)) {
				LED_LEFT.fifoWrite(0x010002);
			}

			if (wii[i]->getButtonClick(UP)) {
				LED_LEFT.fifoWrite(0x010003);
			}

			if (wii[i]->getButtonClick(DOWN)) {
				LED_LEFT.fifoWrite(0x010013);
			}

			if (wii[i]->getButtonClick(LEFT)) {
				LED_LEFT.fifoWrite(0x010014);
			}

			if (wii[i]->getButtonClick(RIGHT)) {
				LED_LEFT.fifoWrite(0x010015);
			}

		}
	}
};


#endif //__TINY_H__
