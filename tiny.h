#ifndef __TINY_H__
#define __TINY_H__



#include "defines.h"



class tiny : public animation {
public:
	virtual void frame(pixelArray **strip, WII **wii) {
		for (int i=0; i<min(PLAYERS,2); i++) {
			if (!wii[i]->wiimoteConnected) continue;

			if (wii[i]->getButtonClick(ONE)) {
				ledstrip[0]->fifoWrite(0x01000000);
				ledstrip[1]->fifoWrite(0x01000000);
			}

			if (wii[i]->getButtonClick(TWO)) {
				ledstrip[0]->fifoWrite(0x00010000);
				ledstrip[1]->fifoWrite(0x00010000);
			}

			if (wii[i]->getButtonClick(PLUS)) {
				ledstrip[0]->fifoWrite(0x00000100);
				ledstrip[1]->fifoWrite(0x00000100);
			}

			if (wii[i]->getButtonClick(MINUS)) {
				ledstrip[0]->fifoWrite(0x00000001);
				ledstrip[1]->fifoWrite(0x00000001);
			}

			if (wii[i]->getButtonClick(UP)) {
				ledstrip[0]->fifoWrite(0x80000000);
				ledstrip[1]->fifoWrite(0x80000000);
			}

			if (wii[i]->getButtonClick(DOWN)) {
				ledstrip[0]->fifoWrite(0x00800000);
				ledstrip[1]->fifoWrite(0x00800000);
			}

			if (wii[i]->getButtonClick(LEFT)) {
				ledstrip[0]->fifoWrite(0x00008000);
				ledstrip[1]->fifoWrite(0x00008000);
			}

			if (wii[i]->getButtonClick(RIGHT)) {
				ledstrip[0]->fifoWrite(0x00000080);
				ledstrip[1]->fifoWrite(0x00000080);
			}

		}
	}
};


#endif //__TINY_H__
