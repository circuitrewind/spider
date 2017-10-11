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




#ifndef INLINE
#define INLINE		inline __attribute__ ((always_inline))
#endif




struct color_t {

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
	// COPY COLOR FROM EXISTING COLOR_T POINTER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(const color_t *color) {
		this->g = color->g;
		this->r = color->r;
		this->b = color->b;
	}




	////////////////////////////////////////////////////////////////////////////
	// COLOR FROM R-G-B VALUES
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(uint8_t r, uint8_t g, uint8_t b) {
		this->g = g;
		this->r = r;
		this->b = b;
	}




	////////////////////////////////////////////////////////////////////////////
	// COLOR FROM A 32-BIT INTEGER IN TRADITIONAL 0X00BBGGRR ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(uint32_t color) {
		this->g = (color >>  8) & 0xff;
		this->r = (color >>  0) & 0xff;
		this->b = (color >> 16) & 0xff;
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00BBGGRR ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE operator uint32_t() const {
		return (this->r) | (this->g << 8) | (this->b << 16);
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00BBGGRR ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE uint32_t operator =(uint32_t color) {
		this->g = (color >>  8) & 0xff;
		this->r = (color >>  0) & 0xff;
		this->b = (color >> 16) & 0xff;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// INCREASE VALUE
	////////////////////////////////////////////////////////////////////////////
	INLINE void add(uint8_t value) { this->add(value, value, value); }
	INLINE void add(uint8_t r, uint8_t g, uint8_t b) {
		this->g += g;
		this->r += r;
		this->b += b;
	}




	////////////////////////////////////////////////////////////////////////////
	// DECREASE VALUE
	////////////////////////////////////////////////////////////////////////////
	INLINE void sub(uint8_t value) { this->sub(value, value, value); }
	INLINE void sub(uint8_t r, uint8_t g, uint8_t b) {
		this->g -= g;
		this->r -= r;
		this->b -= b;
	}




	////////////////////////////////////////////////////////////////////////////
	// SHIFT VALUE RIGHT
	////////////////////////////////////////////////////////////////////////////
	INLINE void right(uint8_t value) { this->right(value, value, value); }
	INLINE void right(uint8_t r, uint8_t g, uint8_t b) {
		this->g >>= g;
		this->r >>= r;
		this->b >>= b;
	}




	////////////////////////////////////////////////////////////////////////////
	// SHIFT VALUE LEFT
	////////////////////////////////////////////////////////////////////////////
	INLINE void left(uint8_t value) { this->left(value, value, value); }
	INLINE void left(uint8_t r, uint8_t g, uint8_t b) {
		this->g <<= g;
		this->r <<= r;
		this->b <<= b;
	}




	////////////////////////////////////////////////////////////////////////////
	// INPUT A HUE VALUE 0 TO 767 TO GET A RGB COLOR VALUE.
	// THE COLORS ARE A TRANSITION R - G - B - BACK TO R.
	////////////////////////////////////////////////////////////////////////////
	static color_t hue(uint16_t hue) {
		uint8_t step = hue & 0xff;

		switch ((hue >> 8) & 0x03) {
			case 0x01:	return color_t(    0, ~step,  step);
			case 0x02:	return color_t( step,     0, ~step);
			default:	return color_t(~step,  step,     0);
		}
	}




	////////////////////////////////////////////////////////////////////////////
	// 256 PREDEFINED XTERM COLORS
	// SOURCE: https://jonasjacek.github.io/colors/
	////////////////////////////////////////////////////////////////////////////
	static INLINE color_t Black()				{ return color_t(0,0,0); }
	static INLINE color_t Maroon()				{ return color_t(128,0,0); }
	static INLINE color_t Green()				{ return color_t(0,128,0); }
	static INLINE color_t Olive()				{ return color_t(128,128,0); }
	static INLINE color_t Navy()				{ return color_t(0,0,128); }
	static INLINE color_t Purple()				{ return color_t(128,0,128); }
	static INLINE color_t Teal()				{ return color_t(0,128,128); }
	static INLINE color_t Silver()				{ return color_t(192,192,192); }
	static INLINE color_t Grey()				{ return color_t(128,128,128); }
	static INLINE color_t Red()					{ return color_t(255,0,0); }
	static INLINE color_t Lime()				{ return color_t(0,255,0); }
	static INLINE color_t Yellow()				{ return color_t(255,255,0); }
	static INLINE color_t Blue()				{ return color_t(0,0,255); }
	static INLINE color_t Fuchsia()				{ return color_t(255,0,255); }
	static INLINE color_t Aqua()				{ return color_t(0,255,255); }
	static INLINE color_t White()				{ return color_t(255,255,255); }
	// ^^^  FIRST 16 COLORS  ^^^  -  VVV  THE REST OF THE 256 COLORS  VVV
	static INLINE color_t Grey0()				{ return color_t(0,0,0); }
	static INLINE color_t NavyBlue()			{ return color_t(0,0,95); }
	static INLINE color_t DarkBlue()			{ return color_t(0,0,135); }
	static INLINE color_t Blue3()				{ return color_t(0,0,175); }
	static INLINE color_t Blue3()				{ return color_t(0,0,215); }
	static INLINE color_t Blue1()				{ return color_t(0,0,255); }
	static INLINE color_t DarkGreen()			{ return color_t(0,95,0); }
	static INLINE color_t DeepSkyBlue4()		{ return color_t(0,95,95); }
	static INLINE color_t DeepSkyBlue4()		{ return color_t(0,95,135); }
	static INLINE color_t DeepSkyBlue4()		{ return color_t(0,95,175); }
	static INLINE color_t DodgerBlue3()			{ return color_t(0,95,215); }
	static INLINE color_t DodgerBlue2()			{ return color_t(0,95,255); }
	static INLINE color_t Green4()				{ return color_t(0,135,0); }
	static INLINE color_t SpringGreen4()		{ return color_t(0,135,95); }
	static INLINE color_t Turquoise4()			{ return color_t(0,135,135); }
	static INLINE color_t DeepSkyBlue3()		{ return color_t(0,135,175); }
	static INLINE color_t DeepSkyBlue3()		{ return color_t(0,135,215); }
	static INLINE color_t DodgerBlue1()			{ return color_t(0,135,255); }
	static INLINE color_t Green3()				{ return color_t(0,175,0); }
	static INLINE color_t SpringGreen3()		{ return color_t(0,175,95); }
	static INLINE color_t DarkCyan()			{ return color_t(0,175,135); }
	static INLINE color_t LightSeaGreen()		{ return color_t(0,175,175); }
	static INLINE color_t DeepSkyBlue2()		{ return color_t(0,175,215); }
	static INLINE color_t DeepSkyBlue1()		{ return color_t(0,175,255); }
	static INLINE color_t Green3()				{ return color_t(0,215,0); }
	static INLINE color_t SpringGreen3()		{ return color_t(0,215,95); }
	static INLINE color_t SpringGreen2()		{ return color_t(0,215,135); }
	static INLINE color_t Cyan3()				{ return color_t(0,215,175); }
	static INLINE color_t DarkTurquoise()		{ return color_t(0,215,215); }
	static INLINE color_t Turquoise2()			{ return color_t(0,215,255); }
	static INLINE color_t Green1()				{ return color_t(0,255,0); }
	static INLINE color_t SpringGreen2()		{ return color_t(0,255,95); }
	static INLINE color_t SpringGreen1()		{ return color_t(0,255,135); }
	static INLINE color_t MediumSpringGreen()	{ return color_t(0,255,175); }
	static INLINE color_t Cyan2()				{ return color_t(0,255,215); }
	static INLINE color_t Cyan1()				{ return color_t(0,255,255); }
	static INLINE color_t DarkRed()				{ return color_t(95,0,0); }
	static INLINE color_t DeepPink4()			{ return color_t(95,0,95); }
	static INLINE color_t Purple4()				{ return color_t(95,0,135); }
	static INLINE color_t Purple4()				{ return color_t(95,0,175); }
	static INLINE color_t Purple3()				{ return color_t(95,0,215); }
	static INLINE color_t BlueViolet()			{ return color_t(95,0,255); }
	static INLINE color_t Orange4()				{ return color_t(95,95,0); }
	static INLINE color_t Grey37()				{ return color_t(95,95,95); }
	static INLINE color_t MediumPurple4()		{ return color_t(95,95,135); }
	static INLINE color_t SlateBlue3()			{ return color_t(95,95,175); }
	static INLINE color_t SlateBlue3()			{ return color_t(95,95,215); }
	static INLINE color_t RoyalBlue1()			{ return color_t(95,95,255); }
	static INLINE color_t Chartreuse4()			{ return color_t(95,135,0); }
	static INLINE color_t DarkSeaGreen4()		{ return color_t(95,135,95); }
	static INLINE color_t PaleTurquoise4()		{ return color_t(95,135,135); }
	static INLINE color_t SteelBlue()			{ return color_t(95,135,175); }
	static INLINE color_t SteelBlue3()			{ return color_t(95,135,215); }
	static INLINE color_t CornflowerBlue()		{ return color_t(95,135,255); }
	static INLINE color_t Chartreuse3()			{ return color_t(95,175,0); }
	static INLINE color_t DarkSeaGreen4()		{ return color_t(95,175,95); }
	static INLINE color_t CadetBlue()			{ return color_t(95,175,135); }
	static INLINE color_t CadetBlue()			{ return color_t(95,175,175); }
	static INLINE color_t SkyBlue3()			{ return color_t(95,175,215); }
	static INLINE color_t SteelBlue1()			{ return color_t(95,175,255); }
	static INLINE color_t Chartreuse3()			{ return color_t(95,215,0); }
	static INLINE color_t PaleGreen3()			{ return color_t(95,215,95); }
	static INLINE color_t SeaGreen3()			{ return color_t(95,215,135); }
	static INLINE color_t Aquamarine3()			{ return color_t(95,215,175); }
	static INLINE color_t MediumTurquoise()		{ return color_t(95,215,215); }
	static INLINE color_t SteelBlue1()			{ return color_t(95,215,255); }
	static INLINE color_t Chartreuse2()			{ return color_t(95,255,0); }
	static INLINE color_t SeaGreen2()			{ return color_t(95,255,95); }
	static INLINE color_t SeaGreen1()			{ return color_t(95,255,135); }
	static INLINE color_t SeaGreen1()			{ return color_t(95,255,175); }
	static INLINE color_t Aquamarine1()			{ return color_t(95,255,215); }
	static INLINE color_t DarkSlateGray2()		{ return color_t(95,255,255); }
	static INLINE color_t DarkRed()				{ return color_t(135,0,0); }
	static INLINE color_t DeepPink4()			{ return color_t(135,0,95); }
	static INLINE color_t DarkMagenta()			{ return color_t(135,0,135); }
	static INLINE color_t DarkMagenta()			{ return color_t(135,0,175); }
	static INLINE color_t DarkViolet()			{ return color_t(135,0,215); }
	static INLINE color_t Purple()				{ return color_t(135,0,255); }
	static INLINE color_t Orange4()				{ return color_t(135,95,0); }
	static INLINE color_t LightPink4()			{ return color_t(135,95,95); }
	static INLINE color_t Plum4()				{ return color_t(135,95,135); }
	static INLINE color_t MediumPurple3()		{ return color_t(135,95,175); }
	static INLINE color_t MediumPurple3()		{ return color_t(135,95,215); }
	static INLINE color_t SlateBlue1()			{ return color_t(135,95,255); }
	static INLINE color_t Yellow4()				{ return color_t(135,135,0); }
	static INLINE color_t Wheat4()				{ return color_t(135,135,95); }
	static INLINE color_t Grey53()				{ return color_t(135,135,135); }
	static INLINE color_t LightSlateGrey()		{ return color_t(135,135,175); }
	static INLINE color_t MediumPurple()		{ return color_t(135,135,215); }
	static INLINE color_t LightSlateBlue()		{ return color_t(135,135,255); }
	static INLINE color_t Yellow4()				{ return color_t(135,175,0); }
	static INLINE color_t DarkOliveGreen3()		{ return color_t(135,175,95); }
	static INLINE color_t DarkSeaGreen()		{ return color_t(135,175,135); }
	static INLINE color_t LightSkyBlue3()		{ return color_t(135,175,175); }
	static INLINE color_t LightSkyBlue3()		{ return color_t(135,175,215); }
	static INLINE color_t SkyBlue2()			{ return color_t(135,175,255); }
	static INLINE color_t Chartreuse2()			{ return color_t(135,215,0); }
	static INLINE color_t DarkOliveGreen3()		{ return color_t(135,215,95); }
	static INLINE color_t PaleGreen3()			{ return color_t(135,215,135); }
	static INLINE color_t DarkSeaGreen3()		{ return color_t(135,215,175); }
	static INLINE color_t DarkSlateGray3()		{ return color_t(135,215,215); }
	static INLINE color_t SkyBlue1()			{ return color_t(135,215,255); }
	static INLINE color_t Chartreuse1()			{ return color_t(135,255,0); }
	static INLINE color_t LightGreen()			{ return color_t(135,255,95); }
	static INLINE color_t LightGreen()			{ return color_t(135,255,135); }
	static INLINE color_t PaleGreen1()			{ return color_t(135,255,175); }
	static INLINE color_t Aquamarine1()			{ return color_t(135,255,215); }
	static INLINE color_t DarkSlateGray1()		{ return color_t(135,255,255); }
	static INLINE color_t Red3()				{ return color_t(175,0,0); }
	static INLINE color_t DeepPink4()			{ return color_t(175,0,95); }
	static INLINE color_t MediumVioletRed()		{ return color_t(175,0,135); }
	static INLINE color_t Magenta3()			{ return color_t(175,0,175); }
	static INLINE color_t DarkViolet()			{ return color_t(175,0,215); }
	static INLINE color_t Purple()				{ return color_t(175,0,255); }
	static INLINE color_t DarkOrange3()			{ return color_t(175,95,0); }
	static INLINE color_t IndianRed()			{ return color_t(175,95,95); }
	static INLINE color_t HotPink3()			{ return color_t(175,95,135); }
	static INLINE color_t MediumOrchid3()		{ return color_t(175,95,175); }
	static INLINE color_t MediumOrchid()		{ return color_t(175,95,215); }
	static INLINE color_t MediumPurple2()		{ return color_t(175,95,255); }
	static INLINE color_t DarkGoldenrod()		{ return color_t(175,135,0); }
	static INLINE color_t LightSalmon3()		{ return color_t(175,135,95); }
	static INLINE color_t RosyBrown()			{ return color_t(175,135,135); }
	static INLINE color_t Grey63()				{ return color_t(175,135,175); }
	static INLINE color_t MediumPurple2()		{ return color_t(175,135,215); }
	static INLINE color_t MediumPurple1()		{ return color_t(175,135,255); }
	static INLINE color_t Gold3()				{ return color_t(175,175,0); }
	static INLINE color_t DarkKhaki()			{ return color_t(175,175,95); }
	static INLINE color_t NavajoWhite3()		{ return color_t(175,175,135); }
	static INLINE color_t Grey69()				{ return color_t(175,175,175); }
	static INLINE color_t LightSteelBlue3()		{ return color_t(175,175,215); }
	static INLINE color_t LightSteelBlue()		{ return color_t(175,175,255); }
	static INLINE color_t Yellow3()				{ return color_t(175,215,0); }
	static INLINE color_t DarkOliveGreen3()		{ return color_t(175,215,95); }
	static INLINE color_t DarkSeaGreen3()		{ return color_t(175,215,135); }
	static INLINE color_t DarkSeaGreen2()		{ return color_t(175,215,175); }
	static INLINE color_t LightCyan3()			{ return color_t(175,215,215); }
	static INLINE color_t LightSkyBlue1()		{ return color_t(175,215,255); }
	static INLINE color_t GreenYellow()			{ return color_t(175,255,0); }
	static INLINE color_t DarkOliveGreen2()		{ return color_t(175,255,95); }
	static INLINE color_t PaleGreen1()			{ return color_t(175,255,135); }
	static INLINE color_t DarkSeaGreen2()		{ return color_t(175,255,175); }
	static INLINE color_t DarkSeaGreen1()		{ return color_t(175,255,215); }
	static INLINE color_t PaleTurquoise1()		{ return color_t(175,255,255); }
	static INLINE color_t Red3()				{ return color_t(215,0,0); }
	static INLINE color_t DeepPink3()			{ return color_t(215,0,95); }
	static INLINE color_t DeepPink3()			{ return color_t(215,0,135); }
	static INLINE color_t Magenta3()			{ return color_t(215,0,175); }
	static INLINE color_t Magenta3()			{ return color_t(215,0,215); }
	static INLINE color_t Magenta2()			{ return color_t(215,0,255); }
	static INLINE color_t DarkOrange3()			{ return color_t(215,95,0); }
	static INLINE color_t IndianRed()			{ return color_t(215,95,95); }
	static INLINE color_t HotPink3()			{ return color_t(215,95,135); }
	static INLINE color_t HotPink2()			{ return color_t(215,95,175); }
	static INLINE color_t Orchid()				{ return color_t(215,95,215); }
	static INLINE color_t MediumOrchid1()		{ return color_t(215,95,255); }
	static INLINE color_t Orange3()				{ return color_t(215,135,0); }
	static INLINE color_t LightSalmon3()		{ return color_t(215,135,95); }
	static INLINE color_t LightPink3()			{ return color_t(215,135,135); }
	static INLINE color_t Pink3()				{ return color_t(215,135,175); }
	static INLINE color_t Plum3()				{ return color_t(215,135,215); }
	static INLINE color_t Violet()				{ return color_t(215,135,255); }
	static INLINE color_t Gold3()				{ return color_t(215,175,0); }
	static INLINE color_t LightGoldenrod3()		{ return color_t(215,175,95); }
	static INLINE color_t Tan()					{ return color_t(215,175,135); }
	static INLINE color_t MistyRose3()			{ return color_t(215,175,175); }
	static INLINE color_t Thistle3()			{ return color_t(215,175,215); }
	static INLINE color_t Plum2()				{ return color_t(215,175,255); }
	static INLINE color_t Yellow3()				{ return color_t(215,215,0); }
	static INLINE color_t Khaki3()				{ return color_t(215,215,95); }
	static INLINE color_t LightGoldenrod2()		{ return color_t(215,215,135); }
	static INLINE color_t LightYellow3()		{ return color_t(215,215,175); }
	static INLINE color_t Grey84()				{ return color_t(215,215,215); }
	static INLINE color_t LightSteelBlue1()		{ return color_t(215,215,255); }
	static INLINE color_t Yellow2()				{ return color_t(215,255,0); }
	static INLINE color_t DarkOliveGreen1()		{ return color_t(215,255,95); }
	static INLINE color_t DarkOliveGreen1()		{ return color_t(215,255,135); }
	static INLINE color_t DarkSeaGreen1()		{ return color_t(215,255,175); }
	static INLINE color_t Honeydew2()			{ return color_t(215,255,215); }
	static INLINE color_t LightCyan1()			{ return color_t(215,255,255); }
	static INLINE color_t Red1()				{ return color_t(255,0,0); }
	static INLINE color_t DeepPink2()			{ return color_t(255,0,95); }
	static INLINE color_t DeepPink1()			{ return color_t(255,0,135); }
	static INLINE color_t DeepPink1()			{ return color_t(255,0,175); }
	static INLINE color_t Magenta2()			{ return color_t(255,0,215); }
	static INLINE color_t Magenta1()			{ return color_t(255,0,255); }
	static INLINE color_t OrangeRed1()			{ return color_t(255,95,0); }
	static INLINE color_t IndianRed1()			{ return color_t(255,95,95); }
	static INLINE color_t IndianRed1()			{ return color_t(255,95,135); }
	static INLINE color_t HotPink()				{ return color_t(255,95,175); }
	static INLINE color_t HotPink()				{ return color_t(255,95,215); }
	static INLINE color_t MediumOrchid1()		{ return color_t(255,95,255); }
	static INLINE color_t DarkOrange()			{ return color_t(255,135,0); }
	static INLINE color_t Salmon1()				{ return color_t(255,135,95); }
	static INLINE color_t LightCoral()			{ return color_t(255,135,135); }
	static INLINE color_t PaleVioletRed1()		{ return color_t(255,135,175); }
	static INLINE color_t Orchid2()				{ return color_t(255,135,215); }
	static INLINE color_t Orchid1()				{ return color_t(255,135,255); }
	static INLINE color_t Orange1()				{ return color_t(255,175,0); }
	static INLINE color_t SandyBrown()			{ return color_t(255,175,95); }
	static INLINE color_t LightSalmon1()		{ return color_t(255,175,135); }
	static INLINE color_t LightPink1()			{ return color_t(255,175,175); }
	static INLINE color_t Pink1()				{ return color_t(255,175,215); }
	static INLINE color_t Plum1()				{ return color_t(255,175,255); }
	static INLINE color_t Gold1()				{ return color_t(255,215,0); }
	static INLINE color_t LightGoldenrod2()		{ return color_t(255,215,95); }
	static INLINE color_t LightGoldenrod2()		{ return color_t(255,215,135); }
	static INLINE color_t NavajoWhite1()		{ return color_t(255,215,175); }
	static INLINE color_t MistyRose1()			{ return color_t(255,215,215); }
	static INLINE color_t Thistle1()			{ return color_t(255,215,255); }
	static INLINE color_t Yellow1()				{ return color_t(255,255,0); }
	static INLINE color_t LightGoldenrod1()		{ return color_t(255,255,95); }
	static INLINE color_t Khaki1()				{ return color_t(255,255,135); }
	static INLINE color_t Wheat1()				{ return color_t(255,255,175); }
	static INLINE color_t Cornsilk1()			{ return color_t(255,255,215); }
	static INLINE color_t Grey100()				{ return color_t(255,255,255); }
	static INLINE color_t Grey3()				{ return color_t(8,8,8); }
	static INLINE color_t Grey7()				{ return color_t(18,18,18); }
	static INLINE color_t Grey11()				{ return color_t(28,28,28); }
	static INLINE color_t Grey15()				{ return color_t(38,38,38); }
	static INLINE color_t Grey19()				{ return color_t(48,48,48); }
	static INLINE color_t Grey23()				{ return color_t(58,58,58); }
	static INLINE color_t Grey27()				{ return color_t(68,68,68); }
	static INLINE color_t Grey30()				{ return color_t(78,78,78); }
	static INLINE color_t Grey35()				{ return color_t(88,88,88); }
	static INLINE color_t Grey39()				{ return color_t(98,98,98); }
	static INLINE color_t Grey42()				{ return color_t(108,108,108); }
	static INLINE color_t Grey46()				{ return color_t(118,118,118); }
	static INLINE color_t Grey50()				{ return color_t(128,128,128); }
	static INLINE color_t Grey54()				{ return color_t(138,138,138); }
	static INLINE color_t Grey58()				{ return color_t(148,148,148); }
	static INLINE color_t Grey62()				{ return color_t(158,158,158); }
	static INLINE color_t Grey66()				{ return color_t(168,168,168); }
	static INLINE color_t Grey70()				{ return color_t(178,178,178); }
	static INLINE color_t Grey74()				{ return color_t(188,188,188); }
	static INLINE color_t Grey78()				{ return color_t(198,198,198); }
	static INLINE color_t Grey82()				{ return color_t(208,208,208); }
	static INLINE color_t Grey85()				{ return color_t(218,218,218); }
	static INLINE color_t Grey89()				{ return color_t(228,228,228); }
	static INLINE color_t Grey93()				{ return color_t(238,238,238); }
};




#endif //__color_h__
