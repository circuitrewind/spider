#ifndef __ANIMATION_H__
#define __ANIMATION_H__



class animation {
public:

	animation() {
		for (int i=0; i<10; i++) {
			if (list[i] == NULL) {
				list[i] = this;
				return;
			}
		}

		//THINGS BREAK IF WE HAVE TOO MANY ANIMATIONS... SO DON'T
		while (1);
	}



	virtual ~animation() {
		for (int i=0; i<10; i++) {
			if (list[i] == this) {
				list[i] = NULL;
			}
		}
	}



protected:
	virtual void loop(pixelArray **strip)=0;



public:
	INLINE static void loop_all(pixelArray **strip) {
		for (int i=0; i<10; i++) {
			if (list[i]) list[i]->loop(strip);
		}
	}



	INLINE static void delete_all() {
		for (int i=0; i<10; i++) {
			delete list[i];
		}
	}



protected:
	elapsedMillis time;



private:
	static animation *list[10];
};




#endif //__ANIMATION_H__
