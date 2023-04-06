#pragma once
#include <SDL.h>
using box = SDL_Rect;
class impact {
public:
	inline box get() { return m_box; }
	inline void sethitBox(int x, int y, int w, int h) {
		m_hitBox = { x,y,w,h };
	}
	void set(int x, int y, int w, int h) {
		m_box = {
			x = m_hitBox.x,
			y = m_hitBox.y,
			w = m_hitBox.w,
			h = m_hitBox.h

		};
	}
private:
	box m_box;
	box m_hitBox;
};