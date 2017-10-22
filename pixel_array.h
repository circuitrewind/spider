#ifndef __PIXEL_ARRAY_H__
#define __PIXEL_ARRAY_H__



#include "led.h"



extern color_t pix_colorz[7];
extern color_t pix_colorx[7];



#define GRID_WIDTH	12
#define GRID_HEIGHT	23
#define GRID_TOTAL	(GRID_WIDTH*GRID_HEIGHT)




class pixelArray : public ws2812b {
public:
	pixelArray(uint8_t led_pin, const uint16_t *led_layout) :
		ws2812b(led_pin, GRID_TOTAL),
		layout(led_layout) {}


	static int16_t index(int8_t x, int8_t y) {
		if (x < 0  ||  x >= GRID_WIDTH  ||  y < 0  ||  y >= GRID_HEIGHT) return -1;
		return (y * GRID_WIDTH) + x;
//		uint16_t pos = ((GRID_HEIGHT-1)-y) * GRID_WIDTH;
//		return (y & 0x01) ? (pos + ((GRID_WIDTH-1) - x)) : (pos + x);

//		return	  (((GRID_HEIGHT-1)-y) * GRID_WIDTH)		// Y calculation
//				+ (((GRID_WIDTH-1) * (y & 0x01)) - x);		// X calculation
	}


	INLINE void setPixelColor(uint16_t pos, color_t color) {
		if (pos < GRID_TOTAL) grid[pos] = color;
	}


	INLINE color_t getPixelColor(uint16_t pos) const {
		return (pos < GRID_TOTAL) ? grid[pos] : color_t::black();
	}


	INLINE color_t *getPixels() {
		return grid;
	}


	INLINE void draw(int8_t x, int8_t y, color_t color) {
		int16_t pos = index(x, y);
		if (pos != -1) setPixelColor(pos, color);
	}


	INLINE color_t read(int8_t x, int8_t y) const {
		int16_t pos = index(x, y);
		return (pos != -1)
			? color_t(getPixelColor(pos))
			: color_t::black();
	}


	color_t swap(int8_t x, int8_t y, color_t color);


	INLINE void symbol(uint8_t c, int8_t x, int8_t y, color_t color) {
		const char z[2] = {c, 0};
		string(z, x, y, color);
	}


	void string(const char *text, int8_t x_offset, int8_t y_offset, color_t color);
	static uint16_t stringWidth(const char *text);


	void show() {
		this->begin();
		for (int y=GRID_HEIGHT-1; y>=0; y--) {
			uint16_t	row = layout[y];
			int			set = y*GRID_WIDTH;
			for (int x=0; x<GRID_WIDTH; x++) {
				if (row & (1<<x)) {
					if (y & 0x01) {
						pixel(grid[set + ((GRID_WIDTH-1) - x)]);
					} else {
						pixel(grid[set + x]);
					}
				}
			}
		}
		this->end();
	}


	void clear() {
		memset(grid, 0, sizeof(grid));
	}


protected:
	const uint16_t	*layout;
	color_t			grid[GRID_WIDTH * GRID_HEIGHT];
};



#endif //__PIXEL_ARRAY_H__
