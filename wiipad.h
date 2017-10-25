#ifndef __WII_PAD_H__
#define __WII_PAD_H__




enum WII_BUTTONS {
	UP		=  4,
	DOWN	=  6,
	LEFT	=  5,
	RIGHT	= 19,
	PLUS	=  3,
	MINUS	= 17,
	ONE		= 16,
	TWO		=  7,
	A		=  8,
	B		= 15,
	HOME	= 18,
};




class WII {
public:
	WII(uint8_t player_id) {
		buttons				= 0;
		previous			= 0;
		player				= player_id;
		wiimoteConnected	= (player == 1);
	}


	INLINE void loop() {
		previous	= buttons;
		buttons		= 0;
		clicked		= previous | buttons;
	}


	bool getButtonClick(uint8_t button) {
		return false;
	}



	INLINE void setLedOn(uint8_t) {}
	INLINE void setRumbleToggle() {}


public:
	uint8_t		player;
	bool		wiimoteConnected;

	uint32_t	buttons;
	uint32_t	previous;
	uint32_t	clicked;
};




#endif // __WII_PAD_H__
