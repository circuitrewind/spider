/*----------------------------------------------------------------------------*\
| BitBang SPI client library                                                   |
\*----------------------------------------------------------------------------*/



#ifndef	__com_master_h__
#define	__com_master_h__




#include "defines.h"


#define COMS_FIFO_SIZE 4



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
			Serial.println("Enabling...");
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
			Serial.println("Disabling...");
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

			Serial.println("Waiting for Attiny85...");

			if (!miso()) return;

			Serial.println("Writing...");

			uint16_b data = fifoRead();
			for (int i=15; i>=0; i--) {
				mosi(data & (1 << i));
				delayMicroseconds(1);
				clk(true);
				delayMicroseconds(1);
				clk(false);
			}

			int thing = data;
			char str[16];
			sprintf(str, "Out: %04x", thing);
			Serial.println(str);

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
		// TRUE IF THERE IS CURRENT DATA IN THE BUFFER
		////////////////////////////////////////////////////////////////////////
		void fifoWrite(uint16_b data) {
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
		uint16_b fifoRead() {
			if (!hasData()) return uint16_b();

			uint16_b ret = buffer[0];

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
		uint16_b	buffer[COMS_FIFO_SIZE];
};



extern coms LED_LEFT;
extern coms LED_RIGHT;


#endif //__com_master_h__
