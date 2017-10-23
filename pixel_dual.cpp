#ifdef TEENSYDUINO



#include "defines.h"
#include "pixel_dual.h"
#include "pixel_font.h"




color_t pixelDual::swap(int8_t x, int8_t y, color_t color) {
	int16_t pos = index(x, y);
	if (pos == -1) return color_t::black();
	color_t ret = getPixelColor(pos);
	setPixelColor(pos, color);
	return ret;
}




void pixelDual::string(const char *text, int8_t x_offset, int8_t y_offset, color_t color) {
	while (*text) {

		if (*text < 0x21) {
			x_offset += 3;
			text++;
			continue;
		}


		char index = (*text > 0x7E) ? 0x7F : *text;
		character item = pixelfont[index - 0x21];
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




#endif //TEENSYDUINO
