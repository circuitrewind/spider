#if defined ARDUINO_attiny || defined ARDUINO_AVR_DIGISPARK



#include "defines.h"
#include "coms.h"



uint32_b coms::process() {
	pinMode(this->_miso,	OUTPUT);
	pinMode(this->_mosi,	INPUT);
	pinMode(this->_clk,		INPUT);
	pinMode(this->_ss,		INPUT);

	uint32_b	data;
	uint8_t		bits = 31;

	this->miso(1);

	while (!this->ss()) {
		while (!this->clk()) {
			if (this->ss()) goto output;
		}

		data.shift(bits, this->mosi());

		if (--bits == 0) goto output;

		while (this->clk()) {
			if (this->ss()) goto output;
		}
	}

	output:

	this->miso(0);
	pinMode(this->_miso,	INPUT);

	return (bits == 0) ? data : uint32_b::fill();
}




#endif //ARDUINO_attiny || ARDUINO_AVR_DIGISPARK
