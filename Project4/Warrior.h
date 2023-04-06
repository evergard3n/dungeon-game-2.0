#pragma once
#include "Character.h"
#include "Animation.h"
#include <SDL.h>
#include "RigidBody.h"
#include "Vector2D.h"
#include "impact.h"


#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f
#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Warrior: public Character
{
public:
	Warrior(Properties* prop);
	virtual void Draw() ;
	virtual void Clean() ;
	virtual void Update(float dt) ;
private:
	void state();
private:
	bool m_isJumping;
	bool m_isGrounded;
	bool m_isRunning;
	bool m_isAttacking;
	bool m_isClimbing;

	float m_jumptime;
	float m_jumpforce;
	float m_attackTime;

	impact* m_impact;
	Animation* m_Animation;
	RigidBody* m_rigidBody;
	Vector2D m_lastSafePos;
};

