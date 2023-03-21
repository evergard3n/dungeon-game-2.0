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
	m_rigidBody->Update(0.1);
	m_Transform->TranslateX (m_rigidBody->position().X);
	m_Transform->TranslateY (m_rigidBody->position().Y);
	
	m_Animation->Update();
}

