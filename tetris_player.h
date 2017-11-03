#ifndef __TETRIS_PLAYER_H__
#define __TETRIS_PLAYER_H__



#include "defines.h"
#include "tetris_pieces.h"


#define TETRIS_WIDTH		10
#define TETRIS_HEIGHT		16
#define TETRIS_INDEX(x,y)	grid[((y)*TETRIS_WIDTH)+(x)]


class tetris;


class tetris_player : public animation {
public:
	tetris_player(uint8_t id, tetris *par) {
		pixelArray::animation(PR_BOTTOM_ANIM);

		parent		= par;
		elapsed		= 0;
		stack		= 0;
		player		= id;
		memset(grid, 0, sizeof(grid));

		ledstrip[player]->fifoWrite(0x010003L);

		new_piece();
	}


	INLINE int align_x() const { return 1; }
	INLINE int align_y() const { return 7; }
	INLINE uint8_t id()  const { return player; }


	void new_piece();


	bool lines();

	void clear(int line);

	void draw_grid(pixelArray *strip);

	void draw_piece(pixelArray *strip, uint8_t index, uint8_t rotation);

	bool collision(int x_offset, int y_offset, uint8_t index, uint8_t rotation);

	void lock(int x_offset, int y_offset, uint8_t index, uint8_t rotation);

	virtual void frame(pixelArray **strip, WII **wii);


private:
	uint8_t player;

	uint8_t grid[TETRIS_WIDTH * TETRIS_HEIGHT];

	tetris		*parent;

	int			piece_x;
	int			piece_y;
	uint8_t		piece_r;
	uint8_t		piece_i;
	uint16_t	stack;
};




#endif //__TETRIS_PLAYER_H__
