#include "defines.h"
#include "animation.h"



animation *animation::list[10] = {
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL,
};



animation::animation() {
	reset();

	for (int i=0; i<10; i++) {
		if (list[i] == NULL) {
			list[i] = this;
			return;
		}
	}

	#ifndef __AVR__
	//THINGS BREAK IF WE HAVE TOO MANY ANIMATIONS... SO DON'T
	Serial.println(F("ANIMATION RESOURCE EXHALATION"));
	#endif
	while (1);
}
