#include "Warrior.h"
#include "Input.h"
#include "CollisionHandler.h"




Warrior::Warrior(Transform* tf) : GameObject(tf) {
    m_Tf->ScrollRatio = 1;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;
    m_HPcap = 100;
    m_HealthPoint = m_HPcap;
    m_Collider = new Collider();
    m_Collider->SetBuffer(-60, -24, -10, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(5.0f);

    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(1, 4, 100);
}

void Warrior::Draw() {
    //m_Collider->Draw();
    Vector2D cam = Camera::Instance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::Instance()->GetRenderer(), &box);
    if (m_HPcap <= 100) {
        SDL_Rect health_bar = { m_Tf->X + 60, m_Tf->Y, 40, 3 };
        health_bar.x -= cam.X;
        health_bar.y -= cam.Y;
        health_bar.w *= m_HealthPoint / 100;
        SDL_Rect health_bar_bg = { m_Tf->X + 60, m_Tf->Y, 40, 3 };
        health_bar_bg.x -= cam.X;
        health_bar_bg.y -= cam.Y;
        SDL_SetRenderDrawColor(Engine::Instance()->GetRenderer(), 0, 0, 0, 100);
        SDL_RenderFillRect(Engine::Instance()->GetRenderer(), &health_bar_bg);

        SDL_SetRenderDrawColor(Engine::Instance()->GetRenderer(), 0, 255, 0, 100);
        SDL_RenderFillRect(Engine::Instance()->GetRenderer(), &health_bar);
    }
    else {
        SDL_Rect health_bar = { m_Tf->X + 60, m_Tf->Y - 5, 40, 3 };
        health_bar.x -= cam.X;
        health_bar.y -= cam.Y;
        
        SDL_Rect health_bar_secondary = { m_Tf->X + 60, m_Tf->Y, 40, 3 };
        health_bar_secondary.x -= cam.X;
        health_bar_secondary.y -= cam.Y;
        health_bar_secondary.w *= (m_HealthPoint-100) / 100;
        SDL_Rect health_bar_bg = { m_Tf->X + 60, m_Tf->Y, 40, 3 };
        health_bar_bg.x -= cam.X;
        health_bar_bg.y -= cam.Y;
        SDL_SetRenderDrawColor(Engine::Instance()->GetRenderer(), 0, 0, 0, 100);
        SDL_RenderFillRect(Engine::Instance()->GetRenderer(), &health_bar_bg);
        
        SDL_SetRenderDrawColor(Engine::Instance()->GetRenderer(), 0, 255, 0, 100);
        SDL_RenderFillRect(Engine::Instance()->GetRenderer(), &health_bar);
        SDL_RenderFillRect(Engine::Instance()->GetRenderer(), &health_bar_secondary);
    }
    m_Animation->Draw(m_Tf);
}

void Warrior::Update(float dt) {

    m_IsRunning = false;
    m_IsCrouching = false;
    m_RigidBody->UnSetForce();

    // Run forward
    if (Input::Instance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking) {
        m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
        m_Tf->Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }

    // Run backward
    if (Input::Instance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking) {
        m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
        m_Tf->Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    // Crouch
    if (Input::Instance()->GetKeyDown(SDL_SCANCODE_S)) {
        m_RigidBody->UnSetForce();
        m_IsCrouching = true;
    }

    // Attack
    if (Input::Instance()->GetKeyDown(SDL_SCANCODE_K)) {
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
    }

    // Jump
    if (Input::Instance()->GetKeyDown(SDL_SCANCODE_J) && m_IsGrounded) {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    if (Input::Instance()->GetKeyDown(SDL_SCANCODE_J) && m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    else {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // Fall
    if (m_RigidBody->Veclocity().Y > 0 && !m_IsGrounded)
        m_IsFalling = true;
    else
        m_IsFalling = false;

    // Attack timer
    if (m_IsAttacking && m_AttackTime > 0) {
        m_AttackTime -= dt;
    }
    else {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Tf->X;
    m_Tf->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 18, 50);

    if (m_Collider->CollideWithMap())
        m_Tf->X = m_LastSafePosition.X;


    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Tf->Y;
    m_Tf->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 18, 50);

    if (m_Collider->CollideWithMap()) {
        m_IsGrounded = true;
        m_Tf->Y = m_LastSafePosition.Y;
    }
    else {
        m_IsGrounded = false;
    }

    GameObject::Update(dt);
    if (m_HealthPoint >= m_HPcap) {
        m_HealthPoint = m_HPcap;
    }
    if (m_HealthPoint <= 0) {
        m_IsDead = true;
        Clean();
    }
    AnimationState();
    m_Animation->Update(dt);
}


void Warrior::AnimationState() {
    // idling
    m_Tf->TextureID = "player_idle";
    m_Animation->SetProps(0, 6, 100);

    // running
    if (m_IsRunning) {
        m_Tf->TextureID = "player_run";
        m_Animation->SetProps(0, 4, 100);
    }

    // crouching
    if (m_IsCrouching) {
        m_Tf->TextureID = "player_crouch";
        m_Animation->SetProps(0, 6, 100);
    }

    // jumping
    if (m_IsJumping) {
        m_Tf->TextureID = "player_jump";
        m_Animation->SetProps(0, 2, 200);
    }

    // falling
    if (m_IsFalling) {
        m_Tf->TextureID = "player_fall";
        m_Animation->SetProps(0, 2, 400);
    }

    // attacking
    if (m_IsAttacking) {
        m_Tf->TextureID = "player_attack";
        m_Animation->SetProps(0, 14, 80);
    }
}

void Warrior::Clean() {

}

