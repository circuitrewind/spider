#include "coms.h"



uint16_b coms::process() {
	uint16_t	data = 0;
	uint8_t		bits = 0;

	while (this->ss() == HIGH) {
		while (this->clk() == HIGH) {
			if (this->ss() != HIGH) return uint16_b::fill();
		}

		data = (data << 1) | (this->mosi() == HIGH);

		if (++bits == 16) return data;

		while (this->clk() == LOW) {
			if (this->ss() != HIGH) return uint16_b::fill();
		}

	}

	return uint16_b::fill();
}
