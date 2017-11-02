#ifdef TEENSYDUINO



#include "spider.h"
#include "bootloader.h"
#include "menu.h"
#include "grid.h"
#include "pixel_dual.h"
#include "tetris.h"




// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
//#include <spi4teensy3.h>
#endif
//#include <SPI.h>




pixelArray	*strip[2];
pixelDual	*dual;
color_t		grid_data[GRID_TOTAL * 2];



USB Usb;

BTD Btd(&Usb);
WII *wii[PLAYERS];



coms LED_LEFT( 11, 12, 14, 4);
coms LED_RIGHT(11, 12, 14, 3);


elapsedMillis render_time;



void setup_arm() {
	//ENABLE SERIAL COMMUNICATION FOR DEBUGGING
	Serial.begin(115200);


	//INITIALIZE THE MAIN LED GRID
	Serial.println("Grid 0");
	strip[0] = new pixelArray(17, GRID_WIDTH, GRID_HEIGHT, GRID, &grid_data[0]);
	strip[0]->begin();
	strip[0]->clear();
	strip[0]->string("\x7F", 0, GRID_HEIGHT-5, color_t::red().right(5));
	strip[0]->show();


	//INITIALIZE THE SECONDARY LED GRID
	Serial.println("Grid 1");
	strip[1] = new pixelArray( 9, GRID_WIDTH, GRID_HEIGHT, GRID, &grid_data[GRID_TOTAL]);
	strip[1]->begin();
	strip[1]->clear();
	strip[1]->string("\x7F", 0, GRID_HEIGHT-5, color_t::red().right(5));
	strip[1]->show();


	//INITIALIZE THE SECONDARY LED GRID
	Serial.println("Dual Grids");
	dual = new pixelDual(GRID_WIDTH*2, GRID_HEIGHT, strip[0], strip[1]);


	//RANDOMIZE SEED A LITTLE BIT
	Serial.println("Randomizer");
	pinMode(22, INPUT);		//ANALOG 8
	pinMode(23, INPUT);		//ANALOG 9
	randomSeed((uint32_t)uint32_b(analogRead(8), analogRead(9)));


	//RESET USB CONTROLLER
	Serial.println("USB");
	delay(100);
	pinMode(7, OUTPUT);
	digitalWrite(7, LOW);
	delay(100);
	digitalWrite(7, HIGH);
	delay(100);
	strip[0]->string("\x7F\x7F", 0, GRID_HEIGHT-5, color_t::red().right(5));
	strip[0]->show();


	//CONFIGURE BLUETOOTH SYNC BUTTON
	Serial.println("Button");
	pinMode(24, INPUT_PULLUP);


	//CREATE WII REMOTE BLUETOOTH SERVICES
	Serial.println("Players");
	for (int i=0; i<PLAYERS; i++) {
		wii[i] = new WII(&Btd);
	}


	//INITIALIZE USB
	if (Usb.Init() != -1) {
		strip[1]->string("\x7F\x7F", 0, GRID_HEIGHT-5, color_t::red().right(5));
		strip[1]->show();

		//CREATE MAIN GAME OBJECT
		Serial.println("LOADED");
		new bootloader();
//		new tetris();
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


	//HANDLE ATTINY85 SPI TRANSFERS
	if (!LED_RIGHT.enabled()) LED_LEFT.loop();
	if (!LED_LEFT.enabled()) LED_RIGHT.loop();


	//HANDLE GAME LOOP
	animation::loop_all(strip, wii);


	//FRAME AND LED RENDERING LOOP
	if (render_time >= 20) {
		render_time -= 20;

		pixelArray::increment();
		animation::frame_all(strip, wii);

		strip[0]->show();
		strip[1]->show();

		//CLEAR BUTTON STATES
		for (int i=0; i<PLAYERS; i++) {
			wii[i]->clear();
		}
	}


	//CHANGE GAME OBJECT BACK TO MAIN MENU
	for (int i=0; i<PLAYERS; i++) {
		if (!wii[i]->wiimoteConnected) continue;
		if (!wii[i]->getButtonClick(HOME)) continue;

		Serial.print("\r\nHOME");
		animation::delete_all();
		strip[0]->clear();
		strip[1]->clear();
		strip[0]->show();
		strip[1]->show();

		for (int x=0; x<PLAYERS; x++) {
			wii[x]->clear();
		}

		new menu();
		return;
	}
}




#endif //TEENSYDUINO
