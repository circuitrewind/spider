#ifndef __spider_games_h__
#define __spider_games_h__


#ifdef TEENSYDUINO
#include <Wii.h>
#define PLAYERS 4
#else //ARDUINO_AVR_NANO
#include "wiipad.h"
#define PLAYERS 1
#endif //TEENSYDUINO/ARDUINO_AVR_NANO





class spidergame {
public:
	spidergame() {}
	virtual ~spidergame() {}

	virtual void loop( pixelArray **strip, WII **wii) {}
	virtual void frame(pixelArray **strip, WII **wii) {}

protected:
	elapsedMillis elapsed;
};


extern spidergame *game;



#endif //__spider_games_h__
