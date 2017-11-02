#ifndef __TETRIS_H__
#define __TETRIS_H__



#include "defines.h"
#include "tetris_player.h"



#define TETRIS_WIDTH		10
#define TETRIS_HEIGHT		16
#define TETRIS_INDEX(x,y)	grid[((y)*TETRIS_WIDTH)+(x)]



class tetris : public animation {
	friend class tetris_player;

public:
	tetris() {
		player[0] = new tetris_player(0, this);
		player[1] = new tetris_player(1, this);
	}

private:
	tetris_player *player[2];
};




#endif //__TETRIS_H__
