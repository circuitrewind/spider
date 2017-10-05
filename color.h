#ifndef __color_h__
#define __color_h__



#include "defines.h"



struct color_t {

	public:
		////////////////////////////////////////////////////////////////////////
		//NOTE:	yes, this is in G-R-B order, this is the order that the WS2812B
		//		LED expects the colors to be sent in
		////////////////////////////////////////////////////////////////////////
		uint8_t g;
		uint8_t r;
		uint8_t b;




	public:


		INLINE color_t() {
			this->g = 0;
			this->r = 0;
			this->b = 0;
		}


		INLINE color_t(const color_t &color) {
			this->g = color.g;
			this->r = color.r;
			this->b = color.b;
		}


		INLINE color_t(const color_t *color) {
			this->g = color->g;
			this->r = color->r;
			this->b = color->b;
		}


		INLINE color_t(uint8_t r, uint8_t g, uint8_t b) {
			this->g = g;
			this->r = r;
			this->b = b;
		}


		INLINE color_t(uint32_t color) {
			this->g = (color >>  8) & 0xff;
			this->r = (color >>  0) & 0xff;
			this->b = (color >> 16) & 0xff;
		}




		////////////////////////////////////////////////////////////////////////
		// Input a hue value 0 to 767 to get a RGB color value.
		// The colors are a transition r - g - b - back to r.
		////////////////////////////////////////////////////////////////////////
		static color_t hue(uint16_t hue) {
			uint8_t step = hue & 0xff;

			switch ((hue >> 8) & 0x03) {
				case 0x04: //FALL THROUGH, THIS IS AN OVERFLOW CONDITION
				case 0x00: return color_t(~step,  step,     0);
				case 0x01: return color_t(    0, ~step,  step);
				case 0x02: return color_t( step,     0, ~step);
			}
		}




		////////////////////////////////////////////////////////////////////////
		// PREDEFINED COLORS
		////////////////////////////////////////////////////////////////////////
		static INLINE color_t black()	{ return color_t(  0,   0,   0); }
		static INLINE color_t white()	{ return color_t(255, 255, 255); }
		static INLINE color_t red()		{ return color_t(255,   0,   0); }
		static INLINE color_t green()	{ return color_t(  0, 255,   0); }
		static INLINE color_t blue()	{ return color_t(  0,   0, 255); }
		static INLINE color_t cyan()	{ return color_t(  0, 255, 255); }
		static INLINE color_t magenta()	{ return color_t(255,   0, 255); }
		static INLINE color_t yellow()	{ return color_t(255, 255,   0); }
};



#endif //__color_h__
