#ifndef __spider_games_h__
#define __spider_games_h__


#ifdef TEENSYDUINO
#include <Wii.h>
#else
#include "wiipad.h"
#endif //TEENSYDUINO


#define PLAYERS 4



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
