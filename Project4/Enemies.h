#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "RigidBody.h"
#include "Collider.h"
#include "SpriteAnimation.h"
#include "Play.h"
#include "ObjectFactory.h"
#define DEFAULT_ENE_HP = 50
class Enemy : public GameObject {

public:
    Enemy(Transform* tf);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);
    virtual bool IsDead();
    virtual void AnimationState();
    virtual int GetId() const { return m_Id; }
   
    
private:
    bool m_IsIdle;
    bool m_IsAttacking;
    bool m_IsWalking;
    bool m_IsDead;
    bool m_IsHurt;
    float m_HealthPoint;
    int m_Id;
    static int S_n;
    float m_Damage;
    Collider* m_Collider;
    RigidBody* m_EneRigidbody;
    
    SpriteAnimation* m_Animation;
    Vector2D m_EneLastSafePos;
    friend class Play;
};

#endif // ENEMY_H

