#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"

Warrior::Warrior(Properties* props) : Character(props) {

    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-20, -10, 10, 50);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 4, 100);
}

void Warrior::Draw() {
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt) {

    m_Animation->SetProps("player", 1, 4, 100);
    m_RigidBody->UnSetForce();

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_RigidBody->ApplyForceX(3 * BACKWARD);
        m_Animation->SetProps("player_run", 1, 4, 100, SDL_FLIP_HORIZONTAL);
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_RigidBody->ApplyForceX(3 * FORWARD);
        m_Animation->SetProps("player_run", 1, 4, 100);
    }

    // Jump
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded) {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    else {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 60, 96);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;


    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 60, 96);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else {
        m_IsGrounded = false;
    }

    if (m_IsJumping || !m_IsGrounded) {
        m_Animation->SetProps("player_jump", 1, 2, 150);
    }
    //current losing condition code
    if(m_Transform->Y/32>=17) {
        std::cout << "Game Over!" << std::endl;
        Engine::GetInstance()->Clean();
        Engine::GetInstance()->Quit();
    }
    //current winning condition
    std::cout << m_Transform->X << " " << m_Transform->Y << std::endl;
    
    if (m_Transform->Y == 197 && m_Transform->X == 1673) {
        std::cout << "Stage Cleared!" << std::endl;
        Engine::GetInstance()->Clean();
        Engine::GetInstance()->Quit();
    }
    
    /*if (CollisionHandler::GetInstance()->ConditionCollision(m_Collider->Get(), 27)) {
        m_RigidBody->Update(dt);
        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
            m_RigidBody->UnSetForce();
            m_RigidBody->ApplyForceX(1 * FORWARD);
            m_Animation->SetProps("player_run", 1, 4, 100, SDL_FLIP_HORIZONTAL);
        }

        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
            m_RigidBody->UnSetForce();
            m_RigidBody->ApplyForceX(1 * FORWARD);
            m_Animation->SetProps("player_run", 1, 4, 100);
        }
        m_RigidBody->Update(dt);
        
    }*/
    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;
    m_Animation->Update();
}

void Warrior::Clean() {
    TextureManager::GetInstance()->Drop(m_TextureID);
}

