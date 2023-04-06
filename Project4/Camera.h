#pragma once
#include <SDL.h>
#include "Point.h"
#include "Vector2D.h"
#include "Engine.h"
class Camera
{
public:
	void update(float dt);
	inline static Camera* getInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
	}
	inline SDL_Rect getcharbox() { return m_charbox; }
	inline Vector2D getpos() { return m_pos; }
	inline void setTarget(Point* target) {
		m_target = target;
	}
private:
	Camera() { m_charbox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; }
	SDL_Rect m_charbox;
	Point* m_target;
	Vector2D m_pos;
	static Camera* s_Instance;
};

