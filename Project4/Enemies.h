#pragma once
#include "Warrior.h"
#include "TextureManager.h"
#include "TileLayer.h"
#define DEFAULT_ENE_HP 50
class Enemies : public Character
{
public:
	Enemies(Properties* props);
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	virtual int randomEneType();
	virtual Vector2D RandomSpawnPos();
	virtual bool IsDead() { return m_IsDead; }
private:
	bool m_IsGrounded;
	bool m_IsIdle;
	bool m_IsAttacking;
	bool m_IsWalking;
	bool m_IsDead;
	float m_HealthPoint;
	int m_EneType;
	float m_Damage;
	Collider* m_EneCollider;
	Animation* m_EneAnimation;
	RigidBody* m_EneRigidbody;
	Vector2D m_EneLastSafePos;
};

