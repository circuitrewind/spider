#ifndef __TETRIS_H__
#define __TETRIS_H__



#include "defines.h"
#include "pieces.h"


#define TETRIS_WIDTH		10
#define TETRIS_HEIGHT		16
#define TETRIS_INDEX(x,y)	grid[((y)*TETRIS_WIDTH)+(x)]



class tetris : public animation {
public:
	tetris() {
		elapsed = 0;
		memset(grid, 0, sizeof(grid));
		newPiece();
	}


	void newPiece() {
		piece_x = 5;
		piece_y = 0;
		piece_r = 0;
		piece_i = random(0,7);
	}


	void lines();

	void clear(int line);


	void draw_piece(pixelArray *strip, uint8_t index, uint8_t rotation);

	bool collision(int x_offset, int y_offset, uint8_t index, uint8_t rotation);

	void lock(int x_offset, int y_offset, uint8_t index, uint8_t rotation);

	virtual void frame(pixelArray **strip, WII **wii);


private:

	uint8_t grid[TETRIS_WIDTH * TETRIS_HEIGHT];

	int		piece_x;
	int		piece_y;
	uint8_t	piece_r;
	uint8_t	piece_i;
};


#endif //__TETRIS_H__
