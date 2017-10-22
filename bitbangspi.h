#ifndef __BITBANG_SPI_H__
#define __BITBANG_SPI_H__




class BitBangedSPI {
public:
	BitBangedSPI() : pulseWidth(0) {}

	void begin() {
		digitalWrite(PIN_SCK, LOW);
		digitalWrite(PIN_MOSI, LOW);
		pinMode(PIN_SCK, OUTPUT);
		pinMode(PIN_MOSI, OUTPUT);
		pinMode(PIN_MISO, INPUT);
	}

	void beginTransaction(uint32_t clock) {
		pulseWidth = (500000 + clock - 1) / clock;
		if (pulseWidth == 0) pulseWidth = 1;
	}

	void end() {}

	uint8_t transfer (uint8_t b) {
		for (unsigned int i = 0; i < 8; ++i) {
			digitalWrite(PIN_MOSI, (b & 0x80) ? HIGH : LOW);
			digitalWrite(PIN_SCK, HIGH);
			delayMicroseconds(pulseWidth);
			b = (b << 1) | digitalRead(PIN_MISO);
			digitalWrite(PIN_SCK, LOW); // slow pulse
			delayMicroseconds(pulseWidth);
		}
		return b;
	}

private:
	unsigned long pulseWidth; // in microseconds
};




#endif //__BITBANG_SPI_H__
