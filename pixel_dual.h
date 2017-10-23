#ifndef __PIXEL_DUAL_H__
#define __PIXEL_DUAL_H__



#include "pixel_array.h"



class pixelDual {
public:
	pixelDual(uint16_t led_width, uint16_t led_height, pixelArray *left, pixelArray *right)
		:	grid_width( led_width),
			grid_height(led_height),
			grid_total( led_width*led_height),
			grid_left(left),
			grid_right(right) {}




	int16_t index(int8_t x, int8_t y) const {
		if (x >= half()) {
			return grid_right->index(x-half(), y) + total();
		} else {
			return grid_left->index(x, y);
		}
	}



	INLINE void setPixelColor(uint16_t pos, color_t color) {
		if (pos >= total()) return;
		color_t *grid = grid_left->getPixels();
		grid[pos] = color;
	}




	INLINE color_t getPixelColor(uint16_t pos) const {
		if (pos >= total()) return color_t::black();
		color_t *grid = grid_left->getPixels();
		return grid[pos];
	}




	INLINE void draw(int8_t x, int8_t y, color_t color) {
		if (x >= half()) {
			grid_right->draw(x-half(), y, color);
		} else {
			grid_left->draw(x, y, color);
		}
	}




	INLINE color_t read(int8_t x, int8_t y) const {
		if (x >= half()) {
			return grid_right->read(x-half(), y);
		} else {
			return grid_left->read(x, y);
		}
	}




	color_t swap(int8_t x, int8_t y, color_t color);




	INLINE void symbol(uint8_t c, int8_t x, int8_t y, color_t color) {
		const char z[2] = {c, 0};
		string(z, x, y, color);
	}



	INLINE void clear() {
		grid_left->clear();
		grid_right->clear();
	}




	void string(const char *text, int8_t x_offset, int8_t y_offset, color_t color);



	INLINE uint16_t half()		const { return grid_width >> 1;	}
	INLINE uint16_t width()		const { return grid_width;		}
	INLINE uint16_t height()	const { return grid_height;		}
	INLINE uint16_t total()		const { return grid_total;		}




protected:
	const uint16_t	grid_width;
	const uint16_t	grid_height;
	const uint16_t	grid_total;
	pixelArray		*grid_left;
	pixelArray		*grid_right;
};


extern pixelDual *dual;



#endif //__PIXEL_DUAL_H__
