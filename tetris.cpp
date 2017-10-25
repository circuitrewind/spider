#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO




#include "defines.h"
#include "tetris.h"




////////////////////////////////////////////////////////////////////////////////
//DRAW A TETRIS PIECE TO THE PIXEL ARRAY
////////////////////////////////////////////////////////////////////////////////
void tetris::draw_piece(pixelArray *strip, uint8_t index, uint8_t rotation) {
	uint16_t	data	= pieces[index].shape[rotation];
	uint32_t	bit		= 1;

	for (int y=0; y<4; y++) {
		for (int x=0; x<4; x++) {

			if (data & bit) {
				strip->draw(
					x + piece_x,
					y + piece_y,
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
bool tetris::collision(int x_offset, int y_offset, uint8_t index, uint8_t rotation) {
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
//LOCK A PIECE ONTO THE TETRIS GRID
////////////////////////////////////////////////////////////////////////////////
void tetris::lock(int x_offset, int y_offset, uint8_t index, uint8_t rotation) {
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

	newPiece();
}




////////////////////////////////////////////////////////////////////////////////
//CHECK FOR LINES THAT CAN BE CLEARED
////////////////////////////////////////////////////////////////////////////////
void tetris::lines() {
	for (int y=TETRIS_HEIGHT-1; y>=0; y--) {
		for (int x=0; x<TETRIS_WIDTH; x++) {
			if (!TETRIS_INDEX(x,y)) {
				x = TETRIS_WIDTH; continue;
			}
			if (x == TETRIS_WIDTH - 1) {
				clear(y);
				y++;
			}
		}
	}
}




////////////////////////////////////////////////////////////////////////////////
//CLEAR A LINE FROM THE GRID
////////////////////////////////////////////////////////////////////////////////
void tetris::clear(int line) {
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
//THE MAIN TETRIS RENDER LOOP
////////////////////////////////////////////////////////////////////////////////
void tetris::frame(pixelArray **strip, WII **wii) {
	strip[0]->clear();


	//DRAW THE LOCKED TETRIS PIECES
	for (int y=0; y<TETRIS_HEIGHT; y++) {
		for (int x=0; x<TETRIS_WIDTH; x++) {
			uint8_t pixel = TETRIS_INDEX(x, y);
			if (pixel) strip[0]->draw(x, y, pieces[pixel-1].color);
		}
	}


	//MOVE LEFT / RIGHT
	if (wii[0]->getButtonClick(UP)) {
		if (!collision(piece_x-1, piece_y, piece_i, piece_r)) {
			piece_x--;
		}

	} else if (wii[0]->getButtonClick(DOWN)) {
		if (!collision(piece_x+1, piece_y, piece_i, piece_r)) {
			piece_x++;
		}
	}


	//MOVE DOWN FASTER / INSTA-DROP
	if (wii[0]->getButtonClick(LEFT)) {
		elapsed = 500;
	}


	//ROTATION RIGHT / LEFT
	if (wii[0]->getButtonClick(TWO)) {
		uint8_t rotate = (piece_r + 1) & 0x03;
		if (!collision(piece_x, piece_y, piece_i, rotate)) {
			piece_r = rotate;
		}

	} else if (wii[0]->getButtonClick(ONE)) {
		uint8_t rotate = (piece_r - 1) & 0x03;
		if (!collision(piece_x, piece_y, piece_i, rotate)) {
			piece_r = rotate;
		}
	}


	//TIMER FOR PIECE DROPPING
	if (elapsed >= 500) {
		elapsed -= 500;

		if (collision(piece_x, piece_y+1, piece_i, piece_r)) {
			lock(piece_x, piece_y, piece_i, piece_r);
			lines();
		} else {
			piece_y++;
		}
	}


	//DRAW CURRENT PIECE
	draw_piece(strip[0], piece_i, piece_r);
}



#endif //TEENSYDUINO || defined ARDUINO_AVR_NANO
