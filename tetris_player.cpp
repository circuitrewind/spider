#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO




#include "defines.h"
#include "tetris.h"
#include "tetris_clear.h"
#include "gameover.h"




////////////////////////////////////////////////////////////////////////////////
//DRAW A TETRIS PIECE TO THE PIXEL ARRAY
////////////////////////////////////////////////////////////////////////////////
void tetris_player::draw_piece(pixelArray *strip, uint8_t index, uint8_t rotation) {
	uint16_t	data	= pieces[index].shape[rotation];
	uint32_t	bit		= 1;

	for (int y=0; y<4; y++) {
		for (int x=0; x<4; x++) {

			if (data & bit) {
				strip->draw(
					x + piece_x + align_x(),
					y + piece_y + align_y(),
					pieces[index].color
				);
			}

			bit <<= ((uint32_t)1);
		}
	}
}




////////////////////////////////////////////////////////////////////////////////
//CHECK IF COLLISION WOULD HAPPEN FOR A GIVEN PEICE/ROTATION/LOCATION
////////////////////////////////////////////////////////////////////////////////
bool tetris_player::collision(int x_offset, int y_offset, uint8_t index, uint8_t rotation) {
	uint16_t	data	= pieces[index].shape[rotation];
	uint32_t	bit		= 1;

	for (int y=0; y<4; y++) {
		for (int x=0; x<4; x++) {

			if (data & bit) {
				if (x + x_offset < 0) {
					return true;
				}

				if (y + y_offset < 0) {
					return true;
				}

				if (x + x_offset >= TETRIS_WIDTH) {
					return true;
				}

				if (y + y_offset >= TETRIS_HEIGHT) {
					return true;
				}

				if (TETRIS_INDEX(x + x_offset, y + y_offset)) {
					return true;
				}
			}

			bit <<= ((uint32_t)1);
		}
	}

	return false;
}




////////////////////////////////////////////////////////////////////////////////
//GENERATE A NEW RANDOM PIECE AND CHECK FOR GAME OVER
////////////////////////////////////////////////////////////////////////////////
void tetris_player::new_piece() {
	piece_x = 3;
	piece_y = 0;
	piece_r = 0;
	piece_i = random(1, 7);

	if (collision(piece_x, piece_y, piece_i, piece_r)) {
		parent->player[0]->pause(true);
		parent->player[1]->pause(true);
		new gameover(player);
	} else {
		ledstrip[player]->fifoWrite(
			0x060000L | ((uint16_t)pieces[piece_i].color)
		);
	}
}



////////////////////////////////////////////////////////////////////////////////
//LOCK A PIECE ONTO THE TETRIS GRID
////////////////////////////////////////////////////////////////////////////////
void tetris_player::lock(int x_offset, int y_offset, uint8_t index, uint8_t rotation) {
	uint16_t	data	= pieces[index].shape[rotation];
	uint32_t	bit		= 1;

	for (int y=0; y<4; y++) {
		for (int x=0; x<4; x++) {
			if (data & bit) {
				TETRIS_INDEX(x + x_offset, y + y_offset) = index+1;
			}
			bit <<= ((uint32_t)1);
		}
	}

	if (stack) {
		for (int y=0; y<TETRIS_HEIGHT; y++) {
			for (int x=0; x<TETRIS_WIDTH; x++) {
				if (y<TETRIS_HEIGHT-stack) {
					TETRIS_INDEX(x,y) = TETRIS_INDEX(x,y+stack);
				} else {
					TETRIS_INDEX(x,y) = 1;
				}
			}
		}
	}

	new_piece();
}




////////////////////////////////////////////////////////////////////////////////
//CHECK FOR LINES THAT CAN BE CLEARED
////////////////////////////////////////////////////////////////////////////////
bool tetris_player::lines() {
	uint32_t	cleared	= 0;
	uint8_t		total	= 0;

	for (int y=TETRIS_HEIGHT-1; y>=0; y--) {
		for (int x=0; x<TETRIS_WIDTH; x++) {
			if (!TETRIS_INDEX(x,y)) {
				x = TETRIS_WIDTH; continue;
			}
			if (x == TETRIS_WIDTH - 1) {
				cleared |= 1L << y;
				total++;
			}
		}
	}

	if (total > 0) {
		new tetris_clear(this, cleared);
	}

	if (total > 1) {
		parent->player[player==1?0:1]->stack += total -1;
	}

	return total;
}




////////////////////////////////////////////////////////////////////////////////
//CLEAR A LINE FROM THE GRID
////////////////////////////////////////////////////////////////////////////////
void tetris_player::clear(int line) {
	for (int y=line; y>0; y--) {
		for (int x=0; x<TETRIS_WIDTH; x++) {
			TETRIS_INDEX(x,y) = TETRIS_INDEX(x,y-1);
		}
	}

	for (int x=0; x<TETRIS_WIDTH; x++) {
		TETRIS_INDEX(x,0) = 0;
	}
}




////////////////////////////////////////////////////////////////////////////////
//REDRAW THE GRID
////////////////////////////////////////////////////////////////////////////////
void tetris_player::draw_grid(pixelArray *strip) {
	strip->clear();


	//DRAW THE LOCKED TETRIS PIECES
	for (int y=0; y<TETRIS_HEIGHT; y++) {
		for (int x=0; x<TETRIS_WIDTH; x++) {
			uint8_t pixel = TETRIS_INDEX(x, y);
			if (pixel) {
				strip->draw(
					x + align_x(),
					y + align_y(),
					pieces[pixel-1].color
				);
			}
		}
	}
}




////////////////////////////////////////////////////////////////////////////////
//THE MAIN TETRIS RENDER LOOP
////////////////////////////////////////////////////////////////////////////////
void tetris_player::frame(pixelArray **strip, WII **wii) {
	draw_grid(strip[player]);


	//MOVE LEFT / RIGHT
	if (wii[player]->getButtonClick(UP)) {
		if (!collision(piece_x-1, piece_y, piece_i, piece_r)) {
			piece_x--;
		}

	} else if (wii[player]->getButtonClick(DOWN)) {
		if (!collision(piece_x+1, piece_y, piece_i, piece_r)) {
			piece_x++;
		}
	}


	//MOVE DOWN FASTER / INSTA-DROP
	if (wii[player]->getButtonClick(LEFT)) {
		elapsed = 500;
	}


	//ROTATION RIGHT / LEFT
	if (wii[player]->getButtonClick(TWO)) {
		uint8_t rotate = (piece_r + 1) & 0x03;
		if (!collision(piece_x, piece_y, piece_i, rotate)) {
			piece_r = rotate;
		}

	} else if (wii[player]->getButtonClick(ONE)) {
		uint8_t rotate = (piece_r - 1) & 0x03;
		if (!collision(piece_x, piece_y, piece_i, rotate)) {
			piece_r = rotate;
		}
	}


	//TIMER FOR PIECE DROPPING
	bool clear_lines = false;
	if (elapsed >= 500) {
		elapsed -= 500;

		if (collision(piece_x, piece_y+1, piece_i, piece_r)) {
			lock(piece_x, piece_y, piece_i, piece_r);
			clear_lines = lines();
		} else {
			piece_y++;
		}
	}


	//DRAW CURRENT PIECE
	if (clear_lines) {
		draw_grid(strip[player]);
	} else {
		draw_piece(strip[player], piece_i, piece_r);
	}
}



#endif //TEENSYDUINO || defined ARDUINO_AVR_NANO
