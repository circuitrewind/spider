#ifndef __spider_games_h__
#define __spider_games_h__




//TODO: Have spidergame inherit from animation library
//		OR - just entirely replace this WITH the animation library!?
class spidergame {
public:
	spidergame() {}
	virtual ~spidergame() {}

	virtual void loop( pixelArray **strip, WII **wii) {}
	virtual void frame(pixelArray **strip, WII **wii) {}

	INLINE void reset() { elapsed = 0; }

protected:
	elapsedMillis elapsed;
};


extern spidergame *game;



#endif //__spider_games_h__
