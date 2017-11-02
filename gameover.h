#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__



#include "defines.h"
#include "fadeout.h"



class gameover : public fadeout {
public:
	gameover(uint8_t grid) : fadeout(grid) {}

	virtual void frame(pixelArray **strip, WII **wii) {
		fadeout::frame(strip, wii);

		strip[player]->string("D",  4, GRID_HEIGHT - 20, color_t::red());
		strip[player]->string("E",  4, GRID_HEIGHT - 15, color_t::green());
		strip[player]->string("A",  4, GRID_HEIGHT - 10, color_t::blue());
		strip[player]->string("D",  4, GRID_HEIGHT -  5, color_t::yellow());
	}
};


#endif //__GAMEOVER_H__
