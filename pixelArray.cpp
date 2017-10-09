#include "spidergames.h"




uint32_t pixelArray::swap(int8_t x, int8_t y, uint32_t color) {
	int16_t pos = index(x, y);
	if (pos == -1) return RGB(0,0,0);
	uint32_t ret = getPixelColor(pos);
	setPixelColor(pos, color);
	return ret;
}




void pixelArray::string(const char *text, int8_t x_offset, int8_t y_offset, uint32_t color) {
	while (*text) {

		if (*text < 0x21  ||  *text > 0x7E) {
			x_offset += 3;
			text++;
			continue;
		}

		character item = pixelfont[*text - 0x21];
		for (int x=0; x<item.width; x++) {
			for (int y=0; y<6; y++) {
				if (item.data[x] & (1<<y)) {
					draw(x+x_offset, y+y_offset, color);
				}
			}
		}

		x_offset += item.width + 1;
		text++;
	}
}



uint16_t pixelArray::stringWidth(const char *text) {
	uint16_t x_offset = 0;
	while (*text) {

		if (*text < 0x21  ||  *text > 0x7E) {
			x_offset += 3;
			text++;
			continue;
		}

		character item = pixelfont[*text - 0x21];

		x_offset += item.width + 1;
		text++;
	}

	return x_offset;
}
