/*----------------------------------------------------------------------------*\
| SIMPLE STRUCTS/UNIONS FOR SWAPPING BETWEEN BIG AND LITTLE ENDIAN.            |
| ALL SWAPPING IS DONE IN-PLACE, SO NO ADDITIONAL RAM IS NEEDED.               |
| SWAPPING IS DONE VIA 3 INLINED XOR COMMANDS, KEEPING THE CODE                |
| FOOTPRINT VERY SMALL AS WELL.                                                |
\*----------------------------------------------------------------------------*/




#ifndef __binary_h__
#define __binary_h__




////////////////////////////////////////////////////////////////////////////////
// BITFIELD - 8-BIT
////////////////////////////////////////////////////////////////////////////////
union uint8_b {
	INLINE uint8_b()				{ this->byte_0 = 0; }
	INLINE uint8_b(uint8_t byte)	{ this->byte_0 = byte; }

	uint8_t byte_0;

	struct {
		union {
			unsigned int nibble_0		: 4;
			struct {
				unsigned int bit_0		: 1;
				unsigned int bit_1		: 1;
				unsigned int bit_2		: 1;
				unsigned int bit_3		: 1;
			};
		};
		union {
			unsigned int nibble_1		: 4;
			struct {
				unsigned int bit_4		: 1;
				unsigned int bit_5		: 1;
				unsigned int bit_6		: 1;
				unsigned int bit_7		: 1;
			};
		};
	};


	INLINE operator uint8_t() const {
		return this->byte_0;
	}


	INLINE uint8_t operator =(const uint8_t byte) {
		return this->byte_0 = byte;
	}


	INLINE void in(uint8_t bit) {
		this->byte_0 = (this->byte_0 << 1) | !!bit;
	}


	INLINE uint8_t out() {
		uint8_t out		= this->byte_0 & 0x01;
		this->byte_0	= this->byte_0 >> 1;
		return out;
	}


	static INLINE uint8_t fill() { return 0xff; }
};




////////////////////////////////////////////////////////////////////////////////
// BITFIELD - 16-BIT
////////////////////////////////////////////////////////////////////////////////
union uint16_b {
	INLINE uint16_b()				{ this->word_0 = 0; }
	INLINE uint16_b(uint16_t word)	{ this->word_0 = word; }

	INLINE uint16_b(uint8_t byte_0, uint8_t byte_1) {
		this->byte_0 = byte_0;
		this->byte_1 = byte_1;
	}

	uint16_t word_0;

	struct {
		union {
			uint8_t byte_0;
			struct {
				unsigned int bit_0		: 1;
				unsigned int bit_1		: 1;
				unsigned int bit_2		: 1;
				unsigned int bit_3		: 1;
				unsigned int bit_4		: 1;
				unsigned int bit_5		: 1;
				unsigned int bit_6		: 1;
				unsigned int bit_7		: 1;
			};
		};

		union {
			uint8_t byte_1;
			struct {
				unsigned int bit_8		: 1;
				unsigned int bit_9		: 1;
				unsigned int bit_10		: 1;
				unsigned int bit_11		: 1;
				unsigned int bit_12		: 1;
				unsigned int bit_13		: 1;
				unsigned int bit_14		: 1;
				unsigned int bit_15		: 1;
			};
		};
	};


	INLINE operator uint16_t() const {
		return this->word_0;
	}


	INLINE uint16_t operator =(uint16_t word) {
		return this->word_0 = word;
	}


	INLINE void in(uint8_t bit) {
		this->word_0 = (this->word_0 << 1) | !!bit;
	}


	INLINE uint8_t out() {
		uint8_t out		= this->word_0 & 0x01;
		this->word_0	= this->word_0 >> 1;
		return out;
	}


	INLINE void swap() {
		byte_0 ^= byte_1;
		byte_1 ^= byte_0;
		byte_0 ^= byte_1;
	}


	static INLINE uint16_t fill() { return 0xffff; }
};




////////////////////////////////////////////////////////////////////////////////
// BITFIELD - 32-BIT
////////////////////////////////////////////////////////////////////////////////
union uint32_b {
	INLINE uint32_b()				{ this->dword_0 = 0; }
	INLINE uint32_b(uint32_t dword)	{ this->dword_0 = dword; }

	INLINE uint32_b(uint8_t word_0, uint8_t word_1) {
		this->word_0 = word_0;
		this->word_1 = word_1;
	}

	INLINE uint32_b(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2, uint8_t byte_3) {
		this->byte_0 = byte_0;
		this->byte_1 = byte_1;
		this->byte_2 = byte_2;
		this->byte_3 = byte_3;
	}


	uint32_t dword_0;

	struct {
		union {
			uint16_t word_0;

			struct {
				union {
					uint8_t byte_0;
					struct {
						unsigned int bit_0		: 1;
						unsigned int bit_1		: 1;
						unsigned int bit_2		: 1;
						unsigned int bit_3		: 1;
						unsigned int bit_4		: 1;
						unsigned int bit_5		: 1;
						unsigned int bit_6		: 1;
						unsigned int bit_7		: 1;
					};
				};

				union {
					uint8_t byte_1;
					struct {
						unsigned int bit_8		: 1;
						unsigned int bit_9		: 1;
						unsigned int bit_10		: 1;
						unsigned int bit_11		: 1;
						unsigned int bit_12		: 1;
						unsigned int bit_13		: 1;
						unsigned int bit_14		: 1;
						unsigned int bit_15		: 1;
					};
				};
			};
		};

		union {
			uint16_t word_1;

			struct {
				union {
					uint8_t byte_2;
					struct {
						unsigned int bit_16		: 1;
						unsigned int bit_17		: 1;
						unsigned int bit_18		: 1;
						unsigned int bit_19		: 1;
						unsigned int bit_20		: 1;
						unsigned int bit_21		: 1;
						unsigned int bit_22		: 1;
						unsigned int bit_23		: 1;
					};
				};

				union {
					uint8_t byte_3;
					struct {
						unsigned int bit_24		: 1;
						unsigned int bit_25		: 1;
						unsigned int bit_26		: 1;
						unsigned int bit_27		: 1;
						unsigned int bit_28		: 1;
						unsigned int bit_29		: 1;
						unsigned int bit_30		: 1;
						unsigned int bit_31		: 1;
					};
				};
			};
		};
	};


	INLINE operator uint32_t() const {
		return this->dword_0;
	}


	INLINE uint32_t operator =(uint32_t dword) {
		return this->dword_0 = dword;
	}


	INLINE void in(uint8_t bit) {
		this->dword_0 = (this->dword_0 << 1) | !!bit;
	}


	INLINE uint8_t out() {
		uint8_t out		= this->dword_0 & 0x01;
		this->dword_0	= this->dword_0 >> 1;
		return out;
	}


	INLINE void swap() {
		byte_0 ^= byte_3;
		byte_3 ^= byte_0;
		byte_0 ^= byte_3;

		byte_1 ^= byte_2;
		byte_2 ^= byte_1;
		byte_1 ^= byte_2;
	}


	static INLINE uint32_t fill() { return 0xffffffff; }
};




#endif //__binary_h__
