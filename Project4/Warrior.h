#pragma once
#include "Character.h"
#include "Animation.h"
#include <SDL.h>
#include "RigidBody.h"
#include "Input.h"
class Warrior: public Character
{
public:
	Warrior(Properties* prop);
	virtual void Draw() ;
	virtual void Clean() ;
	virtual void Update(float dt) ;
private:
	//int m_Row, m_Frame, m_FrameCount;
	//int m_AnimSpeed;
	Animation* m_Animation;
	RigidBody* m_rigidBody;
};

