#ifdef ARDUINO_AVR_NANO



#include "spider.h"
#include "bootloader.h"
#include "menu.h"
#include "grid.h"
#include "pixel_dual.h"

#include "anim.h"




pixelArray	*strip[2];
pixelDual	*dual;
color_t		grid_data[GRID_TOTAL];



WII *wii[PLAYERS];


coms LED_LEFT( 11, 12, 13, 10);
coms LED_RIGHT(11, 12, 13, 10);


elapsedMillis render_time;


void setup_nano() {
	//ENABLE SERIAL COMMUNICATION FOR DEBUGGING
	Serial.begin(115200);
	print_ram();


	//INITIALIZE THE MAIN LED GRID
	Serial.println(F("Grid 0"));
	strip[0] = new pixelArray(2, GRID_WIDTH, GRID_HEIGHT, GRID, &grid_data[0]);
	strip[0]->clear();
	strip[0]->string("\x7F", 0, GRID_HEIGHT-5, color_t::red().right(5));
	strip[0]->show();


	//INITIALIZE THE SECONDARY LED GRID
	Serial.println(F("Grid 1"));
	strip[1] = new pixelArray(14, GRID_WIDTH, GRID_HEIGHT, GRID, &grid_data[0]);
	strip[1]->clear();
	strip[1]->string("\x7F", 0, GRID_HEIGHT-5, color_t::red().right(5));
	strip[1]->show();


	//INITIALIZE THE SECONDARY LED GRID
	Serial.println(F("Dual Grids"));
	dual = new pixelDual(GRID_WIDTH*2, GRID_HEIGHT, strip[0], strip[1]);


	//RANDOMIZE SEED A LITTLE BIT
	Serial.println(F("Randomizer"));
	randomSeed((uint32_t)uint32_b(analogRead(6), analogRead(7)));


	//CREATE WII REMOTE BLUETOOTH SERVICES
	Serial.println(F("Players"));
	for (int i=0; i<PLAYERS; i++) {
		wii[i] = new WII(i);
	}


	//CREATE MAIN GAME OBJECT
	Serial.println(F("LOADED"));
//	new bootloader();
	new anim();
	render_time  = 0;


	print_ram();
}




//MAIN LOOP
void loop_nano() {

	//KEEP GENERATING RANDOM NUMBERS
	random(255);


	//HANDLE ATTINY85 SPI TRANSFERS
	if (!LED_RIGHT.enabled()) LED_LEFT.loop();
	if (!LED_LEFT.enabled()) LED_RIGHT.loop();


	//HANDLE GAME LOOP
	wii[0]->loop();
	animation::loop_all(strip, wii);


	//FRAME AND LED RENDERING LOOP
	if (render_time >= 20) {
		render_time -= 20;

		pixelArray::increment();
		animation::frame_all(strip, wii);

		strip[0]->show();
//		strip[1]->show();

		//CLEAR OUT THE BUTTON STATE
		wii[0]->clear();
	}


	//CHANGE GAME OBJECT BACK TO MAIN MENU
	for (int i=0; i<PLAYERS; i++) {
		if (!wii[i]->wiimoteConnected) continue;
		if (!wii[i]->getButtonClick(WII_BUTTONS::HOME)) continue;

		Serial.println(F("HOME"));
		animation::delete_all();
		strip[0]->clear();
//		strip[1]->clear();
		strip[0]->show();
//		strip[1]->show();

		for (int x=0; x<PLAYERS; x++) {
			wii[x]->clear();
		}

		new menu();
		return;
	}
}




#endif //ARDUINO_AVR_NANO
