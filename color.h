/*----------------------------------------------------------------------------*\
| PART OF THE COSPLAY.LIGHTING SOURCE CODE LIBRARY COLLECTION.                 |
| SOURCE:  https://github.com/cosplaylighting/color                            |
| LICENSE: https://github.com/cosplaylighting/color/blob/master/LICENSE        |
+------------------------------------------------------------------------------+
| SIMPLE STRUCT FOR HANDLING RGB COLOR VALUES FOR THE WS2812B LED.             |
| THIS LIBRARY HANDLES CONVERSIONS TO/FROM INTEGER VALUES, RGB VALUES, AND     |
| THE GRB VALUE USED BY THIS LED. THE LIBRARY ALSO HAS PREDEFINED COLOR NAMES  |
| AND BASIC OPERATORS THAT CAN BE USED TO MANIPULATE THE COLOR VALUES.         |
\*----------------------------------------------------------------------------*/




#ifndef __color_h__
#define __color_h__



#include "inline.h"




struct PACKED color_t {

	////////////////////////////////////////////////////////////////////////////
	//NOTE:	yes, this is in G-R-B order, this is the order that the WS2812B
	//		LED expects the colors to be sent in
	////////////////////////////////////////////////////////////////////////////
	uint8_t g;
	uint8_t r;
	uint8_t b;




	////////////////////////////////////////////////////////////////////////////
	// DEFAULT CONSTRUCTOR - ALL ZEROS (BLACK)
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t() {
		this->g = 0;
		this->r = 0;
		this->b = 0;
	}




	////////////////////////////////////////////////////////////////////////////
	// COPY COLOR FROM EXISTING COLOR_T ON THE STACK
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(const color_t &color) {
		this->g = color.g;
		this->r = color.r;
		this->b = color.b;
	}



	////////////////////////////////////////////////////////////////////////////
	// COPY COLOR FROM EXISTING COLOR_T ON THE STACK
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(volatile const color_t &color) {
		this->g = color.g;
		this->r = color.r;
		this->b = color.b;
	}




