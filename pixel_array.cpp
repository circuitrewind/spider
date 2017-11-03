#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



#include "defines.h"
#include "pixel_array.h"
#include "pixel_font.h"




const color_t pix_colorx[10] = {
	color_t(255,   0,   0),
	color_t( 0,  255,   0),
	color_t( 0,    0, 255),
	color_t( 0,  255, 255),
	color_t(255,   0, 255),

	color_t(255, 255,   0),
	color_t(255,  64,   0),
	color_t(0,   255,  64),
	color_t(64,    0, 255),
	color_t(100, 100, 255),
};




uint8_t			pixelArray::color_offset	= 0;
PIXEL_RAINBOW	pixelArray::color_anim		= PR_LEFT;
color_t			pixelArray::color_palette[GRID_MAX];




#ifdef TEENSYDUINO
void pixelArray::show() {
	this->begin();
	for (int y=height()-1; y>=0; y--) {
		uint16_t	row = layout[y];
		uint16_t	set = y * width();
		for (int x=0; x<width(); x++) {
			if (row & (1<<x)) {
				if (y & 0x01) {
					pixel(grid[set + ((width() - 1) - x)]);
				} else {
					pixel(grid[set + x]);
				}
			}
		}
	}
	this->end();
}
#endif //TEENSYDUINO




#ifdef ARDUINO_AVR_NANO
void pixelArray::show() {
	this->begin();
	for (int y=height()-1; y>=0; y--) {
		uint16_t	row = layout[y];
		uint16_t	set = y * width();
		for (int x=width(); x>=0; x--) {
			if (row & (1<<x)) {
				if (y & 0x01) {
					pixel(grid[set + x]);
				} else {
					pixel(grid[set + ((width() - 1) - x)]);
				}
			}
		}
	}
	this->end();
}
#endif //ARDUINO_AVR_NANO




void pixelArray::draw(int8_t x, int8_t y) {
	int16_t pos = index(x, y);
	if (pos == -1) return;

	switch (color_anim) {
		case PR_LEFT:
		case PR_RIGHT:
		case PR_LEFT_ANIM:
		case PR_RIGHT_ANIM:
			setPixelColor(pos, color_palette[x]);
			break;

		case PR_TOP:
		case PR_TOP_ANIM:
		case PR_BOTTOM:
		case PR_BOTTOM_ANIM:
			setPixelColor(pos, color_palette[y]);
			break;

		case PR_TOP_LEFT:
		case PR_TOP_LEFT_ANIM:
		case PR_BOTTOM_RIGHT:
		case PR_BOTTOM_RIGHT_ANIM:
			setPixelColor(pos, color_palette[x+y]);
			break;

		case PR_TOP_RIGHT:
		case PR_TOP_RIGHT_ANIM:
		case PR_BOTTOM_LEFT:
		case PR_BOTTOM_LEFT_ANIM:
			setPixelColor(pos, color_palette[(GRID_WIDTH-x)+y]);
			break;

		default: //DO NOTHING
			break;
	}
}




color_t pixelArray::swap(int8_t x, int8_t y, color_t color) {
	int16_t pos = index(x, y);
	if (pos == -1) return color_t::black();
	color_t ret = getPixelColor(pos);
	setPixelColor(pos, color);
	return ret;
}




void pixelArray::string(const char *_text, int16_t x_offset, int16_t y_offset) {
	const uint8_t *text = (const uint8_t *) _text;

	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		uint8_t index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

		#ifdef ARDUINO_AVR_NANO
			character item = PROGMEM_getAnything(&pixelfont[index]);
		#else
			character item = pixelfont[index];
		#endif

		for (int x=0; x<item.width; x++) {
			uint8_t column = item.data[x];

			for (int y=0; y<6; y++) {
				if (column & (1<<y)) {
					draw(x+x_offset, y+y_offset);
				}
			}
		}

		x_offset += item.width + 1;
		text++;
	}
}




void pixelArray::string(const char *_text, int16_t x_offset, int16_t y_offset, color_t color) {
	const uint8_t *text = (const uint8_t *) _text;

	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		uint8_t index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

		#ifdef ARDUINO_AVR_NANO
			character item = PROGMEM_getAnything(&pixelfont[index]);
		#else
			character item = pixelfont[index];
		#endif

		for (int x=0; x<item.width; x++) {
			uint8_t column = item.data[x];

			for (int y=0; y<6; y++) {
				if (column & (1<<y)) {
					draw(x+x_offset, y+y_offset, color);
				}
			}
		}

		x_offset += item.width + 1;
		text++;
	}
}




int16_t pixelArray::stringWidth(const char *_text) {
	const uint8_t *text = (const uint8_t *) _text;

	int16_t x_offset = 0;
	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		uint8_t index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

		#ifdef ARDUINO_AVR_NANO
			character item = PROGMEM_getAnything(&pixelfont[index]);
		#else
			character item = pixelfont[index];
		#endif

		x_offset += item.width + 1;
		text++;
	}

	return x_offset;
}




void pixelArray::increment() {
	int16_t	total	= 0;
	int16_t	cycle	= 0;
	bool	dir		= false;


	//FIGURE OUT WHICH BASE ANIMATION WE'RE USING
	switch (color_anim) {
		case PR_NONE:
			return;

		case PR_BOTTOM:
		case PR_BOTTOM_ANIM:
			dir = true;
			//no break
		case PR_TOP:
		case PR_TOP_ANIM:
			total = GRID_HEIGHT;
			break;

		case PR_RIGHT:
		case PR_RIGHT_ANIM:
			dir = true;
			//no break
		case PR_LEFT:
		case PR_LEFT_ANIM:
			total = GRID_WIDTH;
			break;

		case PR_BOTTOM_LEFT:
		case PR_BOTTOM_LEFT_ANIM:
			dir = true;
			//no break;
		case PR_TOP_RIGHT:
		case PR_TOP_RIGHT_ANIM:
			total = GRID_WIDTH + GRID_HEIGHT - 1;
			break;

		case PR_TOP_LEFT:
		case PR_TOP_LEFT_ANIM:
			dir = true;
			//no break
		case PR_BOTTOM_RIGHT:
		case PR_BOTTOM_RIGHT_ANIM:
			total = GRID_WIDTH + GRID_HEIGHT - 1;
			break;
	}


	//IF INVALID ANIMATION SELECTED, DON'T WASTE CPU CYCLES!
	if (!total) return;


	//CHECK IF WE'RE DOING PALLETE ANIMATION OR NOT
	switch (color_anim) {
		case PR_BOTTOM_ANIM:
		case PR_TOP_ANIM:
		case PR_RIGHT_ANIM:
		case PR_LEFT_ANIM:
		case PR_TOP_RIGHT_ANIM:
		case PR_BOTTOM_RIGHT_ANIM:
		case PR_BOTTOM_LEFT_ANIM:
		case PR_TOP_LEFT_ANIM:
			cycle = ++color_offset;
			break;

		default: //DO NOTHING!
			break;
	}


	//GENERATE AND STORE THE PALLETE TO RAM
	if (dir) {
		for (int i=0; i<total; i++) {
			uint16_t hue = (256*3) / total * (i + cycle);
			color_palette[total-i-1] = color_t::hue(hue % 768);
		}
	} else {
		for (int i=0; i<total; i++) {
			uint16_t hue = (256*3) / total * (i + cycle);
			color_palette[i] = color_t::hue(hue % 768);
		}

	}
}


#endif //TEENSYDUINO || ARDUINO_AVR_NANO
