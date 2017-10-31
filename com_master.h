/*----------------------------------------------------------------------------*\
| BitBang SPI client library                                                   |
\*----------------------------------------------------------------------------*/



#ifndef	__com_master_h__
#define	__com_master_h__




#include "defines.h"


#define COMS_FIFO_SIZE 5



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
			disable();
		}




		////////////////////////////////////////////////////////////////////////
		// ENABLE OUTPUT
		////////////////////////////////////////////////////////////////////////
		INLINE void enable() {
			pinMode(this->_miso,	INPUT);
			pinMode(this->_mosi,	OUTPUT);
			pinMode(this->_clk,		OUTPUT);
			pinMode(this->_ss,		OUTPUT);
			digitalWrite(this->_ss,	LOW);
			_enabled = true;
		}




		////////////////////////////////////////////////////////////////////////
		// DISABLE OUTPUT
		////////////////////////////////////////////////////////////////////////
		INLINE void disable() {
			pinMode(this->_miso,	INPUT);
			pinMode(this->_mosi,	OUTPUT);
			pinMode(this->_clk,		OUTPUT);
			pinMode(this->_ss,		OUTPUT);
			digitalWrite(this->_ss,	HIGH);
			_enabled = false;
		}




		////////////////////////////////////////////////////////////////////////
		// PROCESS INCOMING DATA
		////////////////////////////////////////////////////////////////////////
		void loop() {
			if (!hasData()) return;

			if (!enabled()) {
				enable();
				return;
			}

			if (!miso()) return;

			uint32_b data = fifoRead();
			for (uint32_t i=31; i>=0; i--) {
				mosi(data.shift(i));
				delayMicroseconds(1);
				clk(true);
				delayMicroseconds(1);
				clk(false);
			}

			disable();
		}




		////////////////////////////////////////////////////////////////////////
		// READ/WRITE DATA FROM EACH OF THE PINS
		////////////////////////////////////////////////////////////////////////
		INLINE bool miso()			{ return digitalRead(this->_miso);	}
		INLINE bool mosi()			{ return digitalRead(this->_miso);	}
		INLINE bool clk()			{ return digitalRead(this->_clk);	}
		INLINE bool ss()			{ return digitalRead(this->_ss);	}
		INLINE void miso(bool bit)	{ digitalWrite(this->_miso,	bit ? HIGH : LOW);	}
		INLINE void mosi(bool bit)	{ digitalWrite(this->_mosi,	bit ? HIGH : LOW);	}
		INLINE void clk( bool bit)	{ digitalWrite(this->_clk,	bit ? HIGH : LOW);	}
		INLINE void ss(  bool bit)	{ digitalWrite(this->_ss,	bit ? HIGH : LOW);	}




		////////////////////////////////////////////////////////////////////////
		// ARE WE CURRENTLY ENABLED FOR OUTPUTTING
		////////////////////////////////////////////////////////////////////////
		INLINE bool enabled() {
			return _enabled;
		}



		////////////////////////////////////////////////////////////////////////
		// TRUE IF THERE IS CURRENT DATA IN THE BUFFER
		////////////////////////////////////////////////////////////////////////
		INLINE bool hasData() {
			return !!buffer[0];
		}




		////////////////////////////////////////////////////////////////////////
		// RETURN THE FIRST ITEM IN THE BUFFER WITHOUT CLEARING ANYTHING OUT
		////////////////////////////////////////////////////////////////////////
		INLINE uint32_b fifoPeak() {
			return buffer[0]
		}




		////////////////////////////////////////////////////////////////////////
		// TRUE IF THERE IS CURRENT DATA IN THE BUFFER
		////////////////////////////////////////////////////////////////////////
		void fifoWrite(uint32_b data) {
			for (int i=0; i<COMS_FIFO_SIZE; i++) {
				if (buffer[i] == 0) {
					buffer[i] = data;
					return;
				}
			}

			//BUFFER IS FULL, SO POP THE FIRST ITEM, AND PUSH NEW DATA TO END
			fifoRead();
			buffer[COMS_FIFO_SIZE-1] = data;
		}




		////////////////////////////////////////////////////////////////////////
		// TRUE IF THERE IS CURRENT DATA IN THE BUFFER
		////////////////////////////////////////////////////////////////////////
		uint32_b fifoRead() {
			if (!hasData()) return uint32_b();

			uint32_b ret = buffer[0];

			for (int i=0; i<COMS_FIFO_SIZE-1; i++) {
				buffer[i] = buffer[i + 1];
			}

			buffer[COMS_FIFO_SIZE-1] = 0;

			return ret;
		}



	private:
		bool		_enabled;
		uint8_t		_mosi;
		uint8_t		_miso;
		uint8_t		_clk;
		uint8_t		_ss;
		uint32_b	buffer[COMS_FIFO_SIZE];
};



extern coms LED_LEFT;
extern coms LED_RIGHT;


#endif //__com_master_h__
