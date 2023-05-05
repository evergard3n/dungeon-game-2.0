#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include <SDL_ttf.h>
Warrior::Warrior(Properties* props) : Character(props) {

    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-20, -10, 10, 50);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(4.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 4, 100);
}

void Warrior::Draw() {
    if (life_lefts() > 0) {
        m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

        Vector2D cam = Camera::GetInstance()->GetPosition();
        SDL_Rect box = m_Collider->Get();
        box.x -= cam.X;
        box.y -= cam.Y;
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
        SDL_Rect health_bar = { m_Transform->X + 20, m_Transform->Y, 40, 3 };
        health_bar.x -= cam.X;
        health_bar.y -= cam.Y;
        health_bar.w *= m_HealthPoint / 100;
        SDL_Rect health_bar_bg = { m_Transform->X + 20, m_Transform->Y, 40, 3 };
        health_bar_bg.x -= cam.X;
        health_bar_bg.y -= cam.Y;
        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 100);
        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &health_bar_bg);
        
        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 100);
        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &health_bar);
        for (int i = 0; i < life_lefts(); i++) {
            int x = m_Transform->X+21;
            TextureManager::GetInstance()->Draw("heart",x+i*11, health_bar_bg.y - cam.Y - 20, 10, 10);
        }
    }
}

void Warrior::Update(float dt) {

    if (life_lefts() <= 0) {
        std::cout << "Game Over!" << std::endl;
        Clean();
    }
    else {
        m_Animation->SetProps("player", 1, 4, 100);
        m_RigidBody->UnSetForce();
        m_IsAttacking = false;

        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
            m_RigidBody->ApplyForceX(3 * BACKWARD);
            m_Flip = SDL_FLIP_HORIZONTAL;
            m_Animation->SetProps("player_run", 1, 4, 100, SDL_FLIP_HORIZONTAL);
        }

        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
            m_RigidBody->ApplyForceX(3 * FORWARD);
            m_Flip = SDL_FLIP_NONE;
            m_Animation->SetProps("player_run", 1, 4, 100);
        }
        if (m_Flip == SDL_FLIP_HORIZONTAL) {
            m_Animation->SetProps("player", 1, 4, 100, SDL_FLIP_HORIZONTAL);
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
        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_G) && m_IsGrounded) {
            m_IsAttacking = true;
            m_Animation->SetProps("player_attacking", 1, 4, 100, m_Flip);
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
            if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) m_Animation->SetProps("player_jump", 1, 2, 150, m_Flip);
            else m_Animation->SetProps("player_jump", 1, 2, 150);

        }
        std::cout << m_HealthPoint << std::endl;
        //current losing condition code
        /*if (m_Transform->Y / 32 >= 17 || m_HealthPoint <= 0) {
            std::cout << "Game Over!" << std::endl;
            Engine::GetInstance()->Clean();
            Engine::GetInstance()->Quit();
        }*/
        //current winning condition

        //std::cout << m_Transform->X << " " << m_Transform->Y << std::endl;


        if (Engine::GetInstance()->WavesLeft()==-1) {
            std::cout << "You Won!" << std::endl;
            m_Won = true;
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

        if (CollisionHandler::GetInstance()->ConditionCollision(m_Collider->Get(), 0) == 104) {
            std::cout << "healing" << std::endl;
            m_HealthPoint = DEFAULT_HP;

        }

        m_Origin->X = m_Transform->X + m_Width / 2;
        m_Origin->Y = m_Transform->Y + m_Height / 2;
        m_Animation->Update();
    }
    
}

int Warrior::life_lefts()
{
    if (m_HealthPoint <= 0) {
        m_lives--;
        m_HealthPoint = DEFAULT_HP;
    }
    return m_lives;
}



void Warrior::Clean() {
    TextureManager::GetInstance()->Drop(m_TextureID);
}

