#include "Engine.h"
#include "Play.h"
#include "Menu.h"
#include "StateManager.h"

Engine* Engine::s_Instance = nullptr;

void Engine::Init() {
    srand(time(NULL));
    SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_RendererFlags r_flags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    m_ScreenViewPort = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, w_flags);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create Window: %s", SDL_GetError());
	}
	m_Renderer = SDL_CreateRenderer(m_Window, -1, r_flags);
	
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		
	}
	if (TTF_Init() == -1) {
		std::cout << "Unable to initialize SDL_ttf\n" << std::endl;
		std::cout << "Error: " << TTF_GetError() << "\n" << std::endl;
		
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
    StateMgr::Instance()->ChangeState(new Menu());
    m_IsRunning = true;
}

Engine::~Engine() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    //Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}





