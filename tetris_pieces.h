#ifndef __TETRIS_PIECES_H__
#define __TETRIS_PIECES_H__




struct PACKED piece {
	uint16_t	shape[4];
	color_t		color;
};


extern const piece pieces[8];




#endif //__TETRIS_PIECES_H__
