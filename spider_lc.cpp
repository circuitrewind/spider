#include "spider.h"
#include "bootloader.h"
#include "menu.h"



#ifdef CORE_TEENSY




// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>




pixelArray *strip[2];


spidergame *game = NULL;

USB Usb;

BTD Btd(&Usb);
WII *Wii[PLAYERS];



elapsedMillis render_time;



void setup_arm() {

	//INITIALIZE THE MAIN LED GRID
	strip[0] = new pixelArray(300, 17, NEO_GRB + NEO_KHZ800);
	strip[0]->begin();
	strip[0]->clear();
	strip[0]->string("Init...", 0, 0, color_t::red().right(5));
	strip[0]->show();


	//INITIALIZE THE SECONDARY LED GRID
	strip[1] = new pixelArray(300,  9, NEO_GRB + NEO_KHZ800);
	strip[1]->begin();
	strip[1]->clear();
	strip[1]->show();


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
	strip[0]->string("Init...", 0, 0, color_t::blue().right(5));
	strip[0]->show();


	//CONFIGURE BLUETOOTH SYNC BUTTON
	pinMode(24, INPUT_PULLUP);


	//ENABLE SERIAL COMMUNICATION FOR DEBUGGING
	Serial.begin(115200);
	strip[0]->string("Init...", 0, 0, color_t::lime().right(5));
	strip[0]->show();


	//CREATE WII REMOTE BLUETOOTH SERVICES
	for (int i=0; i<PLAYERS; i++) {
		Wii[i] = new WII(&Btd);
	}


	//INITIALIZE USB
	if (Usb.Init() != -1) {
		strip[0]->string("Init...", 0, 0, color_t::white().right(5));
		strip[0]->show();

		//CREATE MAIN GAME OBJECT
		game = new bootloader();
		render_time  = 0;

		return;
	}


	//PROBLEM DURING HARDWARE INIT
	strip[0]->clear();
	strip[0]->string("OSC", 0,  0, color_t(100,0,0));
	strip[0]->string("USB", 0,  5, color_t(0,0,100));
	strip[0]->string("Err", 0, 10, color_t(100,0,0));
	strip[0]->show();
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
		if (game) game->loop(strip, Wii);
		strip[0]->show();
		strip[1]->show();
	}


	//CHANGE GAME OBJECT BACK TO MAIN MENU
	for (int i=0; i<PLAYERS; i++) {
		if (Wii[i]->wiimoteConnected) {
			if (Wii[i]->getButtonClick(HOME)) {
				Serial.print("\r\nHOME");
				delete game;
				strip[0]->clear();
				strip[1]->clear();
				strip[0]->show();
				strip[1]->show();
				game = new menu();
			}
		}
	}
}




#endif //CORE_TEENSY
