#ifndef __spider_games_h__
#define __spider_games_h__


#include <elapsedMillis.h>
#include <Wii.h>


#define PLAYERS 4



class spidergame {
public:
	spidergame() {}
	virtual ~spidergame() {}

	virtual void loop(pixelArray *strip, WII **wii) {}

protected:
	elapsedMillis elapsed;
};


extern spidergame *game;



#endif //__spider_games_h__
