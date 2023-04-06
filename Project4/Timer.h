#pragma once
const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 0.8f;
class Timer
{
public:
	void tick();
	inline float getDeltaTime() { return m_deltaTime; }
	inline static Timer* getInstance() { return s_Instance = ( s_Instance != nullptr) ? s_Instance : new Timer(); } 
private:
	Timer(){}
	static Timer* s_Instance;
	float m_deltaTime;
	float m_lastTimer = 0.0f;
};

