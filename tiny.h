#ifndef __TINY_H__
#define __TINY_H__



#include "defines.h"



class tiny : public spidergame {
public:
	virtual void frame(pixelArray **strip, WII **wii) {
		for (int i=0; i<PLAYERS; i++) {
			if (!wii[i]->wiimoteConnected) continue;

			if (wii[i]->getButtonClick(ONE)) {
				LED_LEFT.fifoWrite(0x0110);
			}

			if (wii[i]->getButtonClick(TWO)) {
				LED_LEFT.fifoWrite(0x0111);
			}
		}
	}
};


#endif //__TINY_H__
