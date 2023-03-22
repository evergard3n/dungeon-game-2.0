#pragma once
#include <SDL.h>
class Input
{
public:
	static Input* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
	}
	void listen();
	bool getKeyDown(SDL_Scancode key);
private:
	Input();
	void keyUp();
	void keyDown();

	const Uint8* m_keyStates;
	
	static Input* s_Instance;
};

