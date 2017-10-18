#include "host.h"


void host::reset() {
	memset(buffer, 0, sizeof(buffer));
	offset = 0;
}


void host::loop(pixelArray *strip, WII **wii) {
	while (Serial.available()) {

		//COMPLETELY RESET IF WE OVERFLOW THE BUFFER
		if (offset >= sizeof(buffer)) return reset();

		buffer[offset] = Serial.read();

		//FLOOD WITH ZEROS TO RESET BUFFER
		switch (buffer[offset]) {
			case '\0':
			case '\r':
			case '\n':
			case ';':
				Serial.print("Command: ");
				if (offset) {
					int start=0, end=0, red=0, green=0, blue=0;
					sscanf(
						(char*)buffer,
						"%d,%d=%d,%d,%d",
						&start,	&end,
						&red,	&green,	&blue
					);

					start	= min(max(start,   0), 299);
					end		= min(max(start, end), 299);

					color_t	color = color_t(red, green, blue);

					Serial.print(start);
					Serial.print(", ");
					Serial.print(end);
					Serial.print(" = ");
					Serial.print(color);
					Serial.print("\n");

					for (int i=start; i<=end; i++) {
						strip->setPixelColor(i, color);
					}
				} else {
					Serial.print("[NONE]\n");
				}
				reset();
			continue;
		}

		offset++;
	}
}
