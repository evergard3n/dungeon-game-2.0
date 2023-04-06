#include "Timer.h"
#include <SDL.h>
Timer* Timer::s_Instance = nullptr;
void Timer::tick() {
	m_deltaTime = (SDL_GetTicks() - m_lastTimer) * (TARGET_FPS / 1000.0f);
	if (m_deltaTime > TARGET_DELTATIME) m_deltaTime = TARGET_DELTATIME;
	m_lastTimer = SDL_GetTicks();
}