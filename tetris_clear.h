#ifndef __TETRIS_CLEAR_H__
#define __TETRIS_CLEAR_H__




class tetris_clear : public animation {
public:
	tetris_clear(tetris_player *parent_anim, uint32_t rows_anim) {
		parent	= parent_anim;
		rows	= rows_anim;
		parent->pause(true);
		paused	= parent->elapsed;
	}


	virtual ~tetris_clear() {
		parent->pause(false);
		parent->elapsed = paused;
	}


	INLINE uint8_t id() const { return parent->id(); }


	virtual void frame(pixelArray **strip, WII **wii) {
		if (elapsed > 1000) {
			elapsed	-= 1000;
			paused	-= elapsed;
			for (uint32_t i=0; i<TETRIS_HEIGHT; i++) {
				if ((1L<<i) & rows) {
					parent->clear(i);
				}
			}
			delete this;
			return;
		}

		for (uint32_t y=0; y<TETRIS_HEIGHT; y++) {
			if (!(rows & 1L<<y)) continue;
			for (int x=0; x<TETRIS_WIDTH; x++) {
				strip[id()]->draw(
					x + parent->align_x(),
					y + parent->align_y()
				);
			}
		}
	}


private:
	tetris_player	*parent;
	int32_t			paused;
	uint32_t		rows;
};




#endif //__TETRIS_CLEAR_H__
