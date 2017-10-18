#include "spider.h"
#include "bootloader.h"
#include "menu.h"



#ifdef CORE_TEENSY




// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>




pixelArray strip = pixelArray(256, 17, NEO_GRB + NEO_KHZ800);
spidergame *game = NULL;

USB Usb;

BTD Btd(&Usb);
WII *Wii[PLAYERS];



elapsedMillis render_time;



void setup_arm() {

	//INITIALIZE THE MAIN LED GRID
	strip.begin();
	strip.clear();
	strip.string("Init...", 0, 0, color_t::red().right(5));
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
	strip.string("Init...", 0, 0, color_t::blue().right(5));
	strip.show();


	//CONFIGURE BLUETOOTH SYNC BUTTON
	pinMode(24, INPUT_PULLUP);


	//ENABLE SERIAL COMMUNICATION FOR DEBUGGING
	Serial.begin(115200);
	strip.string("Init...", 0, 0, color_t::lime().right(5));
	strip.show();


	//CREATE WII REMOTE BLUETOOTH SERVICES
	for (int i=0; i<PLAYERS; i++) {
		Wii[i] = new WII(&Btd);
	}


	//INITIALIZE USB
	if (Usb.Init() != -1) {
		strip.string("Init...", 0, 0, color_t::white().right(5));
		strip.show();

		//CREATE MAIN GAME OBJECT
		game = new bootloader();
		render_time  = 0;

		return;
	}


	//PROBLEM DURING HARDWARE INIT
	strip.clear();
	strip.string("OSC", 0,  0, color_t(100,0,0));
	strip.string("USB", 0,  5, color_t(0,0,100));
	strip.string("Err", 0, 10, color_t(100,0,0));
	strip.show();
	while (1);
}




//MAIN LOOP
void loop_arm() {

	//POLL USB, BLUETOOTH, WII REMOTE
	Usb.Task();


	//KEEP GENERATING RANDOM NUMBERS
	random(255);


	//ENABLE BLUETOOTH PAIRING
	if (digitalRead(24) == LOW) {
		Btd.pairWithWiiRemote();
	}


	//HANDLE GAME AND LED RENDERING LOOP
	if (render_time >= 20) {
		render_time -= 20;
		if (game) game->loop(&strip, Wii);
		strip.show();
	}


	//CHANGE GAME OBJECT BACK TO MAIN MENU
	for (int i=0; i<PLAYERS; i++) {
		if (Wii[i]->wiimoteConnected) {
			if (Wii[i]->getButtonClick(HOME)) {
				Serial.print("\r\nHOME");
				delete game;
				strip.clear();
				strip.show();
				game = new menu();
			}
		}
	}
}




#endif //CORE_TEENSY
