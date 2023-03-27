#include "Warrior.h"
#include "Animation.h"
#include  "TextureManager.h"
#include "Transform.h" 
#include <SDL.h>
Warrior::Warrior(Properties* props) :Character(props){
	m_rigidBody = new RigidBody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 4, 100, SDL_FLIP_NONE);
}


void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}

void Warrior::Update(float dt)
{
	m_rigidBody->unsetForce();
	m_Animation->SetProps("player", 1, 4, 100);
	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_A)) {
		m_rigidBody->applyForceX(5*BACKWARD);
		m_Animation->SetProps("player_running", 1, 4, 100, SDL_FLIP_HORIZONTAL);
	}
	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_D)) {
		m_rigidBody->applyForceX(5*FORWARD);
		m_Animation->SetProps("player_running", 1, 4, 100, SDL_FLIP_NONE);
	}
	
	m_rigidBody->Update(0.8);
	//m_rigidBody->applyForceX(5);
	m_Transform->TranslateX (m_rigidBody->position().X);
	//m_Transform->TranslateY (m_rigidBody->position().Y);
	
	m_Animation->Update();
}

