#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



#include "defines.h"
#include "pixel_array.h"
#include "pixel_font.h"




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
