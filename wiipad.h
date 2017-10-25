#ifndef __WII_PAD_H__
#define __WII_PAD_H__



enum WII_BUTTONS {
	PLUS	=  3,
	RIGHT	=  4,
	UP		=  5,
	LEFT	=  6,
	TWO		=  7,
	A		=  8,
	B		= 15,
	ONE		= 16,
	MINUS	= 17,
	HOME	= 18,
	DOWN	= 19,
};




class WII {
public:
	WII(uint8_t player_id) {
		buttons				= 0;
		previous			= 0;
		clicked				= 0;
		player				= player_id;
		wiimoteConnected	= (player == 0);

		for (int i=3; i<=8; i++) {
			pinMode(i, INPUT_PULLUP);
		}

		for (int i=15; i<=19; i++) {
			pinMode(i, INPUT_PULLUP);
		}
	}


	void loop() {
		buttons = 0;

		for (int i=3; i<=8; i++) {
			uint32_t press = (digitalRead(i) == LOW);
			buttons |= press << i;
		}

		for (int i=15; i<=19; i++) {
			uint32_t press = (digitalRead(i) == LOW);
			buttons |= press << i;
		}

		if (buttons != previous) {
			clicked		|= (buttons & ~previous);
			previous	 =  buttons;
		}
	}


	void clear() {
		clicked = 0;
	}


	INLINE bool getButtonPress(uint32_t button) {
		return (buttons & (((uint32_t)1) << button));
	}


	INLINE bool getButtonClick(uint32_t button) {
		return (clicked & (((uint32_t)1) << button));
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
