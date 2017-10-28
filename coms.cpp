#if defined ARDUINO_attiny || defined ARDUINO_AVR_DIGISPARK



#include "defines.h"
#include "coms.h"



uint16_b coms::process() {
	pinMode(this->_miso,	OUTPUT);
	pinMode(this->_mosi,	INPUT);
	pinMode(this->_clk,		INPUT);
	pinMode(this->_ss,		INPUT);

	uint16_t	data = 0;
	uint8_t		bits = 0;

	this->miso(1);

	while (!this->ss()) {
		while (!this->clk()) {
			if (this->ss()) goto output;
		}

		data = (data << 1) | this->mosi();

		if (++bits == 16) goto output;

		while (this->clk()) {
			if (this->ss()) goto output;
		}
	}

	output:

	this->miso(0);
	pinMode(this->_miso,	INPUT);

	return (bits == 16) ? data : uint16_b::fill();
}




#endif //ARDUINO_attiny || ARDUINO_AVR_DIGISPARK
