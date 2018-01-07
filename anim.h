#ifndef __ANIM_H__
#define __ANIM_H__



#include "defines.h"


struct PACKED pixel_command {
	uint8_t x;
	uint8_t y;
	uint16_t delay;
};

static const pixel_command command_list[] = {
	{   5,   5,   0 },
	{   4,   4,  50 }, {  6,  4, 0 },
	{   3,   5,  50 }, {  7,  5, 0 },
	{   3,   6,  50 }, {  7,  6, 0 },
	{   4,   7,  50 }, {  6,  7, 0 },
	{   5,   8,  50 },

	{   5,  16,  50 },
	{   4,  15,  50 }, {  6, 15, 0 },
	{   3,  14,  50 }, {  7, 14, 0 },
	{   2,  15,  50 }, {  8, 15, 0 },
	{   1,  16,  50 }, {  9, 16, 0 },
	{   1,  17,  50 }, {  9, 17, 0 },
	{   1,  18,  50 }, {  9, 18, 0 },
	{   2,  19,  50 }, {  8, 19, 0 },
	{   3,  20,  50 }, {  7, 20, 0 },
	{   4,  21,  50 }, {  6, 21, 0 },
	{   5,  22,  50 },

	{ 254, 254, 500 },
	{ 255, 255,  30 },
	{0,0,0}, //NULL COMMAND
};


/*
static const pixel_command command_list[] = {
	{   7,   4,   0 },
	{   6,   3,  50 }, {  8,  3, 0 },
	{   5,   2,  50 }, {  9,  2, 0 },
	{   4,   2,  50 }, { 10,  2, 0 },
	{   3,   3,  50 }, { 11,  3, 0 },
	{   2,   4,  50 }, { 12,  4, 0 },
	{   2,   5,  50 }, { 12,  5, 0 },
	{   2,   6,  50 }, { 12,  6, 0 },
	{   2,   7,  50 }, { 12,  7, 0 },
	{   3,   8,  50 }, { 11,  8, 0 },
	{   4,   9,  50 }, { 10,  9, 0 },
	{   5,  10,  50 }, {  9, 10, 0 },
	{   6,  11,  50 }, {  8, 11, 0 },
	{   7,  12,  50 },
	{ 254, 254, 500 },
	{ 255, 255,  30 },
	{0,0,0}, //NULL COMMAND
};
*/


class anim : public animation {
public:
	anim() {
		display[0]	= NULL;
		display[1]	= NULL;
		reset();
	}


	void reset(int new_mode=0, int new_cycle=0) {
		delete display[0];
		delete display[1];
		mode		= new_mode;
		cycle		= new_cycle;
		display[0]	= NULL;
		display[1]	= NULL;
		animation::reset();
	}


	virtual void frame(pixelArray **strip, WII **wii);

private:
	int	mode;
	int	cycle;
	int	submode;
	animation *display[2];
};


#endif //__ANIM_H__
