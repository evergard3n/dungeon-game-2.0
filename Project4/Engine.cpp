#include "Engine.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Warrior.h"
#include "Animation.h"
#include "Input.h"
#include "Timer.h"
#include "mapParser.h"
#include <SDL.h>
#include <iostream>
Engine* Engine::s_Instance = nullptr;
//GameObject* background = nullptr;
Warrior* player = nullptr;


bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && SDL_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize sdl: %s", SDL_GetError());
		return false;
	}
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	m_Window = SDL_CreateWindow("bruh", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	if (!mapParser::getInstance()->load()) {
		cout << "Failed to load map" << endl;
		return false;
	}
	m_LevelMap = mapParser::getInstance()->getMaps("MAP");

	
	//background = new Properties("background", 0, 0, 50, 50);
	TextureManager::GetInstance()->Load("player", "textures/bocchi hero.png");
	TextureManager::GetInstance()->Load("player_running", "textures/running.png");
	player = new Warrior(new Properties("player", 100, 500, 192, 192));
	Transform tf;
	tf.Log();
	return m_IsRunning = true;
}

void Engine::Clean()

{
	TextureManager::GetInstance()->Clean();
	mapParser::getInstance()->clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
}

void Engine::Quit()
{
	m_IsRunning = false;
}

void Engine::Update()
{
	float dt= Timer::getInstance()->getDeltaTime();
	
	player->Update(dt);
	m_LevelMap->update();
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_Renderer);
	m_LevelMap->render();
	player->Draw();
	
	SDL_RenderPresent(m_Renderer);
	
}

void Engine::Events()
{
	Input::GetInstance()->listen();
}
