#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "Collision.h"
#include "Camera.h"

Warrior::Warrior(Properties* props) : Character(props) {

    m_jumptime = JUMP_TIME;
    m_jumpforce = JUMP_FORCE;
    m_attackTime = ATTACK_TIME;

    m_impact = new impact();
    m_impact->sethitBox(-60, -20, 0, 0);

    m_rigidBody = new RigidBody();
    m_rigidBody->setGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 4, 100);
}

void Warrior::Draw() {
    

    Vector2D cam = Camera::getInstance()->getpos();
    SDL_Rect box = m_impact->get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt) {

    m_Animation->SetProps("player", 1, 4, 100);
    m_rigidBody->unsetForce();

    if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_A)) {
        m_rigidBody->applyForceX(5 * BACKWARD);
        m_Animation->SetProps("player_running", 1, 4, 100, SDL_FLIP_HORIZONTAL);
    }

    if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_D)) {
        m_rigidBody->applyForceX(5 * FORWARD);
        m_Animation->SetProps("player_running", 1, 4, 100);
    }

    // Jump
    if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_J) && m_isGrounded) {
        m_isJumping = true;
        m_isGrounded = false;
        m_rigidBody->applyForceY(UPWARD * m_jumpforce);
    }
    if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_J) && m_isJumping && m_jumptime > 0) {
        m_jumptime -= dt;
        m_rigidBody->applyForceY(UPWARD * m_jumpforce);
        m_Animation->SetProps("player_running", 1, 4, 100);
    }
    else {
        m_isJumping = false;
        m_jumptime = JUMP_TIME;
    }

    // move on X axis
    m_rigidBody->Update(dt);
    m_lastSafePos.X = m_Transform->X;
    m_Transform->X += m_rigidBody->position().X;
    m_impact->set(m_Transform->X, m_Transform->Y, 200, 200);

    if (Collision::getInstance()->mapCollision(m_impact->get()))
        m_Transform->X = m_lastSafePos.X;


    // move on Y axis
    m_rigidBody->Update(dt);
    m_lastSafePos.Y = m_Transform->Y;
    m_Transform->Y += m_rigidBody->position().Y;
    m_impact->set(m_Transform->X, m_Transform->Y, 200, 200);

    if (Collision::getInstance()->mapCollision(m_impact->get())) {
        m_isGrounded = true;
        m_Transform->Y = m_lastSafePos.Y;
    }
    else {
        m_isGrounded = false;
    }

    if (m_isJumping || !m_isGrounded) {
        m_Animation->SetProps("player_running", 1, 4, 100);
    }

    m_origin->X = m_Transform->X + m_Width / 2;
    m_origin->Y = m_Transform->Y + m_Height / 2;
    m_Animation->Update();
}

void Warrior::Clean() {
    TextureManager::GetInstance()->Drop(m_TextureID);
}

