#ifndef __PIXEL_ARRAY_H__
#define __PIXEL_ARRAY_H__



#include <Adafruit_NeoPixel.h>
#include "color.h"



extern color_t pix_colorz[7];
extern color_t pix_colorx[7];



#define GRID_WIDTH	16
#define GRID_HEIGHT	16




class pixelArray : public Adafruit_NeoPixel {
public:
	pixelArray(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800)
		: Adafruit_NeoPixel(n, p, t) {}


	static int16_t index(int8_t x, int8_t y) {
		if (x < 0  ||  x >= GRID_WIDTH  ||  y < 0  ||  y >= GRID_HEIGHT) return -1;
		uint16_t pos = ((GRID_HEIGHT-1)-y) * GRID_WIDTH;
		return (y & 0x01) ? (pos + ((GRID_WIDTH-1) - x)) : (pos + x);

//		return	  (((GRID_HEIGHT-1)-y) * GRID_WIDTH)		// Y calculation
//				+ (((GRID_WIDTH-1) * (y & 0x01)) - x);		// X calculation
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
};



#endif //__PIXEL_ARRAY_H__
