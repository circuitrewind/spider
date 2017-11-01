#ifndef __PONG_H__
#define __PONG_H__



#include "defines.h"



class pong : public animation {
public:
	pong() {
		fade = 4;

		ball_x = (float)(GRID_WIDTH  / 2);
		ball_y = (float)(GRID_HEIGHT / 2);

		rate_x = random_speed();
		rate_y = random_speed();


		random_color();
	}


	INLINE void random_color() {
		color = pix_colorx[
			random(0, 7)
		];
	}


	INLINE float random_speed() {
		return ((float)random(300, 700)) / ((float)1000);
	}



	virtual void frame(pixelArray **strip, WII **wii) {
		uint8_t *data;

		data = (uint8_t*) strip[0]->getPixels();
		for (uint16_t i=0; i<GRID_TOTAL*3; i++) {
			if (data[i] > 64) {
				data[i] >>= 1;
			} else if (data[i] > fade) {
				data[i] -= fade;
			} else {
				data[i] = 0;
			}
		}


		//MOVE BALL ON X AXIS
		ball_x += rate_x;
		if (((int)ball_x) >= GRID_WIDTH) {
			ball_x = (float)(GRID_WIDTH-1);
			rate_x = -random_speed();
			random_color();
		} else if (ball_x <= 0) {
			ball_x = 0;
			rate_x = random_speed();
			random_color();
		}


		//MOVE BALL ON Y AXIS
		ball_y += rate_y;
		if (((int)ball_y) >= GRID_HEIGHT) {
			ball_y = (float)(GRID_HEIGHT-1);
			rate_y = -random_speed();
			random_color();
		} else if (ball_y <= 0) {
			ball_y = 0;
			rate_y = random_speed();
			random_color();
		}



		strip[0]->draw((int)ball_x, (int)ball_y, color);
	}


private:
	uint8_t fade;

	float ball_x;
	float ball_y;
	float rate_x;
	float rate_y;

	color_t color;
};


#endif //__PONG_H__
