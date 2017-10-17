#ifndef __spider_games_h__
#define __spider_games_h__


#include <Adafruit_NeoPixel.h>
#include <elapsedMillis.h>
#include <Wii.h>
#include "pixelfont.h"


#define PLAYERS 4

#define GRID_WIDTH	16
#define GRID_HEIGHT	16


#ifndef INLINE
#define INLINE	inline __attribute__ ((always_inline))
#endif //INLINE


#define RGB(r, g, b) (						\
	((((uint32_t)(r)) & 0xFF) << 16)	|	\
	((((uint32_t)(g)) & 0xFF) <<  8)	|	\
	( ((uint32_t)(b)) & 0xFF)				\
)


extern uint32_t pix_colorz[7];
extern uint32_t pix_colorx[7];


class pixelArray : public Adafruit_NeoPixel {
public:
	pixelArray(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800)
		: Adafruit_NeoPixel(n, p, t) {}


	INLINE static int16_t index(int8_t x, int8_t y) {
		if (x < 0  ||  x >= GRID_WIDTH  ||  y < 0  ||  y >= GRID_HEIGHT) return -1;
		uint16_t pos = ((GRID_HEIGHT-1)-y) * GRID_WIDTH;
		return (y & 0x01) ? (pos + ((GRID_WIDTH-1) - x)) : (pos + x);

//		return	  (((GRID_HEIGHT-1)-y) * GRID_WIDTH)		// Y calculation
//				+ (((GRID_WIDTH-1) * (y & 0x01)) - x);		// X calculation
	}


	INLINE void draw(int8_t x, int8_t y, uint32_t color) {
		int16_t pos = index(x, y);
		if (pos != -1) setPixelColor(pos, color);
	}


	INLINE uint32_t read(int8_t x, int8_t y) const {
		int16_t pos = index(x, y);
		return (pos != -1) ? getPixelColor(pos) : RGB(0,0,0);
	}


	uint32_t swap(int8_t x, int8_t y, uint32_t color);


	INLINE void symbol(uint8_t c, int8_t x, int8_t y, uint32_t color) {
		const char z[2] = {c, 0};
		string(z, x, y, color);
	}


	void string(const char *text, int8_t x_offset, int8_t y_offset, uint32_t color);
	static uint16_t stringWidth(const char *text);
};




class spiderGame {
public:
	virtual void loop(pixelArray *strip, WII **wii) {}
	virtual ~spiderGame() {}

protected:
	elapsedMillis elapsed;
};


extern spiderGame *game;




class spiderBootscreen : public spiderGame {
public:
	spiderBootscreen(bool loaded=false) :
		x_offset(GRID_WIDTH),
		loaded(loaded) {}

	virtual void loop(pixelArray *strip, WII **wii);

private:
	int16_t	x_offset;
	bool	loaded;
};




class spiderPaint : public spiderGame {
public:
	spiderPaint() {
		connected		= false;
		for (int i=0; i<PLAYERS; i++) {
			pix_x[i]		= 7;
			pix_y[i]		= i+8;
			pix_z[i]		= 0;
			pix_c[i]		= pix_colorz[i+1];
			pix_cycle[i]	= i+1;
		}
	}

	virtual void loop(pixelArray *strip, WII **wii);

	bool		connected;
	int8_t		pix_x[PLAYERS];
	int8_t		pix_y[PLAYERS];
	uint32_t	pix_z[PLAYERS];
	uint32_t	pix_c[PLAYERS];
	int8_t		pix_cycle[PLAYERS];
};




class spiderDecay : public spiderGame {
	virtual void loop(pixelArray *strip, WII **wii);
};




#endif //__spider_games_h__
