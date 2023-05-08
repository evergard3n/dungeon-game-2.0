#include "Enemies.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include <iostream>
#include "Camera.h"
#include "Play.h"
static Registrar<Enemy> enemy("Enemy");
int Enemy::S_n = 0;


Enemy::Enemy(Transform* tf) :GameObject(tf) {
    m_Tf->ScrollRatio = 1;
    m_EneRigidbody = new RigidBody();
    m_EneRigidbody->SetGravity(9.8);
    m_Collider = new Collider();

    m_HealthPoint = 100;
    m_Damage = 0.06;

    m_Animation = new SpriteAnimation(true);
    m_Animation->SetProps(0, 4, 100);
    m_Id = S_n;
    S_n++;
    
}

void Enemy::Draw() {
    //m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, m_Flip, 0.3f, 0.3f);
    
    //TextureMgr::Instance()->DrawFrame(m_Tf, 0, 6);
    Vector2D cam = Camera::Instance()->GetPosition();
    m_Animation->Draw(m_Tf);
    std::cout << "does this work?" << std::endl;
    SDL_Rect health_bar = { m_Tf->X, m_Tf->Y, 20, 3 };
    health_bar.x -= cam.X;
    health_bar.y -= cam.Y;
    health_bar.w *= m_HealthPoint / 100;
    SDL_SetRenderDrawColor(Engine::Instance()->GetRenderer(), 255, 0, 0, 100);
    if (m_HealthPoint > 0) SDL_RenderFillRect(Engine::Instance()->GetRenderer(), &health_bar);
}

void Enemy::Update(float dt) {

    // X-Axis movements
    m_EneRigidbody->Update(dt);
    m_EneLastSafePos.X = m_Tf->X;
    m_Tf->X += m_EneRigidbody->Position().X;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 40, 40);

    if (CollisionHandler::Instance()->MapCollision(m_Collider->Get()))
        m_Tf->X = m_EneLastSafePos.X;

    // Y-Axis movements
    m_EneRigidbody->Update(dt);
    m_EneLastSafePos.Y = m_Tf->Y;
    m_Tf->Y += m_EneRigidbody->Position().Y;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 40, 40);

    if (CollisionHandler::Instance()->MapCollision(m_Collider->Get()))
        m_Tf->Y = m_EneLastSafePos.Y;
    //AnimationState();
    m_Animation->Update(dt);
    
}

bool Enemy::IsDead()
{
    if (m_HealthPoint <= 0) {
        m_IsDead = true;
    }
    else m_IsDead = false;
    return m_IsDead;
}


void Enemy::AnimationState()
{
    
    m_Tf->TextureID = "enemies_idle";
    m_Animation->SetProps(0, 4, 100);
    
    if (m_IsAttacking) {
        m_Tf->TextureID = "enemies_attacking";
        m_Animation->SetProps(0, 6, 100);
    }
    if (m_IsHurt) {
        m_Tf->TextureID = "enemies_hurt";
        m_Animation->SetProps(0, 2, 100);
    }
    if (m_IsWalking) {
        m_Tf->TextureID = "enemies_walking";
        m_Animation->SetProps(0, 6, 100);
    }
}


void Enemy::Clean() {

}



