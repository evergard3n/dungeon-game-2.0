#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_TIME 10.0f
#define JUMP_FORCE 15.0f
#define DEFAULT_HP 100
#define SUP_TIME 15.0f

class Warrior : public Character {

public:
    Warrior(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);
    inline int life_lefts();
    virtual float GetHP() { return m_HealthPoint; }
  
private:
    bool m_IsJumping;
    bool m_IsGrounded;
    bool m_IsAttacking;

    float m_HealthPoint = DEFAULT_HP;
    int m_lives = 3;
    float m_JumpTime;
    float m_JumpForce;

    Collider* m_Collider;

    Animation* m_Animation;
    RigidBody* m_RigidBody;
    bool m_Won;
    Vector2D m_LastSafePosition;
    friend class Enemies;
    friend class Engine;
};

#endif // WARRIOR_H
