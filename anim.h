#ifndef __ANIM_H__
#define __ANIM_H__



#include "defines.h"



class anim : public spidergame {
public:
	anim() {
		reset();
	}


	void reset(int new_mode=0, int new_cycle=0) {
		mode	= new_mode;
		cycle	= new_cycle;
		spidergame::reset();
	}


	virtual void frame(pixelArray **strip, WII **wii);

private:
	int	mode;
	int	cycle;
	int	submode;
};


#endif //__ANIM_H__
