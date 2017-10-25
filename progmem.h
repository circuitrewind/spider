#ifndef __PROGMEM_H_
#define __PROGMEM_H_




// SOURCE:
// https://arduino.stackexchange.com/questions/13545/using-progmem-to-store-array-of-structs

template <typename T> void PROGMEM_readAnything(const T * sce, T& dest) {
	memcpy_P (&dest, sce, sizeof(T));
}

template <typename T> T PROGMEM_getAnything(const T * sce) {
	static T temp;
	memcpy_P (&temp, sce, sizeof(T));
	return temp;
}




#endif //__PROGMEM_H_
