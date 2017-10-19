#ifndef __MENU_H__
#define __MENU_H__



#include "defines.h"



class menu : public spidergame {
public:
	menu() : selected(0) {}
	virtual void loop(pixelArray **strip, WII **wii);

private:
	int8_t selected;
};



#endif //__MENU_H__
