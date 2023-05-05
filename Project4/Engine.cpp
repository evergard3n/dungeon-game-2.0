#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Warrior.h"
#include "SDL.h"
#include "Timer.h"
#include "MapParser.h"
#include <iostream>
#include "Camera.h"
#include "Enemies.h"
#include <SDL_ttf.h>
#include <unordered_map>
Engine* Engine::s_Instance = nullptr;
Vector2D cam = Camera::GetInstance()->GetPosition();
SDL_Color white = { 255,255,255,255 };

int temp = 0;
bool Engine::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT+60, window_flags);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}
	if (TTF_Init() == -1) {
		std::cout << "Unable to initialize SDL_ttf\n"<<std::endl;
		std::cout << "Error: " << TTF_GetError() << "\n"<<std::endl;
		return 0;
	}
	if (!MapParser::GetInstance()->Load("testing.tmx")) {
		std::cout << "Failed to load map" << std::endl;
		return false;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("level1");
	font = TTF_OpenFont("textures/HelveticaWorld-Regular.ttf", 24);
	TextureManager::GetInstance()->Load("player", "textures/bocchi hero.png");
	TextureManager::GetInstance()->Load("player_run", "textures/running.png");
	TextureManager::GetInstance()->Load("player_jump", "textures/jumping 2.png");
	TextureManager::GetInstance()->Load("player_attacking", "textures/attacking.png");
	TextureManager::GetInstance()->Load("bg", "textures/map/bg full.jpg");
	TextureManager::GetInstance()->Load("enemies", "textures/Hyena_idle.png");
	TextureManager::GetInstance()->Load("enemies_walking", "textures/Hyena_walk.png");
	TextureManager::GetInstance()->Load("enemies_attacking", "textures/Hyena_attack.png");
	TextureManager::GetInstance()->Load("enemies_dying", "textures/Hyena_death.png");
	TextureManager::GetInstance()->Load("enemies_hurt", "textures/Hyena_hurt.png");
	TextureManager::GetInstance()->Load("heart", "textures/heart.png");
	player = new Warrior(new Properties("player", 50, 200, 96, 96));
	
	//addCharacter(player);
	//enemy = new Enemies(new Properties("enemies", 200, 200, 48, 48));
	m_EnemyWaveLeft = 5;
	SpawnEnemy(GetEnemyNumberNextWave());
	// for(int i=0; i<=)
	Camera::GetInstance()->SetTarget(player->GetOrigin());
	return m_IsRunning = true;
}

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("bg", 0, 30, 1920, 640);
	m_LevelMap->Render();
	player->Draw();
	for (auto& it : m_GameObjects) {
		int id = it.first;
		GameObject* enemies = it.second;
		enemies->Draw();
		//std::cout << id << std::endl;
	}
	SDL_RenderPresent(m_Renderer);
}

void Engine::Update() {
	float dt = Timer::GetInstance()->GetDeltaTime();
	player->Update(dt);
	m_LevelMap->Update();
	Camera::GetInstance()->Update(dt);
	std::string s = std::to_string(m_EnemyWaveLeft);
	
	std::vector<int> m_removedIds;
	for (auto& it : m_GameObjects) {
		int id = it.first;
		GameObject* enemies = it.second;
		enemies->Update(dt);
	}
	std::cout << m_ThisWaveEnemy <<" "<< temp << std::endl;
	for (auto& it : m_GameObjects) {
		int id = it.first;
		GameObject* object = it.second;
		
		Enemies* enemy = (Enemies*)object;
		if (enemy->IsDead()) {
			m_removedIds.push_back(enemy->GetId());
			temp++;
				if (temp == m_ThisWaveEnemy&&m_EnemyWaveLeft>=0) {
				m_EnemyWaveLeft--;
				temp = 0;
				m_removedIds.clear();
				SpawnEnemy(GetEnemyNumberNextWave());
				temp--;
			}
			//temp++;
				
		}
		
	}
	for (auto& id : m_removedIds) {
		removeCharacter(m_GameObjects[id]);
	}
	std::cout << m_EnemyWaveLeft << std::endl;
	//std::cout << Camera::GetInstance()->GetPosition().X << " " << Camera::GetInstance()->GetPosition().Y << std::endl;
}

void Engine::Events() {
	Input::GetInstance()->Listen();
}

void Engine::addCharacter(GameObject* object)
{
	m_GameObjects[object->GetId()] = object;
}

void Engine::removeCharacter(GameObject* object)
{
	m_GameObjects.erase(object->GetId());

}

inline int Engine::GetEnemyNumberNextWave()
{
	
	
	switch (m_EnemyWaveLeft)
	{
	case(5):
	{
		m_ThisWaveEnemy = 5;
		break;
	}
	case(4):
	{
		m_ThisWaveEnemy = 8;
		break;
	}
	case(3):
	{
		m_ThisWaveEnemy = 10;
		break;
	}
	case(2):
	{   m_ThisWaveEnemy = 13;
	break;
	}
	case(1):
	{
		m_ThisWaveEnemy = 16;
		break;
	}
	case(0):
	{
		m_ThisWaveEnemy = 20;
		break;
	}
	default:
	{
		m_ThisWaveEnemy = 0;
		break;
	}
	}
	return m_ThisWaveEnemy;
	
}



void Engine::SpawnEnemy(int n)
{
	for (int i = 1; i <= n; i++) {
		srand(time(0));
		int x = rand() % (200 - 3 + 1) + 300 * i;
		
		Enemies* enemy = new Enemies(new Properties("enemies", x%2500, 50, 48, 48));
		addCharacter(enemy);
	}
}




void Engine::Clean() {
	TextureManager::GetInstance()->Clean();
	MapParser::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	TTF_CloseFont(font);
	IMG_Quit();
	SDL_Quit();
	
}

void Engine::Quit() {
	m_IsRunning = false;
}
