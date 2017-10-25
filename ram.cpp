#include "defines.h"


int freeRam () {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}


void print_ram() {
	Serial.print(F("Free RAM: "));
	Serial.println(freeRam());
}
