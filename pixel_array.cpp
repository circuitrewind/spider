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




#ifdef TEENSYDUINO#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



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





color_t pixelArray::swap(int8_t x, int8_t y, color_t color) {
	int16_t pos = index(x, y);
	if (pos == -1) return color_t::black();
	color_t ret = getPixelColor(pos);
	setPixelColor(pos, color);
	return ret;
}




void pixelArray::string(const char *text, int16_t x_offset, int16_t y_offset, PIXEL_RAINBOW rainbow) {
	uint16_t	total	= 0;
	uint8_t		dir		= 0;


	switch (rainbow) {
		case PR_BOTTOM:
		case PR_BOTTOM_ANIM:
			dir = 1;
			//no break
		case PR_TOP:
		case PR_TOP_ANIM:
			total = GRID_HEIGHT;
		break;

		case PR_RIGHT:
		case PR_RIGHT_ANIM:
			dir = 1;
			//no break
		case PR_LEFT:
		case PR_LEFT_ANIM:
			total = GRID_WIDTH;
		break;

		case PR_TOP_RIGHT:
		case PR_BOTTOM_RIGHT:
		case PR_BOTTOM_LEFT:
		case PR_TOP_LEFT:
		case PR_TOP_RIGHT_ANIM:
		case PR_BOTTOM_RIGHT_ANIM:
		case PR_BOTTOM_LEFT_ANIM:
		case PR_TOP_LEFT_ANIM:
			total = GRID_WIDTH + GRID_HEIGHT - 1;
		break;
	}


	color_t colors[total];
	for (int i=0; i<total; i++) {
		colors[i] = color_t::hue((256*3) / total * i);
	}

	color_t color;



	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		char index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

		#ifdef ARDUINO_AVR_NANO
			character item = PROGMEM_getAnything(&pixelfont[index]);
		#else
			character item = pixelfont[index];
		#endif

		for (int x=0; x<item.width; x++) {
			uint8_t x_pixel = x + x_offset;
			if (x_pixel < 0  ||  x_pixel > GRID_WIDTH) continue;

			uint8_t column = item.data[x];

			switch (rainbow) {
				case PR_RIGHT:
				case PR_RIGHT_ANIM:
				case PR_LEFT:
				case PR_LEFT_ANIM:
					color = colors[x_pixel];
			}

			for (int y=0; y<6; y++) {
				uint8_t y_pixel = y + y_offset;
				if (y_pixel < 0  ||  y_pixel > GRID_WIDTH) continue;

				if (column & (1<<y)) {
					switch (rainbow) {
						case PR_BOTTOM:
						case PR_BOTTOM_ANIM:
						case PR_TOP:
						case PR_TOP_ANIM:
							color = colors[y_pixel];
					}

					draw(x_pixel, y_pixel, color);
				}
			}
		}

		x_offset += item.width + 1;
		text++;
	}
}




void pixelArray::string(const char *text, int16_t x_offset, int16_t y_offset, color_t color) {
	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		char index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

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



int16_t pixelArray::stringWidth(const char *text) {
	int16_t x_offset = 0;
	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		char index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

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




#endif //TEENSYDUINO || ARDUINO_AVR_NANO

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





color_t pixelArray::swap(int8_t x, int8_t y, color_t color) {
	int16_t pos = index(x, y);
	if (pos == -1) return color_t::black();
	color_t ret = getPixelColor(pos);
	setPixelColor(pos, color);
	return ret;
}




void pixelArray::string(const char *text, int16_t x_offset, int16_t y_offset) {
	uint16_t segments = (256*3) / GRID_WIDTH;

	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		char index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

		#ifdef ARDUINO_AVR_NANO
			character item = PROGMEM_getAnything(&pixelfont[index]);
		#else
			character item = pixelfont[index];
		#endif

		for (int x=0; x<item.width; x++) {
			uint8_t column = item.data[x];
			color_t color = color_t::hue((x+x_offset) * segments);
			//TODO: support different rainbow animations
			//X speed, Y speed

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




void pixelArray::string(const char *text, int16_t x_offset, int16_t y_offset, color_t color) {
	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		char index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

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



int16_t pixelArray::stringWidth(const char *text) {
	int16_t x_offset = 0;
	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}

		char index = ((*text > 0x7E) ? 0x7F : *text) - 0x21;

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




#endif //TEENSYDUINO || ARDUINO_AVR_NANO