	////////////////////////////////////////////////////////////////////////////
	// COPY COLOR FROM EXISTING COLOR_T POINTER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(const color_t *color) {
		this->g = color->g;
		this->r = color->r;
		this->b = color->b;
	}




	////////////////////////////////////////////////////////////////////////////
	// COPY COLOR FROM EXISTING COLOR_T POINTER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(volatile const color_t *color) {
		this->g = color->g;
		this->r = color->r;
		this->b = color->b;
	}




	////////////////////////////////////////////////////////////////////////////
	// COLOR FROM R-G-B VALUES
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(const uint8_t r, const uint8_t g, const uint8_t b) {
		this->g = g;
		this->r = r;
		this->b = b;
	}




	////////////////////////////////////////////////////////////////////////////
	// COLOR FROM A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(const int16_t color) {
		this->g = (color >>  2) & 0x1f;
		this->r = (color >>  7) & 0x1f;
		this->b = (color <<  3) & 0x1f;
	}




	////////////////////////////////////////////////////////////////////////////
	// COLOR FROM A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(const uint16_t color) {
		this->g = (color >>  2) & 0x1f;
		this->r = (color >>  7) & 0x1f;
		this->b = (color <<  3) & 0x1f;
	}




	////////////////////////////////////////////////////////////////////////////
	// COLOR FROM A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(const int32_t color) {
		this->g = (color >>  8) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->b = (color >>  0) & 0xff;
	}




	////////////////////////////////////////////////////////////////////////////
	// COLOR FROM A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(const uint32_t color) {
		this->g = (color >>  8) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->b = (color >>  0) & 0xff;
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE operator int16_t() const {
		return	((this->r & 0xf8) << 7)
			|	((this->g & 0xf8) << 2)
			|	((this->b & 0xf8) >> 3);
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBB ORDER - VOLATILE
	////////////////////////////////////////////////////////////////////////////
	INLINE operator int16_t() volatile const {
		return	((this->r & 0xf8) << 7)
			|	((this->g & 0xf8) << 2)
			|	((this->b & 0xf8) >> 3);
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE operator uint16_t() const {
		return	((this->r & 0xf8) << 7)
			|	((this->g & 0xf8) << 2)
			|	((this->b & 0xf8) >> 3);
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBB ORDER - VOLATILE
	////////////////////////////////////////////////////////////////////////////
	INLINE operator uint16_t() volatile const {
		return	((this->r & 0xf8) << 7)
			|	((this->g & 0xf8) << 2)
			|	((this->b & 0xf8) >> 3);
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE operator int32_t() const {
		return (this->r << 16) | (this->g << 8) | (this->b << 0);
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER - VOLATILE
	////////////////////////////////////////////////////////////////////////////
	INLINE operator int32_t() volatile const {
		return (this->r << 16) | (this->g << 8) | (this->b << 0);
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE operator uint32_t() const {
		return (this->r << 16) | (this->g << 8) | (this->b << 0);
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER - VOLATILE
	////////////////////////////////////////////////////////////////////////////
	INLINE operator uint32_t() volatile const {
		return (this->r << 16) | (this->g << 8) | (this->b << 0);
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE int16_t operator =(const int16_t color) {
		this->g = (color >>  2) & 0x1f;
		this->r = (color >>  7) & 0x1f;
		this->b = (color <<  3) & 0x1f;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBBB ORDER - VOLATILE
	////////////////////////////////////////////////////////////////////////////
	INLINE int16_t operator =(const int16_t color) volatile {
		this->g = (color >>  2) & 0x1f;
		this->r = (color >>  7) & 0x1f;
		this->b = (color <<  3) & 0x1f;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE uint16_t operator =(const uint16_t color) {
		this->g = (color >>  2) & 0x1f;
		this->r = (color >>  7) & 0x1f;
		this->b = (color <<  3) & 0x1f;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 15-BIT INTEGER IN TRADITIONAL 0B0RRRRRGGGGGBBBBB ORDER - VOLATILE
	////////////////////////////////////////////////////////////////////////////
	INLINE uint16_t operator =(const uint16_t color) volatile {
		this->g = (color >>  2) & 0x1f;
		this->r = (color >>  7) & 0x1f;
		this->b = (color <<  3) & 0x1f;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE int32_t operator =(const int32_t color) {
		this->g = (color >>  8) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->b = (color >>  0) & 0xff;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER - VOLATILE
	////////////////////////////////////////////////////////////////////////////
	INLINE int32_t operator =(const int32_t color) volatile {
		this->g = (color >>  8) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->b = (color >>  0) & 0xff;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE uint32_t operator =(const uint32_t color) {
		this->g = (color >>  8) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->b = (color >>  0) & 0xff;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER - VOLATILE
	////////////////////////////////////////////////////////////////////////////
	INLINE uint32_t operator =(const uint32_t color) volatile {
		this->g = (color >>  8) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->b = (color >>  0) & 0xff;
		return color;
	}


//////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	// INCREASE VALUE
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t add(const uint8_t value) {
		return this->add(value, value, value);
	}

	INLINE color_t add(const uint8_t r, const uint8_t g, const uint8_t b) {
		this->g += g;
		this->r += r;
		this->b += b;
		return this;
	}




	////////////////////////////////////////////////////////////////////////////
	// DECREASE VALUE
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t sub(const uint8_t value) {
		return this->sub(value, value, value);
	}

	INLINE color_t sub(const uint8_t r, const uint8_t g, const uint8_t b) {
		this->g -= g;
		this->r -= r;
		this->b -= b;
		return this;
	}




	////////////////////////////////////////////////////////////////////////////
	// SHIFT VALUE RIGHT
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t right(const uint8_t value) {
		return this->right(value, value, value);
	}

	INLINE color_t right(const uint8_t r, const uint8_t g, const uint8_t b) {
		this->g >>= g;
		this->r >>= r;
		this->b >>= b;
		return this;
	}




	////////////////////////////////////////////////////////////////////////////
	// SHIFT VALUE LEFT
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t left(const uint8_t value) {
		return this->left(value, value, value);
	}

	INLINE color_t left(const uint8_t r, const uint8_t g, const uint8_t b) {
		this->g <<= g;
		this->r <<= r;
		this->b <<= b;
		return this;
	}




	////////////////////////////////////////////////////////////////////////////
	// INPUT A HUE VALUE 0 TO 767 TO GET A RGB COLOR VALUE.
	// THE COLORS ARE A TRANSITION R - G - B - BACK TO R.
	////////////////////////////////////////////////////////////////////////////
	static color_t hue(const uint16_t hue) {
		const uint8_t step = hue & 0xff;

		switch ((hue >> 8) & 0x03) {
			case 0x01:	return color_t(    0, ~step,  step);
			case 0x02:	return color_t( step,     0, ~step);
			default:	return color_t(~step,  step,     0);
		}
	}




	////////////////////////////////////////////////////////////////////////////
	// VGA COLOR NAMES - THESE ARE ALSO THE HTML COLOR CODE NAMES
	// SOURCE: http://www.blooberry.com/indexdot/color/vganame.htm
	////////////////////////////////////////////////////////////////////////////
	static INLINE color_t black()					{ return color_t(); }
	static INLINE color_t white()					{ return 0xffffffl; }
	static INLINE color_t red()						{ return 0xff0000l; }
	static INLINE color_t yellow()					{ return 0xffff00l; }
	static INLINE color_t lime()					{ return 0x00ff00l; }
	static INLINE color_t aqua()					{ return 0x00ffffl; }
	static INLINE color_t blue()					{ return 0x0000ffl; }
	static INLINE color_t fuchsia()					{ return 0xff00ffl; }
	static INLINE color_t orange()					{ return 0xff8000l; }
	static INLINE color_t gray()					{ return 0x808080l; }
	static INLINE color_t silver()					{ return 0xc0c0c0l; }
	static INLINE color_t maroon()					{ return 0x800000l; }
	static INLINE color_t olive()					{ return 0x808000l; }
	static INLINE color_t green()					{ return 0x008000l; }
	static INLINE color_t teal()					{ return 0x008080l; }
	static INLINE color_t navy()					{ return 0x000080l; }
	static INLINE color_t purple()					{ return 0x800080l; }




	////////////////////////////////////////////////////////////////////////////
	// X11 COLOR CODES - THESE ARE ALSO THE HTML COLOR CODE NAMES
	// SOURCE: https://www.w3schools.com/colors/colors_x11.asp
	////////////////////////////////////////////////////////////////////////////
	static INLINE color_t aliceblue()				{ return 0xf0f8ffl; }
	static INLINE color_t antiquewhite()			{ return 0xfaebd7l; }
	static INLINE color_t antiquewhite1()			{ return 0xffefdbl; }
	static INLINE color_t antiquewhite2()			{ return 0xeedfccl; }
	static INLINE color_t antiquewhite3()			{ return 0xcdc0b0l; }
	static INLINE color_t antiquewhite4()			{ return 0x8b8378l; }
	static INLINE color_t aquamarine1()				{ return 0x7fffd4l; }
	static INLINE color_t aquamarine2()				{ return 0x76eec6l; }
	static INLINE color_t aquamarine4()				{ return 0x458b74l; }
	static INLINE color_t azure1()					{ return 0xf0ffffl; }
	static INLINE color_t azure2()					{ return 0xe0eeeel; }
	static INLINE color_t azure3()					{ return 0xc1cdcdl; }
	static INLINE color_t azure4()					{ return 0x838b8bl; }
	static INLINE color_t beige()					{ return 0xf5f5dcl; }
	static INLINE color_t bisque1()					{ return 0xffe4c4l; }
	static INLINE color_t bisque2()					{ return 0xeed5b7l; }
	static INLINE color_t bisque3()					{ return 0xcdb79el; }
	static INLINE color_t bisque4()					{ return 0x8b7d6bl; }
	static INLINE color_t blanchedalmond()			{ return 0xffebcdl; }
	static INLINE color_t blue1()					{ return 0x0000ffl; }
	static INLINE color_t blue2()					{ return 0x0000eel; }
	static INLINE color_t blue4()					{ return 0x00008bl; }
	static INLINE color_t blueviolet()				{ return 0x8a2be2l; }
	static INLINE color_t brown()					{ return 0xa52a2al; }
	static INLINE color_t brown1()					{ return 0xff4040l; }
	static INLINE color_t brown2()					{ return 0xee3b3bl; }
	static INLINE color_t brown3()					{ return 0xcd3333l; }
	static INLINE color_t brown4()					{ return 0x8b2323l; }
	static INLINE color_t burlywood()				{ return 0xdeb887l; }
	static INLINE color_t burlywood1()				{ return 0xffd39bl; }
	static INLINE color_t burlywood2()				{ return 0xeec591l; }
	static INLINE color_t burlywood3()				{ return 0xcdaa7dl; }
	static INLINE color_t burlywood4()				{ return 0x8b7355l; }
	static INLINE color_t cadetblue()				{ return 0x5f9ea0l; }
	static INLINE color_t cadetblue1()				{ return 0x98f5ffl; }
	static INLINE color_t cadetblue2()				{ return 0x8ee5eel; }
	static INLINE color_t cadetblue3()				{ return 0x7ac5cdl; }
	static INLINE color_t cadetblue4()				{ return 0x53868bl; }
	static INLINE color_t chartreuse1()				{ return 0x7fff00l; }
	static INLINE color_t chartreuse2()				{ return 0x76ee00l; }
	static INLINE color_t chartreuse3()				{ return 0x66cd00l; }
	static INLINE color_t chartreuse4()				{ return 0x458b00l; }
	static INLINE color_t chocolate()				{ return 0xd2691el; }
	static INLINE color_t chocolate1()				{ return 0xff7f24l; }
	static INLINE color_t chocolate2()				{ return 0xee7621l; }
	static INLINE color_t chocolate3()				{ return 0xcd661dl; }
	static INLINE color_t coral()					{ return 0xff7f50l; }
	static INLINE color_t coral1()					{ return 0xff7256l; }
	static INLINE color_t coral2()					{ return 0xee6a50l; }
	static INLINE color_t coral3()					{ return 0xcd5b45l; }
	static INLINE color_t coral4()					{ return 0x8b3e2fl; }
	static INLINE color_t cornflowerblue()			{ return 0x6495edl; }
	static INLINE color_t cornsilk1()				{ return 0xfff8dcl; }
	static INLINE color_t ornsilk2()				{ return 0xeee8cdl; }
	static INLINE color_t cornsilk3()				{ return 0xcdc8b1l; }
	static INLINE color_t cornsilk4()				{ return 0x8b8878l; }
	static INLINE color_t cyan1()					{ return 0x00ffffl; }
	static INLINE color_t cyan2()					{ return 0x00eeeel; }
	static INLINE color_t cyan3()					{ return 0x00cdcdl; }
	static INLINE color_t cyan4()					{ return 0x008b8bl; }
	static INLINE color_t darkgoldenrod()			{ return 0xb8860bl; }
	static INLINE color_t darkgoldenrod1()			{ return 0xffb90fl; }
	static INLINE color_t darkgoldenrod2()			{ return 0xeead0el; }
	static INLINE color_t darkgoldenrod3()			{ return 0xcd950cl; }
	static INLINE color_t darkgoldenrod4()			{ return 0x8b6508l; }
	static INLINE color_t darkgreen()				{ return 0x006400l; }
	static INLINE color_t darkkhaki()				{ return 0xbdb76bl; }
	static INLINE color_t darkolivegreen()			{ return 0x556b2fl; }
	static INLINE color_t darkolivegreen1()			{ return 0xcaff70l; }
	static INLINE color_t darkolivegreen2()			{ return 0xbcee68l; }
	static INLINE color_t darkolivegreen3()			{ return 0xa2cd5al; }
	static INLINE color_t darkolivegreen4()			{ return 0x6e8b3dl; }
	static INLINE color_t darkorange()				{ return 0xff8c00l; }
	static INLINE color_t darkorange1()				{ return 0xff7f00l; }
	static INLINE color_t darkorange2()				{ return 0xee7600l; }
	static INLINE color_t darkorange3()				{ return 0xcd6600l; }
	static INLINE color_t darkorange4()				{ return 0x8b4500l; }
	static INLINE color_t darkorchid()				{ return 0x9932ccl; }
	static INLINE color_t darkorchid1()				{ return 0xbf3effl; }
	static INLINE color_t darkorchid2()				{ return 0xb23aeel; }
	static INLINE color_t darkorchid3()				{ return 0x9a32cdl; }
	static INLINE color_t darkorchid4()				{ return 0x68228bl; }
	static INLINE color_t darksalmon()				{ return 0xe9967al; }
	static INLINE color_t darkseagreen()			{ return 0x8fbc8fl; }
	static INLINE color_t darkseagreen1()			{ return 0xc1ffc1l; }
	static INLINE color_t darkseagreen2()			{ return 0xb4eeb4l; }
	static INLINE color_t darkseagreen3()			{ return 0x9bcd9bl; }
	static INLINE color_t darkseagreen4()			{ return 0x698b69l; }
	static INLINE color_t darkslateblue()			{ return 0x483d8bl; }
	static INLINE color_t darkslategray()			{ return 0x2f4f4fl; }
	static INLINE color_t darkslategray1()			{ return 0x97ffffl; }
	static INLINE color_t darkslategray2()			{ return 0x8deeeel; }
	static INLINE color_t darkslategray3()			{ return 0x79cdcdl; }
	static INLINE color_t darkslategray4()			{ return 0x528b8bl; }
	static INLINE color_t darkturquoise()			{ return 0x00ced1l; }
	static INLINE color_t darkviolet()				{ return 0x9400d3l; }
	static INLINE color_t deeppink1()				{ return 0xff1493l; }
	static INLINE color_t deeppink2()				{ return 0xee1289l; }
	static INLINE color_t deeppink3()				{ return 0xcd1076l; }
	static INLINE color_t deeppink4()				{ return 0x8b0a50l; }
	static INLINE color_t deepskyblue1()			{ return 0x00bfffl; }
	static INLINE color_t deepskyblue2()			{ return 0x00b2eel; }
	static INLINE color_t deepskyblue3()			{ return 0x009acdl; }
	static INLINE color_t deepskyblue4()			{ return 0x00688bl; }
	static INLINE color_t dimgray()					{ return 0x696969l; }
	static INLINE color_t dodgerblue1()				{ return 0x1e90ffl; }
	static INLINE color_t dodgerblue2()				{ return 0x1c86eel; }
	static INLINE color_t dodgerblue3()				{ return 0x1874cdl; }
	static INLINE color_t dodgerblue4()				{ return 0x104e8bl; }
	static INLINE color_t firebrick()				{ return 0xb22222l; }
	static INLINE color_t firebrick1()				{ return 0xff3030l; }
	static INLINE color_t firebrick2()				{ return 0xee2c2cl; }
	static INLINE color_t firebrick3()				{ return 0xcd2626l; }
	static INLINE color_t firebrick4()				{ return 0x8b1a1al; }
	static INLINE color_t floralwhite()				{ return 0xfffaf0l; }
	static INLINE color_t forestgreen()				{ return 0x228b22l; }
	static INLINE color_t gainsboro()				{ return 0xdcdcdcl; }
	static INLINE color_t ghostwhite()				{ return 0xf8f8ffl; }
	static INLINE color_t gold1()					{ return 0xffd700l; }
	static INLINE color_t gold2()					{ return 0xeec900l; }
	static INLINE color_t gold3()					{ return 0xcdad00l; }
	static INLINE color_t gold4()					{ return 0x8b7500l; }
	static INLINE color_t goldenrod()				{ return 0xdaa520l; }
	static INLINE color_t goldenrod1()				{ return 0xffc125l; }
	static INLINE color_t goldenrod2()				{ return 0xeeb422l; }
	static INLINE color_t goldenrod3()				{ return 0xcd9b1dl; }
	static INLINE color_t goldenrod4()				{ return 0x8b6914l; }
	static INLINE color_t gray0()					{ return 0xbebebel; }
	static INLINE color_t gray1()					{ return 0x030303l; }
	static INLINE color_t gray2()					{ return 0x050505l; }
	static INLINE color_t gray3()					{ return 0x080808l; }
	static INLINE color_t gray4()					{ return 0x0a0a0al; }
	static INLINE color_t gray5()					{ return 0x0d0d0dl; }
	static INLINE color_t gray6()					{ return 0x0f0f0fl; }
	static INLINE color_t gray7()					{ return 0x121212l; }
	static INLINE color_t gray8()					{ return 0x141414l; }
	static INLINE color_t gray9()					{ return 0x171717l; }
	static INLINE color_t gray10()					{ return 0x1a1a1al; }
	static INLINE color_t gray11()					{ return 0x1c1c1cl; }
	static INLINE color_t gray12()					{ return 0x1f1f1fl; }
	static INLINE color_t gray13()					{ return 0x212121l; }
	static INLINE color_t gray14()					{ return 0x242424l; }
	static INLINE color_t gray15()					{ return 0x262626l; }
	static INLINE color_t gray16()					{ return 0x292929l; }
	static INLINE color_t gray17()					{ return 0x2b2b2bl; }
	static INLINE color_t gray18()					{ return 0x2e2e2el; }
	static INLINE color_t gray19()					{ return 0x303030l; }
	static INLINE color_t gray20()					{ return 0x333333l; }
	static INLINE color_t gray21()					{ return 0x363636l; }
	static INLINE color_t gray22()					{ return 0x383838l; }
	static INLINE color_t gray23()					{ return 0x3b3b3bl; }
	static INLINE color_t gray24()					{ return 0x3d3d3dl; }
	static INLINE color_t gray25()					{ return 0x404040l; }
	static INLINE color_t gray26()					{ return 0x424242l; }
	static INLINE color_t gray27()					{ return 0x454545l; }
	static INLINE color_t gray28()					{ return 0x474747l; }
	static INLINE color_t gray29()					{ return 0x4a4a4al; }
	static INLINE color_t gray30()					{ return 0x4d4d4dl; }
	static INLINE color_t gray31()					{ return 0x4f4f4fl; }
	static INLINE color_t gray32()					{ return 0x525252l; }
	static INLINE color_t gray33()					{ return 0x545454l; }
	static INLINE color_t gray34()					{ return 0x575757l; }
	static INLINE color_t gray35()					{ return 0x595959l; }
	static INLINE color_t gray36()					{ return 0x5c5c5cl; }
	static INLINE color_t gray37()					{ return 0x5e5e5el; }
	static INLINE color_t gray38()					{ return 0x616161l; }
	static INLINE color_t gray39()					{ return 0x636363l; }
	static INLINE color_t gray40()					{ return 0x666666l; }
	static INLINE color_t gray41()					{ return 0x696969l; }
	static INLINE color_t gray42()					{ return 0x6b6b6bl; }
	static INLINE color_t gray43()					{ return 0x6e6e6el; }
	static INLINE color_t gray44()					{ return 0x707070l; }
	static INLINE color_t gray45()					{ return 0x737373l; }
	static INLINE color_t gray46()					{ return 0x757575l; }
	static INLINE color_t gray47()					{ return 0x787878l; }
	static INLINE color_t gray48()					{ return 0x7a7a7al; }
	static INLINE color_t gray49()					{ return 0x7d7d7dl; }
	static INLINE color_t gray50()					{ return 0x7f7f7fl; }
	static INLINE color_t gray51()					{ return 0x828282l; }
	static INLINE color_t gray52()					{ return 0x858585l; }
	static INLINE color_t gray53()					{ return 0x878787l; }
	static INLINE color_t gray54()					{ return 0x8a8a8al; }
	static INLINE color_t gray55()					{ return 0x8c8c8cl; }
	static INLINE color_t gray56()					{ return 0x8f8f8fl; }
	static INLINE color_t gray57()					{ return 0x919191l; }
	static INLINE color_t gray58()					{ return 0x949494l; }
	static INLINE color_t gray59()					{ return 0x969696l; }
	static INLINE color_t gray60()					{ return 0x999999l; }
	static INLINE color_t gray61()					{ return 0x9c9c9cl; }
	static INLINE color_t gray62()					{ return 0x9e9e9el; }
	static INLINE color_t gray63()					{ return 0xa1a1a1l; }
	static INLINE color_t gray64()					{ return 0xa3a3a3l; }
	static INLINE color_t gray65()					{ return 0xa6a6a6l; }
	static INLINE color_t gray66()					{ return 0xa8a8a8l; }
	static INLINE color_t gray67()					{ return 0xabababl; }
	static INLINE color_t gray68()					{ return 0xadadadl; }
	static INLINE color_t gray69()					{ return 0xb0b0b0l; }
	static INLINE color_t gray70()					{ return 0xb3b3b3l; }
	static INLINE color_t gray71()					{ return 0xb5b5b5l; }
	static INLINE color_t gray72()					{ return 0xb8b8b8l; }
	static INLINE color_t gray73()					{ return 0xbababal; }
	static INLINE color_t gray74()					{ return 0xbdbdbdl; }
	static INLINE color_t gray75()					{ return 0xbfbfbfl; }
	static INLINE color_t gray76()					{ return 0xc2c2c2l; }
	static INLINE color_t gray77()					{ return 0xc4c4c4l; }
	static INLINE color_t gray78()					{ return 0xc7c7c7l; }
	static INLINE color_t gray79()					{ return 0xc9c9c9l; }
	static INLINE color_t gray80()					{ return 0xccccccl; }
	static INLINE color_t gray81()					{ return 0xcfcfcfl; }
	static INLINE color_t gray82()					{ return 0xd1d1d1l; }
	static INLINE color_t gray83()					{ return 0xd4d4d4l; }
	static INLINE color_t gray84()					{ return 0xd6d6d6l; }
	static INLINE color_t gray85()					{ return 0xd9d9d9l; }
	static INLINE color_t gray86()					{ return 0xdbdbdbl; }
	static INLINE color_t gray87()					{ return 0xdededel; }
	static INLINE color_t gray88()					{ return 0xe0e0e0l; }
	static INLINE color_t gray89()					{ return 0xe3e3e3l; }
	static INLINE color_t gray90()					{ return 0xe5e5e5l; }
	static INLINE color_t gray91()					{ return 0xe8e8e8l; }
	static INLINE color_t gray92()					{ return 0xebebebl; }
	static INLINE color_t gray93()					{ return 0xedededl; }
	static INLINE color_t gray94()					{ return 0xf0f0f0l; }
	static INLINE color_t gray95()					{ return 0xf2f2f2l; }
	static INLINE color_t gray97()					{ return 0xf7f7f7l; }
	static INLINE color_t gray98()					{ return 0xfafafal; }
	static INLINE color_t gray99()					{ return 0xfcfcfcl; }
	static INLINE color_t green1()					{ return 0x00ff00l; }
	static INLINE color_t green2()					{ return 0x00ee00l; }
	static INLINE color_t green3()					{ return 0x00cd00l; }
	static INLINE color_t green4()					{ return 0x008b00l; }
	static INLINE color_t greenyellow()				{ return 0xadff2fl; }
	static INLINE color_t honeydew1()				{ return 0xf0fff0l; }
	static INLINE color_t honeydew2()				{ return 0xe0eee0l; }
	static INLINE color_t honeydew3()				{ return 0xc1cdc1l; }
	static INLINE color_t honeydew4()				{ return 0x838b83l; }
	static INLINE color_t hotpink()					{ return 0xff69b4l; }
	static INLINE color_t hotpink1()				{ return 0xff6eb4l; }
	static INLINE color_t hotpink2()				{ return 0xee6aa7l; }
	static INLINE color_t hotpink3()				{ return 0xcd6090l; }
	static INLINE color_t hotpink4()				{ return 0x8b3a62l; }
	static INLINE color_t indianred()				{ return 0xcd5c5cl; }
	static INLINE color_t indianred1()				{ return 0xff6a6al; }
	static INLINE color_t indianred2()				{ return 0xee6363l; }
	static INLINE color_t indianred3()				{ return 0xcd5555l; }
	static INLINE color_t indianred4()				{ return 0x8b3a3al; }
	static INLINE color_t ivory1()					{ return 0xfffff0l; }
	static INLINE color_t ivory2()					{ return 0xeeeee0l; }
	static INLINE color_t ivory3()					{ return 0xcdcdc1l; }
	static INLINE color_t ivory4()					{ return 0x8b8b83l; }
	static INLINE color_t khaki()					{ return 0xf0e68cl; }
	static INLINE color_t khaki1()					{ return 0xfff68fl; }
	static INLINE color_t khaki2()					{ return 0xeee685l; }
	static INLINE color_t khaki3()					{ return 0xcdc673l; }
	static INLINE color_t khaki4()					{ return 0x8b864el; }
	static INLINE color_t lavender()				{ return 0xe6e6fal; }
	static INLINE color_t lavenderblush1()			{ return 0xfff0f5l; }
	static INLINE color_t lavenderblush2()			{ return 0xeee0e5l; }
	static INLINE color_t lavenderblush3()			{ return 0xcdc1c5l; }
	static INLINE color_t lavenderblush4()			{ return 0x8b8386l; }
	static INLINE color_t lawngreen()				{ return 0x7cfc00l; }
	static INLINE color_t lemonchiffon1()			{ return 0xfffacdl; }
	static INLINE color_t lemonchiffon2()			{ return 0xeee9bfl; }
	static INLINE color_t lemonchiffon3()			{ return 0xcdc9a5l; }
	static INLINE color_t lemonchiffon4()			{ return 0x8b8970l; }
	static INLINE color_t light()					{ return 0xeedd82l; }
	static INLINE color_t lightblue()				{ return 0xadd8e6l; }
	static INLINE color_t lightblue1()				{ return 0xbfefffl; }
	static INLINE color_t lightblue2()				{ return 0xb2dfeel; }
	static INLINE color_t lightblue3()				{ return 0x9ac0cdl; }
	static INLINE color_t lightblue4()				{ return 0x68838bl; }
	static INLINE color_t lightcoral()				{ return 0xf08080l; }
	static INLINE color_t lightcyan1()				{ return 0xe0ffffl; }
	static INLINE color_t lightcyan2()				{ return 0xd1eeeel; }
	static INLINE color_t lightcyan3()				{ return 0xb4cdcdl; }
	static INLINE color_t lightcyan4()				{ return 0x7a8b8bl; }
	static INLINE color_t lightgoldenrod1()			{ return 0xffec8bl; }
	static INLINE color_t lightgoldenrod2()			{ return 0xeedc82l; }
	static INLINE color_t lightgoldenrod3()			{ return 0xcdbe70l; }
	static INLINE color_t lightgoldenrod4()			{ return 0x8b814cl; }
	static INLINE color_t lightgoldenrodyellow()	{ return 0xfafad2l; }
	static INLINE color_t lightgray()				{ return 0xd3d3d3l; }
	static INLINE color_t lightpink()				{ return 0xffb6c1l; }
	static INLINE color_t lightpink1()				{ return 0xffaeb9l; }
	static INLINE color_t lightpink2()				{ return 0xeea2adl; }
	static INLINE color_t lightpink3()				{ return 0xcd8c95l; }
	static INLINE color_t lightpink4()				{ return 0x8b5f65l; }
	static INLINE color_t lightsalmon1()			{ return 0xffa07al; }
	static INLINE color_t lightsalmon2()			{ return 0xee9572l; }
	static INLINE color_t lightsalmon3()			{ return 0xcd8162l; }
	static INLINE color_t lightsalmon4()			{ return 0x8b5742l; }
	static INLINE color_t lightseagreen()			{ return 0x20b2aal; }
	static INLINE color_t lightskyblue()			{ return 0x87cefal; }
	static INLINE color_t lightskyblue1()			{ return 0xb0e2ffl; }
	static INLINE color_t lightskyblue2()			{ return 0xa4d3eel; }
	static INLINE color_t lightskyblue3()			{ return 0x8db6cdl; }
	static INLINE color_t lightskyblue4()			{ return 0x607b8bl; }
	static INLINE color_t lightslateblue()			{ return 0x8470ffl; }
	static INLINE color_t lightslategray()			{ return 0x778899l; }
	static INLINE color_t lightsteelblue()			{ return 0xb0c4del; }
	static INLINE color_t lightsteelblue1()			{ return 0xcae1ffl; }
	static INLINE color_t lightsteelblue2()			{ return 0xbcd2eel; }
	static INLINE color_t lightsteelblue3()			{ return 0xa2b5cdl; }
	static INLINE color_t lightsteelblue4()			{ return 0x6e7b8bl; }
	static INLINE color_t lightyellow1()			{ return 0xffffe0l; }
	static INLINE color_t lightyellow2()			{ return 0xeeeed1l; }
	static INLINE color_t lightyellow3()			{ return 0xcdcdb4l; }
	static INLINE color_t lightyellow4()			{ return 0x8b8b7al; }
	static INLINE color_t limegreen()				{ return 0x32cd32l; }
	static INLINE color_t linen()					{ return 0xfaf0e6l; }
	static INLINE color_t magenta()					{ return 0xff00ffl; }
	static INLINE color_t magenta2()				{ return 0xee00eel; }
	static INLINE color_t magenta3()				{ return 0xcd00cdl; }
	static INLINE color_t magenta4()				{ return 0x8b008bl; }
	static INLINE color_t maroon0()					{ return 0xb03060l; }
	static INLINE color_t maroon1()					{ return 0xff34b3l; }
	static INLINE color_t maroon2()					{ return 0xee30a7l; }
	static INLINE color_t maroon3()					{ return 0xcd2990l; }
	static INLINE color_t maroon4()					{ return 0x8b1c62l; }
	static INLINE color_t medium()					{ return 0x66cdaal; }
	static INLINE color_t mediumaquamarine()		{ return 0x66cdaal; }
	static INLINE color_t mediumblue()				{ return 0x0000cdl; }
	static INLINE color_t mediumorchid()			{ return 0xba55d3l; }
	static INLINE color_t mediumorchid1()			{ return 0xe066ffl; }
	static INLINE color_t mediumorchid2()			{ return 0xd15feel; }
	static INLINE color_t mediumorchid3()			{ return 0xb452cdl; }
	static INLINE color_t mediumorchid4()			{ return 0x7a378bl; }
	static INLINE color_t mediumpurple()			{ return 0x9370dbl; }
	static INLINE color_t mediumpurple1()			{ return 0xab82ffl; }
	static INLINE color_t mediumpurple2()			{ return 0x9f79eel; }
	static INLINE color_t mediumpurple3()			{ return 0x8968cdl; }
	static INLINE color_t mediumpurple4()			{ return 0x5d478bl; }
	static INLINE color_t mediumseagreen()			{ return 0x3cb371l; }
	static INLINE color_t mediumslateblue()			{ return 0x7b68eel; }
	static INLINE color_t mediumspringgreen()		{ return 0x00fa9al; }
	static INLINE color_t mediumturquoise()			{ return 0x48d1ccl; }
	static INLINE color_t mediumvioletred()			{ return 0xc71585l; }
	static INLINE color_t midnightblue()			{ return 0x191970l; }
	static INLINE color_t mintcream()				{ return 0xf5fffal; }
	static INLINE color_t mistyrose1()				{ return 0xffe4e1l; }
	static INLINE color_t mistyrose2()				{ return 0xeed5d2l; }
	static INLINE color_t mistyrose3()				{ return 0xcdb7b5l; }
	static INLINE color_t mistyrose4()				{ return 0x8b7d7bl; }
	static INLINE color_t moccasin()				{ return 0xffe4b5l; }
	static INLINE color_t navajowhite1()			{ return 0xffdeadl; }
	static INLINE color_t navajowhite2()			{ return 0xeecfa1l; }
	static INLINE color_t navajowhite3()			{ return 0xcdb38bl; }
	static INLINE color_t navajowhite4()			{ return 0x8b795el; }
	static INLINE color_t navyblue()				{ return 0x000080l; }
	static INLINE color_t oldlace()					{ return 0xfdf5e6l; }
	static INLINE color_t olivedrab()				{ return 0x6b8e23l; }
	static INLINE color_t olivedrab1()				{ return 0xc0ff3el; }
	static INLINE color_t olivedrab2()				{ return 0xb3ee3al; }
	static INLINE color_t olivedrab4()				{ return 0x698b22l; }
	static INLINE color_t orange1()					{ return 0xffa500l; }
	static INLINE color_t orange2()					{ return 0xee9a00l; }
	static INLINE color_t orange3()					{ return 0xcd8500l; }
	static INLINE color_t orange4()					{ return 0x8b5a00l; }
	static INLINE color_t orangered1()				{ return 0xff4500l; }
	static INLINE color_t orangered2()				{ return 0xee4000l; }
	static INLINE color_t orangered3()				{ return 0xcd3700l; }
	static INLINE color_t orangered4()				{ return 0x8b2500l; }
	static INLINE color_t orchid()					{ return 0xda70d6l; }
	static INLINE color_t orchid1()					{ return 0xff83fal; }
	static INLINE color_t orchid2()					{ return 0xee7ae9l; }
	static INLINE color_t orchid3()					{ return 0xcd69c9l; }
	static INLINE color_t orchid4()					{ return 0x8b4789l; }
	static INLINE color_t pale()					{ return 0xdb7093l; }
	static INLINE color_t palegoldenrod()			{ return 0xeee8aal; }
	static INLINE color_t palegreen()				{ return 0x98fb98l; }
	static INLINE color_t palegreen1()				{ return 0x9aff9al; }
	static INLINE color_t palegreen2()				{ return 0x90ee90l; }
	static INLINE color_t palegreen3()				{ return 0x7ccd7cl; }
	static INLINE color_t palegreen4()				{ return 0x548b54l; }
	static INLINE color_t paleturquoise()			{ return 0xafeeeel; }
	static INLINE color_t paleturquoise1()			{ return 0xbbffffl; }
	static INLINE color_t paleturquoise2()			{ return 0xaeeeeel; }
	static INLINE color_t paleturquoise3()			{ return 0x96cdcdl; }
	static INLINE color_t paleturquoise4()			{ return 0x668b8bl; }
	static INLINE color_t palevioletred()			{ return 0xdb7093l; }
	static INLINE color_t palevioletred1()			{ return 0xff82abl; }
	static INLINE color_t palevioletred2()			{ return 0xee799fl; }
	static INLINE color_t palevioletred3()			{ return 0xcd6889l; }
	static INLINE color_t palevioletred4()			{ return 0x8b475dl; }
	static INLINE color_t papayawhip()				{ return 0xffefd5l; }
	static INLINE color_t peachpuff1()				{ return 0xffdab9l; }
	static INLINE color_t peachpuff2()				{ return 0xeecbadl; }
	static INLINE color_t peachpuff3()				{ return 0xcdaf95l; }
	static INLINE color_t peachpuff4()				{ return 0x8b7765l; }
	static INLINE color_t pink()					{ return 0xffc0cbl; }
	static INLINE color_t pink1()					{ return 0xffb5c5l; }
	static INLINE color_t pink2()					{ return 0xeea9b8l; }
	static INLINE color_t pink3()					{ return 0xcd919el; }
	static INLINE color_t pink4()					{ return 0x8b636cl; }
	static INLINE color_t plum()					{ return 0xdda0ddl; }
	static INLINE color_t plum1()					{ return 0xffbbffl; }
	static INLINE color_t plum2()					{ return 0xeeaeeel; }
	static INLINE color_t plum3()					{ return 0xcd96cdl; }
	static INLINE color_t plum4()					{ return 0x8b668bl; }
	static INLINE color_t powderblue()				{ return 0xb0e0e6l; }
	static INLINE color_t purple0()					{ return 0xa020f0l; }
	static INLINE color_t purple1()					{ return 0x9b30ffl; }
	static INLINE color_t purple2()					{ return 0x912ceel; }
	static INLINE color_t purple3()					{ return 0x7d26cdl; }
	static INLINE color_t purple4()					{ return 0x551a8bl; }
	static INLINE color_t red1()					{ return 0xff0000l; }
	static INLINE color_t red2()					{ return 0xee0000l; }
	static INLINE color_t red3()					{ return 0xcd0000l; }
	static INLINE color_t red4()					{ return 0x8b0000l; }
	static INLINE color_t rosybrown()				{ return 0xbc8f8fl; }
	static INLINE color_t rosybrown1()				{ return 0xffc1c1l; }
	static INLINE color_t rosybrown2()				{ return 0xeeb4b4l; }
	static INLINE color_t rosybrown3()				{ return 0xcd9b9bl; }
	static INLINE color_t rosybrown4()				{ return 0x8b6969l; }
	static INLINE color_t royalblue()				{ return 0x4169e1l; }
	static INLINE color_t royalblue1()				{ return 0x4876ffl; }
	static INLINE color_t royalblue2()				{ return 0x436eeel; }
	static INLINE color_t royalblue3()				{ return 0x3a5fcdl; }
	static INLINE color_t royalblue4()				{ return 0x27408bl; }
	static INLINE color_t saddlebrown()				{ return 0x8b4513l; }
	static INLINE color_t salmon()					{ return 0xfa8072l; }
	static INLINE color_t salmon1()					{ return 0xff8c69l; }
	static INLINE color_t salmon2()					{ return 0xee8262l; }
	static INLINE color_t salmon3()					{ return 0xcd7054l; }
	static INLINE color_t salmon4()					{ return 0x8b4c39l; }
	static INLINE color_t sandybrown()				{ return 0xf4a460l; }
	static INLINE color_t seagreen1()				{ return 0x54ff9fl; }
	static INLINE color_t seagreen2()				{ return 0x4eee94l; }
	static INLINE color_t seagreen3()				{ return 0x43cd80l; }
	static INLINE color_t seagreen4()				{ return 0x2e8b57l; }
	static INLINE color_t seashell1()				{ return 0xfff5eel; }
	static INLINE color_t seashell2()				{ return 0xeee5del; }
	static INLINE color_t seashell3()				{ return 0xcdc5bfl; }
	static INLINE color_t seashell4()				{ return 0x8b8682l; }
	static INLINE color_t sienna()					{ return 0xa0522dl; }
	static INLINE color_t sienna1()					{ return 0xff8247l; }
	static INLINE color_t sienna2()					{ return 0xee7942l; }
	static INLINE color_t sienna3()					{ return 0xcd6839l; }
	static INLINE color_t sienna4()					{ return 0x8b4726l; }
	static INLINE color_t skyblue()					{ return 0x87ceebl; }
	static INLINE color_t skyblue1()				{ return 0x87ceffl; }
	static INLINE color_t skyblue2()				{ return 0x7ec0eel; }
	static INLINE color_t skyblue3()				{ return 0x6ca6cdl; }
	static INLINE color_t skyblue4()				{ return 0x4a708bl; }
	static INLINE color_t slateblue()				{ return 0x6a5acdl; }
	static INLINE color_t slateblue1()				{ return 0x836fffl; }
	static INLINE color_t slateblue2()				{ return 0x7a67eel; }
	static INLINE color_t slateblue3()				{ return 0x6959cdl; }
	static INLINE color_t slateblue4()				{ return 0x473c8bl; }
	static INLINE color_t slategray()				{ return 0x708090l; }
	static INLINE color_t slategray1()				{ return 0xc6e2ffl; }
	static INLINE color_t slategray2()				{ return 0xb9d3eel; }
	static INLINE color_t slategray3()				{ return 0x9fb6cdl; }
	static INLINE color_t slategray4()				{ return 0x6c7b8bl; }
	static INLINE color_t snow1()					{ return 0xfffafal; }
	static INLINE color_t snow2()					{ return 0xeee9e9l; }
	static INLINE color_t snow3()					{ return 0xcdc9c9l; }
	static INLINE color_t snow4()					{ return 0x8b8989l; }
	static INLINE color_t springgreen1()			{ return 0x00ff7fl; }
	static INLINE color_t springgreen2()			{ return 0x00ee76l; }
	static INLINE color_t springgreen3()			{ return 0x00cd66l; }
	static INLINE color_t springgreen4()			{ return 0x008b45l; }
	static INLINE color_t steelblue()				{ return 0x4682b4l; }
	static INLINE color_t steelblue1()				{ return 0x63b8ffl; }
	static INLINE color_t steelblue2()				{ return 0x5caceel; }
	static INLINE color_t steelblue3()				{ return 0x4f94cdl; }
	static INLINE color_t steelblue4()				{ return 0x36648bl; }
	static INLINE color_t tan()						{ return 0xd2b48cl; }
	static INLINE color_t tan1()					{ return 0xffa54fl; }
	static INLINE color_t tan2()					{ return 0xee9a49l; }
	static INLINE color_t tan3()					{ return 0xcd853fl; }
	static INLINE color_t tan4()					{ return 0x8b5a2bl; }
	static INLINE color_t thistle()					{ return 0xd8bfd8l; }
	static INLINE color_t thistle1()				{ return 0xffe1ffl; }
	static INLINE color_t thistle2()				{ return 0xeed2eel; }
	static INLINE color_t thistle3()				{ return 0xcdb5cdl; }
	static INLINE color_t thistle4()				{ return 0x8b7b8bl; }
	static INLINE color_t tomato1()					{ return 0xff6347l; }
	static INLINE color_t tomato2()					{ return 0xee5c42l; }
	static INLINE color_t tomato3()					{ return 0xcd4f39l; }
	static INLINE color_t tomato4()					{ return 0x8b3626l; }
	static INLINE color_t turquoise()				{ return 0x40e0d0l; }
	static INLINE color_t turquoise1()				{ return 0x00f5ffl; }
	static INLINE color_t turquoise2()				{ return 0x00e5eel; }
	static INLINE color_t turquoise3()				{ return 0x00c5cdl; }
	static INLINE color_t turquoise4()				{ return 0x00868bl; }
	static INLINE color_t violet()					{ return 0xee82eel; }
	static INLINE color_t violetred()				{ return 0xd02090l; }
	static INLINE color_t violetred1()				{ return 0xff3e96l; }
	static INLINE color_t violetred2()				{ return 0xee3a8cl; }
	static INLINE color_t violetred3()				{ return 0xcd3278l; }
	static INLINE color_t violetred4()				{ return 0x8b2252l; }
	static INLINE color_t wheat()					{ return 0xf5deb3l; }
	static INLINE color_t wheat1()					{ return 0xffe7bal; }
	static INLINE color_t wheat2()					{ return 0xeed8ael; }
	static INLINE color_t wheat3()					{ return 0xcdba96l; }
	static INLINE color_t wheat4()					{ return 0x8b7e66l; }
	static INLINE color_t whitesmoke()				{ return 0xf5f5f5l; }
	static INLINE color_t yellow1()					{ return 0xffff00l; }
	static INLINE color_t yellow2()					{ return 0xeeee00l; }
	static INLINE color_t yellow3()					{ return 0xcdcd00l; }
	static INLINE color_t yellow4()					{ return 0x8b8b00l; }
	static INLINE color_t yellowgreen()				{ return 0x9acd32l; }
};




#endif //__color_h__
