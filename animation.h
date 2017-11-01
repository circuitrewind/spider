#ifndef __ANIMATION_H__
#define __ANIMATION_H__



class animation {
public:

	animation();


	virtual ~animation() {
		for (int i=0; i<10; i++) {
			if (list[i] == this) {
				list[i] = NULL;
			}
		}
	}


	INLINE void reset() { elapsed = 0; }



protected:
	virtual void loop( pixelArray **strip, WII **wii) {}
	virtual void frame(pixelArray **strip, WII **wii) {}




public:
	INLINE static void loop_all(pixelArray **strip, WII **wii) {
		for (int i=0; i<10; i++) {
			if (list[i]) list[i]->loop(strip, wii);
		}
	}


	INLINE static void frame_all(pixelArray **strip, WII **wii) {
		for (int i=0; i<10; i++) {
			if (list[i]) list[i]->frame(strip, wii);
		}
	}



	INLINE static void delete_all() {
		for (int i=0; i<10; i++) {
			delete list[i];
		}
	}



protected:
	elapsedMillis elapsed;



private:
	static animation *list[10];
};




#endif //__ANIMATION_H__
