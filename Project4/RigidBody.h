#pragma once
#include "Vector2D.h"

#define UNI_MAS 1.0f
#define GRAVITY 9.8

class RigidBody
{
public:
	RigidBody(){
		m_Mass = UNI_MAS;
		m_Gravity = GRAVITY;
	}
	inline void setMass(float mass) { m_Mass = mass; }
	inline void setGravity(float gravity) { m_Gravity = gravity; }

	void applyForce(Vector2D F) { m_Force = F; }
	inline void applyForceY(float Fy) { m_Force.Y = Fy; }
	inline void applyForceX(float Fx) { m_Force.X = Fx; }
	inline void unsetForce() { m_Force = Vector2D(0, 0); }

	inline void applyFriction(Vector2D Fr) { m_friction = Fr; }
	inline void unsetFriction() { m_friction = Vector2D(0, 0); }

	inline float getMass() { return m_Mass; }
	inline Vector2D position() { return m_position; }
	inline Vector2D velocity() { return m_velocity; }
	inline Vector2D accleration() { return m_accleration; }
	
	void Update(float dt) {
		m_accleration.X = (m_Force.X + m_friction.X) / m_Mass;
		m_accleration.Y = m_Gravity + m_Force.Y / m_Mass;
		m_velocity = m_accleration * dt;
		m_position = m_velocity * dt;
	}
private:
	float m_Mass;
	float m_Gravity;
	Vector2D m_Force;
	Vector2D m_friction;
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_accleration;
};