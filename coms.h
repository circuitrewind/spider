/*----------------------------------------------------------------------------*\
| BitBang SPI client library                                                   |
\*----------------------------------------------------------------------------*/



#ifdef	__AVR__
#ifndef	__coms_h__
#define	__coms_h__




#include "defines.h"




//TODO:	convert this over to a template instead of using variables.
//		this will allow for more compiler optimizations with inlining

class PACKED coms {
	public:



		////////////////////////////////////////////////////////////////////////
		// CREATE A SPI COMS OBJECT WITH GIVEN PIN VALUES
		////////////////////////////////////////////////////////////////////////
		INLINE coms(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t ss) {
			this->_mosi	= mosi;
			this->_miso	= miso;
			this->_clk	= clk;
			this->_ss	= ss;
		}




		////////////////////////////////////////////////////////////////////////
		// ENABLE INTERUPT
		////////////////////////////////////////////////////////////////////////
		INLINE void enable() {
			pinMode(this->_miso,	INPUT);
			pinMode(this->_mosi,	INPUT);
			pinMode(this->_clk,		INPUT);
			pinMode(this->_ss,		INPUT);

			PCMSK |= (1 << this->_ss);
			GIMSK |= 0b00100000;

			this->miso(0);
		}




		////////////////////////////////////////////////////////////////////////
		// DISABLE INTERUPT
		////////////////////////////////////////////////////////////////////////
		INLINE void disable() {
			PCMSK &= ~(1 << this->_ss);

			pinMode(this->_miso,	INPUT);
			pinMode(this->_mosi,	INPUT);
			pinMode(this->_clk,		INPUT);
			pinMode(this->_ss,		INPUT);

			this->miso(0);
		}




		////////////////////////////////////////////////////////////////////////
		// PROCESS INCOMING DATA
		////////////////////////////////////////////////////////////////////////
		uint16_b process();




		////////////////////////////////////////////////////////////////////////
		// READ DATA FROM EACH OF THE INPUT PINS
		////////////////////////////////////////////////////////////////////////
		INLINE uint8_t mosi()	{ return !!(PINB & (1 << this->_mosi));	}
		INLINE uint8_t clk()	{ return !!(PINB & (1 << this->_clk));	}
		INLINE uint8_t ss()		{ return !!(PINB & (1 << this->_ss));	}




		////////////////////////////////////////////////////////////////////////
		// WRITE DATA TO THE OUTPUT PIN
		////////////////////////////////////////////////////////////////////////
		INLINE void miso(uint8_t bit) {
			if (bit) {
				PORTB |=  (1 << this->_miso);
			} else {
				PORTB &= ~(1 << this->_miso);
			}
		}




	private:
		uint8_t _mosi	:4;
		uint8_t _miso	:4;
		uint8_t _clk	:4;
		uint8_t _ss		:4;

};



#endif //__coms_h__
#endif //__AVR__
