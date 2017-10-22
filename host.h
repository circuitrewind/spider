#ifndef __HOST_H__
#define __HOST_H__



#include "defines.h"



class host : public spidergame {
public:
	host() { reset(); }

protected:
	virtual void frame(pixelArray **strip, WII **wii);

	void reset();
	void process(pixelArray *strip);

private:
	uint16_t	offset;
	uint8_t		buffer[100];
};




#endif //__HOST_H__
