#if defined TEENSYDUINO || defined ARDUINO_AVR_NANO



#include "defines.h"
#include "host.h"


void host::reset() {
	memset(buffer, 0, sizeof(buffer));
	offset = 0;
}


void host::frame(pixelArray **strip, WII **wii) {
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
				Serial.print(F("Command: "));
				if (offset) {
					int side=0, start=0, end=0, red=0, green=0, blue=0;
					sscanf(
						(char*)buffer,
						"%d,%d,%d=%d,%d,%d",
						&side,	&start,	&end,
						&red,	&green,	&blue
					);

					start	= min(max(start,   0), 299);
					end		= min(max(start, end), 299);

					color_t	color = color_t(red, green, blue);

					Serial.print(side);
					Serial.print(F(", "));
					Serial.print(start);
					Serial.print(F(", "));
					Serial.print(end);
					Serial.print(F(" = "));
					Serial.print((uint32_t)color);
					Serial.print(F("\n"));

					for (int i=start; i<=end; i++) {
						strip[side]->setPixelColor(i, color);
					}
				} else {
					Serial.print(F("[NONE]\n"));
				}
				reset();
			continue;
		}

		offset++;
	}
}




#endif //TEENSYDUINO || ARDUINO_AVR_NANO
