#include "Enemies.h"
#include "CollisionHandler.h"
#include "Engine.h"
#include "Camera.h"
float absolute(float a, float b)
{
	if (a - b >= 0) return a - b;
	else return b - a;
}
Enemies::Enemies(Properties* props): Character(props)
{
	if (Engine::GetInstance()->WavesLeft() > 3) {
		m_HealthPoint = DEFAULT_HP;
		m_Damage = 0.06;
	}
	else if(Engine::GetInstance()->WavesLeft()==3){
		m_HealthPoint = DEFAULT_HP*1.5;
		m_Damage = 0.08;
	}
	else {
		m_HealthPoint = DEFAULT_HP * 2;
		m_Damage = 0.015;
	}
	m_EneCollider = new Collider();
	m_EneCollider->SetBuffer(-20, -10, 10, 50);
	m_EneRigidbody = new RigidBody();

	m_EneAnimation = new Animation();
	m_EneAnimation->SetProps(m_TextureID, 1, 4, 100);
}

void Enemies::Draw()
{
	Vector2D cam = Camera::GetInstance()->GetPosition();
	m_EneAnimation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	SDL_Rect box = m_EneCollider->Get();
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
	SDL_Rect health_bar = { m_Transform->X, m_Transform->Y, 20, 3 };
	health_bar.x -= cam.X;
	health_bar.y -= cam.Y;
	health_bar.w *= m_HealthPoint / 100;
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 100);
	if(m_HealthPoint>0) SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &health_bar);
}

void Enemies::Clean()
{
	TextureManager::GetInstance()->Drop(m_TextureID);
}

void Enemies::Update(float dt)
{
	m_IsDead = false;
	m_EneAnimation->SetProps("enemies", 1, 4, 100);
	m_EneRigidbody->Update(dt);
	m_EneLastSafePos.X = m_Transform->X;
	m_Transform->X += m_EneRigidbody->Position().X;
	m_EneCollider->Set(m_Transform->X, m_Transform->Y, 40, 80);
	if (CollisionHandler::GetInstance()->MapCollision(m_EneCollider->Get()))
		m_Transform->X = m_EneLastSafePos.X;
	float playerPosX = Engine::GetInstance()->GetPlayer()->m_Transform->X;
	float playerPosY = Engine::GetInstance()->GetPlayer()->m_Transform->Y;
	float temp_time = 2;
	if (m_HealthPoint <= 0) {
		m_IsDead = true;
		m_IsAttacking = false;
	}	
	else {
		if (absolute(playerPosX, m_Transform->X) <= 32 * 5) {

			if (playerPosX == m_Transform->X) {
				m_EneRigidbody->UnSetForce();
				m_IsIdle = true;
				m_EneAnimation->SetProps("enemies", 1, 4, 100, m_Flip);
			}
			if (playerPosX < m_Transform->X) {
				m_Flip = SDL_FLIP_NONE;
				m_IsWalking = true;
				m_EneAnimation->SetProps("enemies_walking", 1, 4, 100, m_Flip);
				m_EneRigidbody->ApplyForceX(0.5 * BACKWARD);
			}

			if (playerPosX > m_Transform->X) {
				m_Flip = SDL_FLIP_HORIZONTAL;
				m_IsWalking = true;
				m_EneAnimation->SetProps("enemies_walking", 1, 4, 100, m_Flip);
				m_EneRigidbody->ApplyForceX(0.5 * FORWARD);
			}
		}
		else {
			m_EneRigidbody->UnSetForce();
			m_IsIdle = true;
			m_EneAnimation->SetProps("enemies", 1, 4, 100, m_Flip);
		}
		//attacking
		
		if (CollisionHandler::GetInstance()->CheckCollision(m_EneCollider->Get(), Engine::GetInstance()->GetPlayer()->m_Collider->Get())) {
			if (Engine::GetInstance()->GetPlayer()->m_IsAttacking == false) {
				m_IsAttacking = true;
				m_EneAnimation->SetProps("enemies_attacking", 1, 4, 100, m_Flip);
				Engine::GetInstance()->GetPlayer()->m_HealthPoint -= m_Damage;
				
			}
			else {
				m_IsAttacking = false;
				m_EneAnimation->SetProps("enemies_hurt", 1, 2, 400, m_Flip);
				m_HealthPoint -= 2.0;
			}

		}
		
		
	}
	
	
	
	m_EneRigidbody->Update(dt);
	m_EneLastSafePos.Y = m_Transform->Y;
	m_Transform->Y += m_EneRigidbody->Position().Y;
	m_EneCollider->Set(m_Transform->X, m_Transform->Y, 40, 80);
	//std::cout << RandomSpawnPos().X <<" "<< RandomSpawnPos().Y << std::endl;
	if (CollisionHandler::GetInstance()->MapCollision(m_EneCollider->Get()))
		m_Transform->Y = m_EneLastSafePos.Y;
	m_EneAnimation->Update();
	
}

int Enemies::randomEneType()
{
	srand(time(0));
	m_EneType = rand() % 2;
	return m_EneType;
}

Vector2D Enemies::RandomSpawnPos()
{
	Vector2D spawnPos;
	srand(time(0));
	int UpBoundX = 60;
	int LowBoundX = 3;
	int UpBoundY = 5, LowBoundY = 3;
	spawnPos.X = rand() % (UpBoundX - LowBoundX + 1) + LowBoundX;
	spawnPos.Y = rand() % (UpBoundY - LowBoundY + 1) + LowBoundY;
	
	return spawnPos*32;
}




