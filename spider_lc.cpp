#include "spider.h"
#include "spidergames.h"




#ifdef CORE_TEENSY




// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>




pixelArray strip = pixelArray(256, 17, NEO_GRB + NEO_KHZ800);
spiderGame *game = NULL;

USB Usb;

BTD Btd(&Usb);
WII Wii[2] = {WII(&Btd, PAIR), WII(&Btd, PAIR)};



elapsedMillis render_time;



void setup_arm() {

	//INITIALIZE THE MAIN LED GRID
	strip.begin();
strip.setBrightness(100);  //TODO: THIS BRIGHTNESS IS JUST DURING DEBUGGING
	strip.string("Init...", 0, 0, RGB(32,0,0));
	strip.show();


	//RANDOMIZE SEED A LITTLE BIT
	pinMode(22, INPUT);		//ANALOG 8
	pinMode(23, INPUT);		//ANALOG 9
	randomSeed((uint32_t)uint32_b(analogRead(8), analogRead(9)));


	//RESET USB CONTROLLER
	delay(100);
	pinMode(7, OUTPUT);
	digitalWrite(7, LOW);
	delay(100);
	digitalWrite(7, HIGH);
	delay(100);
	strip.string("Init...", 0, 0, RGB(0,0,32));
	strip.show();


	//CREATE MAIN GAME OBJECT
	game = new spiderBootscreen();


	//INITIALIZE WII REMOTE OBJECTS
//	for (int i=0; i<PLAYERS; i++) {
//		Wii[i].attachOnInit(onInit);
//	}


	//ENABLE SERIAL COMMUNICATION FOR DEBUGGING
	Serial.begin(115200);
	strip.string("Init...", 0, 0, RGB(0,32,0));
	strip.show();


	//INITIALIZE USB
	if (Usb.Init() != -1) {
		strip.string("Init...", 0, 0, RGB(32,32,32));
		strip.show();
		render_time = 0;
		return;
	}


	//PROBLEM DURING HARDWARE INIT
	strip.clear();
	strip.string("OSC", 0,  0, RGB(100,0,0));
	strip.string("USB", 0,  5, RGB(0,0,100));
	strip.string("Err", 0, 10, RGB(100,0,0));
	strip.show();
	while (1);
}




//MAIN LOOP
void loop_arm() {

	//KEEP GENERATING RANDOM NUMBERS
	random(255);


	//HANDLE GAME AND LED RENDERING LOOP
	if (render_time >= 20) {
		render_time -= 20;
		Usb.Task();
		if (game) game->loop(&strip, Wii);
		strip.show();


		//CHANGE GAME OBJECT BACK TO MAIN MENU
		for (int i=0; i<PLAYERS; i++) {
			if (Wii[i].wiimoteConnected) {
				if (Wii[i].getButtonClick(HOME)) {
					Serial.print("\r\nHOME");
					delete game;
					strip.clear();
					strip.show();
					game = new spiderBootscreen(true);
				}
			}
		}
	}
}


/*
void onInit() {
	Serial.print("\r\nWII REMOTE INIT");
	static bool oldControllerState[PLAYERS];

	for (int i=0; i<PLAYERS; i++) {
		if (Wii[i].wiimoteConnected && !oldControllerState[i]) {
			oldControllerState[i] = true; // Used to check which is the new controller
			Wii[i].setLedOn((LEDEnum)(i + 1)); // Cast directly to LEDEnum - see: "controllerEnums.h"
		}
	}
}
*/



#endif //CORE_TEENSY
