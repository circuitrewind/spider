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
	// COLOR FROM A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t(uint32_t color) {
		this->g = (color >>  8) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->b = (color >>  0) & 0xff;
	}




	////////////////////////////////////////////////////////////////////////////
	// GETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE operator uint32_t() const {
		return (this->r << 16) | (this->g << 8) | (this->b << 0);
	}




	////////////////////////////////////////////////////////////////////////////
	// SETTER AS A 32-BIT INTEGER IN TRADITIONAL 0X00RRGGBB ORDER
	////////////////////////////////////////////////////////////////////////////
	INLINE uint32_t operator =(uint32_t color) {
		this->g = (color >>  8) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->b = (color >>  0) & 0xff;
		return color;
	}




	////////////////////////////////////////////////////////////////////////////
	// INCREASE VALUE
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t add(uint8_t value) {
		return this->add(value, value, value);
	}

	INLINE color_t add(uint8_t r, uint8_t g, uint8_t b) {
		this->g += g;
		this->r += r;
		this->b += b;
		return this;
	}




	////////////////////////////////////////////////////////////////////////////
	// DECREASE VALUE
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t sub(uint8_t value) {
		return this->sub(value, value, value);
	}

	INLINE color_t sub(uint8_t r, uint8_t g, uint8_t b) {
		this->g -= g;
		this->r -= r;
		this->b -= b;
		return this;
	}




	////////////////////////////////////////////////////////////////////////////
	// SHIFT VALUE RIGHT
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t right(uint8_t value) {
		return this->right(value, value, value);
	}

	INLINE color_t right(uint8_t r, uint8_t g, uint8_t b) {
		this->g >>= g;
		this->r >>= r;
		this->b >>= b;
		return this;
	}




	////////////////////////////////////////////////////////////////////////////
	// SHIFT VALUE LEFT
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t left(uint8_t value) {
		return this->left(value, value, value);
	}

	INLINE color_t left(uint8_t r, uint8_t g, uint8_t b) {
		this->g <<= g;
		this->r <<= r;
		this->b <<= b;
		return this;
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
	// VGA COLOR NAMES - THESE ARE ALSO THE HTML COLOR CODE NAMES
	// SOURCE: http://www.blooberry.com/indexdot/color/vganame.htm
	////////////////////////////////////////////////////////////////////////////
	static INLINE color_t black()					{ return color_t(); }
	static INLINE color_t white()					{ return 0xffffff; }
	static INLINE color_t red()						{ return 0xff0000; }
	static INLINE color_t yellow()					{ return 0xffff00; }
	static INLINE color_t lime()					{ return 0x00ff00; }
	static INLINE color_t aqua()					{ return 0x00ffff; }
	static INLINE color_t blue()					{ return 0x0000ff; }
	static INLINE color_t fuchsia()					{ return 0xff00ff; }
	static INLINE color_t orange()					{ return 0xffa500; }
	static INLINE color_t gray()					{ return 0x808080; }
	static INLINE color_t silver()					{ return 0xc0c0c0; }
	static INLINE color_t maroon()					{ return 0x800000; }
	static INLINE color_t olive()					{ return 0x808000; }
	static INLINE color_t green()					{ return 0x008000; }
	static INLINE color_t teal()					{ return 0x008080; }
	static INLINE color_t navy()					{ return 0x000080; }
	static INLINE color_t purple()					{ return 0x800080; }




	////////////////////////////////////////////////////////////////////////////
	// X11 COLOR CODES - THESE ARE ALSO THE HTML COLOR CODE NAMES
	// SOURCE: https://www.w3schools.com/colors/colors_x11.asp
	////////////////////////////////////////////////////////////////////////////
	static INLINE color_t aliceblue()				{ return 0xf0f8ff; }
	static INLINE color_t antiquewhite()			{ return 0xfaebd7; }
	static INLINE color_t antiquewhite1()			{ return 0xffefdb; }
	static INLINE color_t antiquewhite2()			{ return 0xeedfcc; }
	static INLINE color_t antiquewhite3()			{ return 0xcdc0b0; }
	static INLINE color_t antiquewhite4()			{ return 0x8b8378; }
	static INLINE color_t aquamarine1()				{ return 0x7fffd4; }
	static INLINE color_t aquamarine2()				{ return 0x76eec6; }
	static INLINE color_t aquamarine4()				{ return 0x458b74; }
	static INLINE color_t azure1()					{ return 0xf0ffff; }
	static INLINE color_t azure2()					{ return 0xe0eeee; }
	static INLINE color_t azure3()					{ return 0xc1cdcd; }
	static INLINE color_t azure4()					{ return 0x838b8b; }
	static INLINE color_t beige()					{ return 0xf5f5dc; }
	static INLINE color_t bisque1()					{ return 0xffe4c4; }
	static INLINE color_t bisque2()					{ return 0xeed5b7; }
	static INLINE color_t bisque3()					{ return 0xcdb79e; }
	static INLINE color_t bisque4()					{ return 0x8b7d6b; }
	static INLINE color_t blanchedalmond()			{ return 0xffebcd; }
	static INLINE color_t blue1()					{ return 0x0000ff; }
	static INLINE color_t blue2()					{ return 0x0000ee; }
	static INLINE color_t blue4()					{ return 0x00008b; }
	static INLINE color_t blueviolet()				{ return 0x8a2be2; }
	static INLINE color_t brown()					{ return 0xa52a2a; }
	static INLINE color_t brown1()					{ return 0xff4040; }
	static INLINE color_t brown2()					{ return 0xee3b3b; }
	static INLINE color_t brown3()					{ return 0xcd3333; }
	static INLINE color_t brown4()					{ return 0x8b2323; }
	static INLINE color_t burlywood()				{ return 0xdeb887; }
	static INLINE color_t burlywood1()				{ return 0xffd39b; }
	static INLINE color_t burlywood2()				{ return 0xeec591; }
	static INLINE color_t burlywood3()				{ return 0xcdaa7d; }
	static INLINE color_t burlywood4()				{ return 0x8b7355; }
	static INLINE color_t cadetblue()				{ return 0x5f9ea0; }
	static INLINE color_t cadetblue1()				{ return 0x98f5ff; }
	static INLINE color_t cadetblue2()				{ return 0x8ee5ee; }
	static INLINE color_t cadetblue3()				{ return 0x7ac5cd; }
	static INLINE color_t cadetblue4()				{ return 0x53868b; }
	static INLINE color_t chartreuse1()				{ return 0x7fff00; }
	static INLINE color_t chartreuse2()				{ return 0x76ee00; }
	static INLINE color_t chartreuse3()				{ return 0x66cd00; }
	static INLINE color_t chartreuse4()				{ return 0x458b00; }
	static INLINE color_t chocolate()				{ return 0xd2691e; }
	static INLINE color_t chocolate1()				{ return 0xff7f24; }
	static INLINE color_t chocolate2()				{ return 0xee7621; }
	static INLINE color_t chocolate3()				{ return 0xcd661d; }
	static INLINE color_t coral()					{ return 0xff7f50; }
	static INLINE color_t coral1()					{ return 0xff7256; }
	static INLINE color_t coral2()					{ return 0xee6a50; }
	static INLINE color_t coral3()					{ return 0xcd5b45; }
	static INLINE color_t coral4()					{ return 0x8b3e2f; }
	static INLINE color_t cornflowerblue()			{ return 0x6495ed; }
	static INLINE color_t cornsilk1()				{ return 0xfff8dc; }
	static INLINE color_t ornsilk2()				{ return 0xeee8cd; }
	static INLINE color_t cornsilk3()				{ return 0xcdc8b1; }
	static INLINE color_t cornsilk4()				{ return 0x8b8878; }
	static INLINE color_t cyan1()					{ return 0x00ffff; }
	static INLINE color_t cyan2()					{ return 0x00eeee; }
	static INLINE color_t cyan3()					{ return 0x00cdcd; }
	static INLINE color_t cyan4()					{ return 0x008b8b; }
	static INLINE color_t darkgoldenrod()			{ return 0xb8860b; }
	static INLINE color_t darkgoldenrod1()			{ return 0xffb90f; }
	static INLINE color_t darkgoldenrod2()			{ return 0xeead0e; }
	static INLINE color_t darkgoldenrod3()			{ return 0xcd950c; }
	static INLINE color_t darkgoldenrod4()			{ return 0x8b6508; }
	static INLINE color_t darkgreen()				{ return 0x006400; }
	static INLINE color_t darkkhaki()				{ return 0xbdb76b; }
	static INLINE color_t darkolivegreen()			{ return 0x556b2f; }
	static INLINE color_t darkolivegreen1()			{ return 0xcaff70; }
	static INLINE color_t darkolivegreen2()			{ return 0xbcee68; }
	static INLINE color_t darkolivegreen3()			{ return 0xa2cd5a; }
	static INLINE color_t darkolivegreen4()			{ return 0x6e8b3d; }
	static INLINE color_t darkorange()				{ return 0xff8c00; }
	static INLINE color_t darkorange1()				{ return 0xff7f00; }
	static INLINE color_t darkorange2()				{ return 0xee7600; }
	static INLINE color_t darkorange3()				{ return 0xcd6600; }
	static INLINE color_t darkorange4()				{ return 0x8b4500; }
	static INLINE color_t darkorchid()				{ return 0x9932cc; }
	static INLINE color_t darkorchid1()				{ return 0xbf3eff; }
	static INLINE color_t darkorchid2()				{ return 0xb23aee; }
	static INLINE color_t darkorchid3()				{ return 0x9a32cd; }
	static INLINE color_t darkorchid4()				{ return 0x68228b; }
	static INLINE color_t darksalmon()				{ return 0xe9967a; }
	static INLINE color_t darkseagreen()			{ return 0x8fbc8f; }
	static INLINE color_t darkseagreen1()			{ return 0xc1ffc1; }
	static INLINE color_t darkseagreen2()			{ return 0xb4eeb4; }
	static INLINE color_t darkseagreen3()			{ return 0x9bcd9b; }
	static INLINE color_t darkseagreen4()			{ return 0x698b69; }
	static INLINE color_t darkslateblue()			{ return 0x483d8b; }
	static INLINE color_t darkslategray()			{ return 0x2f4f4f; }
	static INLINE color_t darkslategray1()			{ return 0x97ffff; }
	static INLINE color_t darkslategray2()			{ return 0x8deeee; }
	static INLINE color_t darkslategray3()			{ return 0x79cdcd; }
	static INLINE color_t darkslategray4()			{ return 0x528b8b; }
	static INLINE color_t darkturquoise()			{ return 0x00ced1; }
	static INLINE color_t darkviolet()				{ return 0x9400d3; }
	static INLINE color_t deeppink1()				{ return 0xff1493; }
	static INLINE color_t deeppink2()				{ return 0xee1289; }
	static INLINE color_t deeppink3()				{ return 0xcd1076; }
	static INLINE color_t deeppink4()				{ return 0x8b0a50; }
	static INLINE color_t deepskyblue1()			{ return 0x00bfff; }
	static INLINE color_t deepskyblue2()			{ return 0x00b2ee; }
	static INLINE color_t deepskyblue3()			{ return 0x009acd; }
	static INLINE color_t deepskyblue4()			{ return 0x00688b; }
	static INLINE color_t dimgray()					{ return 0x696969; }
	static INLINE color_t dodgerblue1()				{ return 0x1e90ff; }
	static INLINE color_t dodgerblue2()				{ return 0x1c86ee; }
	static INLINE color_t dodgerblue3()				{ return 0x1874cd; }
	static INLINE color_t dodgerblue4()				{ return 0x104e8b; }
	static INLINE color_t firebrick()				{ return 0xb22222; }
	static INLINE color_t firebrick1()				{ return 0xff3030; }
	static INLINE color_t firebrick2()				{ return 0xee2c2c; }
	static INLINE color_t firebrick3()				{ return 0xcd2626; }
	static INLINE color_t firebrick4()				{ return 0x8b1a1a; }
	static INLINE color_t floralwhite()				{ return 0xfffaf0; }
	static INLINE color_t forestgreen()				{ return 0x228b22; }
	static INLINE color_t gainsboro()				{ return 0xdcdcdc; }
	static INLINE color_t ghostwhite()				{ return 0xf8f8ff; }
	static INLINE color_t gold1()					{ return 0xffd700; }
	static INLINE color_t gold2()					{ return 0xeec900; }
	static INLINE color_t gold3()					{ return 0xcdad00; }
	static INLINE color_t gold4()					{ return 0x8b7500; }
	static INLINE color_t goldenrod()				{ return 0xdaa520; }
	static INLINE color_t goldenrod1()				{ return 0xffc125; }
	static INLINE color_t goldenrod2()				{ return 0xeeb422; }
	static INLINE color_t goldenrod3()				{ return 0xcd9b1d; }
	static INLINE color_t goldenrod4()				{ return 0x8b6914; }
	static INLINE color_t gray0()					{ return 0xbebebe; }
	static INLINE color_t gray1()					{ return 0x030303; }
	static INLINE color_t gray2()					{ return 0x050505; }
	static INLINE color_t gray3()					{ return 0x080808; }
	static INLINE color_t gray4()					{ return 0x0a0a0a; }
	static INLINE color_t gray5()					{ return 0x0d0d0d; }
	static INLINE color_t gray6()					{ return 0x0f0f0f; }
	static INLINE color_t gray7()					{ return 0x121212; }
	static INLINE color_t gray8()					{ return 0x141414; }
	static INLINE color_t gray9()					{ return 0x171717; }
	static INLINE color_t gray10()					{ return 0x1a1a1a; }
	static INLINE color_t gray11()					{ return 0x1c1c1c; }
	static INLINE color_t gray12()					{ return 0x1f1f1f; }
	static INLINE color_t gray13()					{ return 0x212121; }
	static INLINE color_t gray14()					{ return 0x242424; }
	static INLINE color_t gray15()					{ return 0x262626; }
	static INLINE color_t gray16()					{ return 0x292929; }
	static INLINE color_t gray17()					{ return 0x2b2b2b; }
	static INLINE color_t gray18()					{ return 0x2e2e2e; }
	static INLINE color_t gray19()					{ return 0x303030; }
	static INLINE color_t gray20()					{ return 0x333333; }
	static INLINE color_t gray21()					{ return 0x363636; }
	static INLINE color_t gray22()					{ return 0x383838; }
	static INLINE color_t gray23()					{ return 0x3b3b3b; }
	static INLINE color_t gray24()					{ return 0x3d3d3d; }
	static INLINE color_t gray25()					{ return 0x404040; }
	static INLINE color_t gray26()					{ return 0x424242; }
	static INLINE color_t gray27()					{ return 0x454545; }
	static INLINE color_t gray28()					{ return 0x474747; }
	static INLINE color_t gray29()					{ return 0x4a4a4a; }
	static INLINE color_t gray30()					{ return 0x4d4d4d; }
	static INLINE color_t gray31()					{ return 0x4f4f4f; }
	static INLINE color_t gray32()					{ return 0x525252; }
	static INLINE color_t gray33()					{ return 0x545454; }
	static INLINE color_t gray34()					{ return 0x575757; }
	static INLINE color_t gray35()					{ return 0x595959; }
	static INLINE color_t gray36()					{ return 0x5c5c5c; }
	static INLINE color_t gray37()					{ return 0x5e5e5e; }
	static INLINE color_t gray38()					{ return 0x616161; }
	static INLINE color_t gray39()					{ return 0x636363; }
	static INLINE color_t gray40()					{ return 0x666666; }
	static INLINE color_t gray41()					{ return 0x696969; }
	static INLINE color_t gray42()					{ return 0x6b6b6b; }
	static INLINE color_t gray43()					{ return 0x6e6e6e; }
	static INLINE color_t gray44()					{ return 0x707070; }
	static INLINE color_t gray45()					{ return 0x737373; }
	static INLINE color_t gray46()					{ return 0x757575; }
	static INLINE color_t gray47()					{ return 0x787878; }
	static INLINE color_t gray48()					{ return 0x7a7a7a; }
	static INLINE color_t gray49()					{ return 0x7d7d7d; }
	static INLINE color_t gray50()					{ return 0x7f7f7f; }
	static INLINE color_t gray51()					{ return 0x828282; }
	static INLINE color_t gray52()					{ return 0x858585; }
	static INLINE color_t gray53()					{ return 0x878787; }
	static INLINE color_t gray54()					{ return 0x8a8a8a; }
	static INLINE color_t gray55()					{ return 0x8c8c8c; }
	static INLINE color_t gray56()					{ return 0x8f8f8f; }
	static INLINE color_t gray57()					{ return 0x919191; }
	static INLINE color_t gray58()					{ return 0x949494; }
	static INLINE color_t gray59()					{ return 0x969696; }
	static INLINE color_t gray60()					{ return 0x999999; }
	static INLINE color_t gray61()					{ return 0x9c9c9c; }
	static INLINE color_t gray62()					{ return 0x9e9e9e; }
	static INLINE color_t gray63()					{ return 0xa1a1a1; }
	static INLINE color_t gray64()					{ return 0xa3a3a3; }
	static INLINE color_t gray65()					{ return 0xa6a6a6; }
	static INLINE color_t gray66()					{ return 0xa8a8a8; }
	static INLINE color_t gray67()					{ return 0xababab; }
	static INLINE color_t gray68()					{ return 0xadadad; }
	static INLINE color_t gray69()					{ return 0xb0b0b0; }
	static INLINE color_t gray70()					{ return 0xb3b3b3; }
	static INLINE color_t gray71()					{ return 0xb5b5b5; }
	static INLINE color_t gray72()					{ return 0xb8b8b8; }
	static INLINE color_t gray73()					{ return 0xbababa; }
	static INLINE color_t gray74()					{ return 0xbdbdbd; }
	static INLINE color_t gray75()					{ return 0xbfbfbf; }
	static INLINE color_t gray76()					{ return 0xc2c2c2; }
	static INLINE color_t gray77()					{ return 0xc4c4c4; }
	static INLINE color_t gray78()					{ return 0xc7c7c7; }
	static INLINE color_t gray79()					{ return 0xc9c9c9; }
	static INLINE color_t gray80()					{ return 0xcccccc; }
	static INLINE color_t gray81()					{ return 0xcfcfcf; }
	static INLINE color_t gray82()					{ return 0xd1d1d1; }
	static INLINE color_t gray83()					{ return 0xd4d4d4; }
	static INLINE color_t gray84()					{ return 0xd6d6d6; }
	static INLINE color_t gray85()					{ return 0xd9d9d9; }
	static INLINE color_t gray86()					{ return 0xdbdbdb; }
	static INLINE color_t gray87()					{ return 0xdedede; }
	static INLINE color_t gray88()					{ return 0xe0e0e0; }
	static INLINE color_t gray89()					{ return 0xe3e3e3; }
	static INLINE color_t gray90()					{ return 0xe5e5e5; }
	static INLINE color_t gray91()					{ return 0xe8e8e8; }
	static INLINE color_t gray92()					{ return 0xebebeb; }
	static INLINE color_t gray93()					{ return 0xededed; }
	static INLINE color_t gray94()					{ return 0xf0f0f0; }
	static INLINE color_t gray95()					{ return 0xf2f2f2; }
	static INLINE color_t gray97()					{ return 0xf7f7f7; }
	static INLINE color_t gray98()					{ return 0xfafafa; }
	static INLINE color_t gray99()					{ return 0xfcfcfc; }
	static INLINE color_t green1()					{ return 0x00ff00; }
	static INLINE color_t green2()					{ return 0x00ee00; }
	static INLINE color_t green3()					{ return 0x00cd00; }
	static INLINE color_t green4()					{ return 0x008b00; }
	static INLINE color_t greenyellow()				{ return 0xadff2f; }
	static INLINE color_t honeydew1()				{ return 0xf0fff0; }
	static INLINE color_t honeydew2()				{ return 0xe0eee0; }
	static INLINE color_t honeydew3()				{ return 0xc1cdc1; }
	static INLINE color_t honeydew4()				{ return 0x838b83; }
	static INLINE color_t hotpink()					{ return 0xff69b4; }
	static INLINE color_t hotpink1()				{ return 0xff6eb4; }
	static INLINE color_t hotpink2()				{ return 0xee6aa7; }
	static INLINE color_t hotpink3()				{ return 0xcd6090; }
	static INLINE color_t hotpink4()				{ return 0x8b3a62; }
	static INLINE color_t indianred()				{ return 0xcd5c5c; }
	static INLINE color_t indianred1()				{ return 0xff6a6a; }
	static INLINE color_t indianred2()				{ return 0xee6363; }
	static INLINE color_t indianred3()				{ return 0xcd5555; }
	static INLINE color_t indianred4()				{ return 0x8b3a3a; }
	static INLINE color_t ivory1()					{ return 0xfffff0; }
	static INLINE color_t ivory2()					{ return 0xeeeee0; }
	static INLINE color_t ivory3()					{ return 0xcdcdc1; }
	static INLINE color_t ivory4()					{ return 0x8b8b83; }
	static INLINE color_t khaki()					{ return 0xf0e68c; }
	static INLINE color_t khaki1()					{ return 0xfff68f; }
	static INLINE color_t khaki2()					{ return 0xeee685; }
	static INLINE color_t khaki3()					{ return 0xcdc673; }
	static INLINE color_t khaki4()					{ return 0x8b864e; }
	static INLINE color_t lavender()				{ return 0xe6e6fa; }
	static INLINE color_t lavenderblush1()			{ return 0xfff0f5; }
	static INLINE color_t lavenderblush2()			{ return 0xeee0e5; }
	static INLINE color_t lavenderblush3()			{ return 0xcdc1c5; }
	static INLINE color_t lavenderblush4()			{ return 0x8b8386; }
	static INLINE color_t lawngreen()				{ return 0x7cfc00; }
	static INLINE color_t lemonchiffon1()			{ return 0xfffacd; }
	static INLINE color_t lemonchiffon2()			{ return 0xeee9bf; }
	static INLINE color_t lemonchiffon3()			{ return 0xcdc9a5; }
	static INLINE color_t lemonchiffon4()			{ return 0x8b8970; }
	static INLINE color_t light()					{ return 0xeedd82; }
	static INLINE color_t lightblue()				{ return 0xadd8e6; }
	static INLINE color_t lightblue1()				{ return 0xbfefff; }
	static INLINE color_t lightblue2()				{ return 0xb2dfee; }
	static INLINE color_t lightblue3()				{ return 0x9ac0cd; }
	static INLINE color_t lightblue4()				{ return 0x68838b; }
	static INLINE color_t lightcoral()				{ return 0xf08080; }
	static INLINE color_t lightcyan1()				{ return 0xe0ffff; }
	static INLINE color_t lightcyan2()				{ return 0xd1eeee; }
	static INLINE color_t lightcyan3()				{ return 0xb4cdcd; }
	static INLINE color_t lightcyan4()				{ return 0x7a8b8b; }
	static INLINE color_t lightgoldenrod1()			{ return 0xffec8b; }
	static INLINE color_t lightgoldenrod2()			{ return 0xeedc82; }
	static INLINE color_t lightgoldenrod3()			{ return 0xcdbe70; }
	static INLINE color_t lightgoldenrod4()			{ return 0x8b814c; }
	static INLINE color_t lightgoldenrodyellow()	{ return 0xfafad2; }
	static INLINE color_t lightgray()				{ return 0xd3d3d3; }
	static INLINE color_t lightpink()				{ return 0xffb6c1; }
	static INLINE color_t lightpink1()				{ return 0xffaeb9; }
	static INLINE color_t lightpink2()				{ return 0xeea2ad; }
	static INLINE color_t lightpink3()				{ return 0xcd8c95; }
	static INLINE color_t lightpink4()				{ return 0x8b5f65; }
	static INLINE color_t lightsalmon1()			{ return 0xffa07a; }
	static INLINE color_t lightsalmon2()			{ return 0xee9572; }
	static INLINE color_t lightsalmon3()			{ return 0xcd8162; }
	static INLINE color_t lightsalmon4()			{ return 0x8b5742; }
	static INLINE color_t lightseagreen()			{ return 0x20b2aa; }
	static INLINE color_t lightskyblue()			{ return 0x87cefa; }
	static INLINE color_t lightskyblue1()			{ return 0xb0e2ff; }
	static INLINE color_t lightskyblue2()			{ return 0xa4d3ee; }
	static INLINE color_t lightskyblue3()			{ return 0x8db6cd; }
	static INLINE color_t lightskyblue4()			{ return 0x607b8b; }
	static INLINE color_t lightslateblue()			{ return 0x8470ff; }
	static INLINE color_t lightslategray()			{ return 0x778899; }
	static INLINE color_t lightsteelblue()			{ return 0xb0c4de; }
	static INLINE color_t lightsteelblue1()			{ return 0xcae1ff; }
	static INLINE color_t lightsteelblue2()			{ return 0xbcd2ee; }
	static INLINE color_t lightsteelblue3()			{ return 0xa2b5cd; }
	static INLINE color_t lightsteelblue4()			{ return 0x6e7b8b; }
	static INLINE color_t lightyellow1()			{ return 0xffffe0; }
	static INLINE color_t lightyellow2()			{ return 0xeeeed1; }
	static INLINE color_t lightyellow3()			{ return 0xcdcdb4; }
	static INLINE color_t lightyellow4()			{ return 0x8b8b7a; }
	static INLINE color_t limegreen()				{ return 0x32cd32; }
	static INLINE color_t linen()					{ return 0xfaf0e6; }
	static INLINE color_t magenta()					{ return 0xff00ff; }
	static INLINE color_t magenta2()				{ return 0xee00ee; }
	static INLINE color_t magenta3()				{ return 0xcd00cd; }
	static INLINE color_t magenta4()				{ return 0x8b008b; }
	static INLINE color_t maroon0()					{ return 0xb03060; }
	static INLINE color_t maroon1()					{ return 0xff34b3; }
	static INLINE color_t maroon2()					{ return 0xee30a7; }
	static INLINE color_t maroon3()					{ return 0xcd2990; }
	static INLINE color_t maroon4()					{ return 0x8b1c62; }
	static INLINE color_t medium()					{ return 0x66cdaa; }
	static INLINE color_t mediumaquamarine()		{ return 0x66cdaa; }
	static INLINE color_t mediumblue()				{ return 0x0000cd; }
	static INLINE color_t mediumorchid()			{ return 0xba55d3; }
	static INLINE color_t mediumorchid1()			{ return 0xe066ff; }
	static INLINE color_t mediumorchid2()			{ return 0xd15fee; }
	static INLINE color_t mediumorchid3()			{ return 0xb452cd; }
	static INLINE color_t mediumorchid4()			{ return 0x7a378b; }
	static INLINE color_t mediumpurple()			{ return 0x9370db; }
	static INLINE color_t mediumpurple1()			{ return 0xab82ff; }
	static INLINE color_t mediumpurple2()			{ return 0x9f79ee; }
	static INLINE color_t mediumpurple3()			{ return 0x8968cd; }
	static INLINE color_t mediumpurple4()			{ return 0x5d478b; }
	static INLINE color_t mediumseagreen()			{ return 0x3cb371; }
	static INLINE color_t mediumslateblue()			{ return 0x7b68ee; }
	static INLINE color_t mediumspringgreen()		{ return 0x00fa9a; }
	static INLINE color_t mediumturquoise()			{ return 0x48d1cc; }
	static INLINE color_t mediumvioletred()			{ return 0xc71585; }
	static INLINE color_t midnightblue()			{ return 0x191970; }
	static INLINE color_t mintcream()				{ return 0xf5fffa; }
	static INLINE color_t mistyrose1()				{ return 0xffe4e1; }
	static INLINE color_t mistyrose2()				{ return 0xeed5d2; }
	static INLINE color_t mistyrose3()				{ return 0xcdb7b5; }
	static INLINE color_t mistyrose4()				{ return 0x8b7d7b; }
	static INLINE color_t moccasin()				{ return 0xffe4b5; }
	static INLINE color_t navajowhite1()			{ return 0xffdead; }
	static INLINE color_t navajowhite2()			{ return 0xeecfa1; }
	static INLINE color_t navajowhite3()			{ return 0xcdb38b; }
	static INLINE color_t navajowhite4()			{ return 0x8b795e; }
	static INLINE color_t navyblue()				{ return 0x000080; }
	static INLINE color_t oldlace()					{ return 0xfdf5e6; }
	static INLINE color_t olivedrab()				{ return 0x6b8e23; }
	static INLINE color_t olivedrab1()				{ return 0xc0ff3e; }
	static INLINE color_t olivedrab2()				{ return 0xb3ee3a; }
	static INLINE color_t olivedrab4()				{ return 0x698b22; }
	static INLINE color_t orange1()					{ return 0xffa500; }
	static INLINE color_t orange2()					{ return 0xee9a00; }
	static INLINE color_t orange3()					{ return 0xcd8500; }
	static INLINE color_t orange4()					{ return 0x8b5a00; }
	static INLINE color_t orangered1()				{ return 0xff4500; }
	static INLINE color_t orangered2()				{ return 0xee4000; }
	static INLINE color_t orangered3()				{ return 0xcd3700; }
	static INLINE color_t orangered4()				{ return 0x8b2500; }
	static INLINE color_t orchid()					{ return 0xda70d6; }
	static INLINE color_t orchid1()					{ return 0xff83fa; }
	static INLINE color_t orchid2()					{ return 0xee7ae9; }
	static INLINE color_t orchid3()					{ return 0xcd69c9; }
	static INLINE color_t orchid4()					{ return 0x8b4789; }
	static INLINE color_t pale()					{ return 0xdb7093; }
	static INLINE color_t palegoldenrod()			{ return 0xeee8aa; }
	static INLINE color_t palegreen()				{ return 0x98fb98; }
	static INLINE color_t palegreen1()				{ return 0x9aff9a; }
	static INLINE color_t palegreen2()				{ return 0x90ee90; }
	static INLINE color_t palegreen3()				{ return 0x7ccd7c; }
	static INLINE color_t palegreen4()				{ return 0x548b54; }
	static INLINE color_t paleturquoise()			{ return 0xafeeee; }
	static INLINE color_t paleturquoise1()			{ return 0xbbffff; }
	static INLINE color_t paleturquoise2()			{ return 0xaeeeee; }
	static INLINE color_t paleturquoise3()			{ return 0x96cdcd; }
	static INLINE color_t paleturquoise4()			{ return 0x668b8b; }
	static INLINE color_t palevioletred()			{ return 0xdb7093; }
	static INLINE color_t palevioletred1()			{ return 0xff82ab; }
	static INLINE color_t palevioletred2()			{ return 0xee799f; }
	static INLINE color_t palevioletred3()			{ return 0xcd6889; }
	static INLINE color_t palevioletred4()			{ return 0x8b475d; }
	static INLINE color_t papayawhip()				{ return 0xffefd5; }
	static INLINE color_t peachpuff1()				{ return 0xffdab9; }
	static INLINE color_t peachpuff2()				{ return 0xeecbad; }
	static INLINE color_t peachpuff3()				{ return 0xcdaf95; }
	static INLINE color_t peachpuff4()				{ return 0x8b7765; }
	static INLINE color_t pink()					{ return 0xffc0cb; }
	static INLINE color_t pink1()					{ return 0xffb5c5; }
	static INLINE color_t pink2()					{ return 0xeea9b8; }
	static INLINE color_t pink3()					{ return 0xcd919e; }
	static INLINE color_t pink4()					{ return 0x8b636c; }
	static INLINE color_t plum()					{ return 0xdda0dd; }
	static INLINE color_t plum1()					{ return 0xffbbff; }
	static INLINE color_t plum2()					{ return 0xeeaeee; }
	static INLINE color_t plum3()					{ return 0xcd96cd; }
	static INLINE color_t plum4()					{ return 0x8b668b; }
	static INLINE color_t powderblue()				{ return 0xb0e0e6; }
	static INLINE color_t purple0()					{ return 0xa020f0; }
	static INLINE color_t purple1()					{ return 0x9b30ff; }
	static INLINE color_t purple2()					{ return 0x912cee; }
	static INLINE color_t purple3()					{ return 0x7d26cd; }
	static INLINE color_t purple4()					{ return 0x551a8b; }
	static INLINE color_t red1()					{ return 0xff0000; }
	static INLINE color_t red2()					{ return 0xee0000; }
	static INLINE color_t red3()					{ return 0xcd0000; }
	static INLINE color_t red4()					{ return 0x8b0000; }
	static INLINE color_t rosybrown()				{ return 0xbc8f8f; }
	static INLINE color_t rosybrown1()				{ return 0xffc1c1; }
	static INLINE color_t rosybrown2()				{ return 0xeeb4b4; }
	static INLINE color_t rosybrown3()				{ return 0xcd9b9b; }
	static INLINE color_t rosybrown4()				{ return 0x8b6969; }
	static INLINE color_t royalblue()				{ return 0x4169e1; }
	static INLINE color_t royalblue1()				{ return 0x4876ff; }
	static INLINE color_t royalblue2()				{ return 0x436eee; }
	static INLINE color_t royalblue3()				{ return 0x3a5fcd; }
	static INLINE color_t royalblue4()				{ return 0x27408b; }
	static INLINE color_t saddlebrown()				{ return 0x8b4513; }
	static INLINE color_t salmon()					{ return 0xfa8072; }
	static INLINE color_t salmon1()					{ return 0xff8c69; }
	static INLINE color_t salmon2()					{ return 0xee8262; }
	static INLINE color_t salmon3()					{ return 0xcd7054; }
	static INLINE color_t salmon4()					{ return 0x8b4c39; }
	static INLINE color_t sandybrown()				{ return 0xf4a460; }
	static INLINE color_t seagreen1()				{ return 0x54ff9f; }
	static INLINE color_t seagreen2()				{ return 0x4eee94; }
	static INLINE color_t seagreen3()				{ return 0x43cd80; }
	static INLINE color_t seagreen4()				{ return 0x2e8b57; }
	static INLINE color_t seashell1()				{ return 0xfff5ee; }
	static INLINE color_t seashell2()				{ return 0xeee5de; }
	static INLINE color_t seashell3()				{ return 0xcdc5bf; }
	static INLINE color_t seashell4()				{ return 0x8b8682; }
	static INLINE color_t sienna()					{ return 0xa0522d; }
	static INLINE color_t sienna1()					{ return 0xff8247; }
	static INLINE color_t sienna2()					{ return 0xee7942; }
	static INLINE color_t sienna3()					{ return 0xcd6839; }
	static INLINE color_t sienna4()					{ return 0x8b4726; }
	static INLINE color_t skyblue()					{ return 0x87ceeb; }
	static INLINE color_t skyblue1()				{ return 0x87ceff; }
	static INLINE color_t skyblue2()				{ return 0x7ec0ee; }
	static INLINE color_t skyblue3()				{ return 0x6ca6cd; }
	static INLINE color_t skyblue4()				{ return 0x4a708b; }
	static INLINE color_t slateblue()				{ return 0x6a5acd; }
	static INLINE color_t slateblue1()				{ return 0x836fff; }
	static INLINE color_t slateblue2()				{ return 0x7a67ee; }
	static INLINE color_t slateblue3()				{ return 0x6959cd; }
	static INLINE color_t slateblue4()				{ return 0x473c8b; }
	static INLINE color_t slategray()				{ return 0x708090; }
	static INLINE color_t slategray1()				{ return 0xc6e2ff; }
	static INLINE color_t slategray2()				{ return 0xb9d3ee; }
	static INLINE color_t slategray3()				{ return 0x9fb6cd; }
	static INLINE color_t slategray4()				{ return 0x6c7b8b; }
	static INLINE color_t snow1()					{ return 0xfffafa; }
	static INLINE color_t snow2()					{ return 0xeee9e9; }
	static INLINE color_t snow3()					{ return 0xcdc9c9; }
	static INLINE color_t snow4()					{ return 0x8b8989; }
	static INLINE color_t springgreen1()			{ return 0x00ff7f; }
	static INLINE color_t springgreen2()			{ return 0x00ee76; }
	static INLINE color_t springgreen3()			{ return 0x00cd66; }
	static INLINE color_t springgreen4()			{ return 0x008b45; }
	static INLINE color_t steelblue()				{ return 0x4682b4; }
	static INLINE color_t steelblue1()				{ return 0x63b8ff; }
	static INLINE color_t steelblue2()				{ return 0x5cacee; }
	static INLINE color_t steelblue3()				{ return 0x4f94cd; }
	static INLINE color_t steelblue4()				{ return 0x36648b; }
	static INLINE color_t tan()						{ return 0xd2b48c; }
	static INLINE color_t tan1()					{ return 0xffa54f; }
	static INLINE color_t tan2()					{ return 0xee9a49; }
	static INLINE color_t tan3()					{ return 0xcd853f; }
	static INLINE color_t tan4()					{ return 0x8b5a2b; }
	static INLINE color_t thistle()					{ return 0xd8bfd8; }
	static INLINE color_t thistle1()				{ return 0xffe1ff; }
	static INLINE color_t thistle2()				{ return 0xeed2ee; }
	static INLINE color_t thistle3()				{ return 0xcdb5cd; }
	static INLINE color_t thistle4()				{ return 0x8b7b8b; }
	static INLINE color_t tomato1()					{ return 0xff6347; }
	static INLINE color_t tomato2()					{ return 0xee5c42; }
	static INLINE color_t tomato3()					{ return 0xcd4f39; }
	static INLINE color_t tomato4()					{ return 0x8b3626; }
	static INLINE color_t turquoise()				{ return 0x40e0d0; }
	static INLINE color_t turquoise1()				{ return 0x00f5ff; }
	static INLINE color_t turquoise2()				{ return 0x00e5ee; }
	static INLINE color_t turquoise3()				{ return 0x00c5cd; }
	static INLINE color_t turquoise4()				{ return 0x00868b; }
	static INLINE color_t violet()					{ return 0xee82ee; }
	static INLINE color_t violetred()				{ return 0xd02090; }
	static INLINE color_t violetred1()				{ return 0xff3e96; }
	static INLINE color_t violetred2()				{ return 0xee3a8c; }
	static INLINE color_t violetred3()				{ return 0xcd3278; }
	static INLINE color_t violetred4()				{ return 0x8b2252; }
	static INLINE color_t wheat()					{ return 0xf5deb3; }
	static INLINE color_t wheat1()					{ return 0xffe7ba; }
	static INLINE color_t wheat2()					{ return 0xeed8ae; }
	static INLINE color_t wheat3()					{ return 0xcdba96; }
	static INLINE color_t wheat4()					{ return 0x8b7e66; }
	static INLINE color_t whitesmoke()				{ return 0xf5f5f5; }
	static INLINE color_t yellow1()					{ return 0xffff00; }
	static INLINE color_t yellow2()					{ return 0xeeee00; }
	static INLINE color_t yellow3()					{ return 0xcdcd00; }
	static INLINE color_t yellow4()					{ return 0x8b8b00; }
	static INLINE color_t yellowgreen()				{ return 0x9acd32; }
};




#endif //__color_h__
