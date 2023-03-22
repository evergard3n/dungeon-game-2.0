#include "Input.h"
#include "Engine.h"

void Input::listen()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: Engine::GetInstance()->Quit();break;
		case SDL_KEYDOWN: keyDown(); break;
		case SDL_KEYUP: keyUp(); break;
		}
	}
}
bool Input::getKeyDown(SDL_Scancode key)
{
	if (m_keyStates[key] == 1) return true;
	return false;


	
}
Input::Input(){
	m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyUp()
{
	m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown()
{
	m_keyStates = SDL_GetKeyboardState(nullptr);
}

Input* Input::s_Instance = nullptr;