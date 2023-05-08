#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "StateManager.h"
#include "Button.h"


Menu::Menu() {}

bool Menu::Init() {

    m_ClearColor = { 16, 45, 70 };
    m_Ctxt = Engine::Instance()->GetRenderer();
    Parser::Instance()->ParseTextures("assets/textures.tml");

    Button* playbtn = new Button(250, 100, StartGame, { "play_n", "play_h", "play_p" });
    //Button* settbtn = new Button(250, 250, Settings, { "opt_n", "opt_h", "opt_p" });
    Button* quitbtn = new Button(250, 300, QuitGame, { "quit_n", "quit_h", "quit_p" });
    TextureMgr::Instance()->Add("background3", "textures2/bocchi bg.jpeg");
    m_GuiObjects.push_back(playbtn);
    //m_GuiObjects.push_back(settbtn);
    m_GuiObjects.push_back(quitbtn);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    music = Mix_LoadMUS("assets/sounds/valley.wav");
    if (music == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        
    }
    Mix_PlayMusic(music, -1);
    std::cout << "menu initialized!" << std::endl;
    return true;
}

void Menu::Render() {
    SDL_SetRenderDrawColor(m_Ctxt, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    SDL_RenderClear(m_Ctxt);
    TextureMgr::Instance()->Draw(new Transform(0, 0, 1980, 1020, "background3"));
    for (auto object : m_GuiObjects)
        object->Draw();
    
    SDL_RenderPresent(m_Ctxt);
}

void Menu::Update() {
    for (auto object : m_GuiObjects)
        object->Update(0);
}

bool Menu::Exit() {
    m_GuiObjects.clear();
    TextureMgr::Instance()->Clean();
    return true;
}

// Callbacks
void Menu::StartGame() {
    StateMgr::Instance()->PushState(new Play());
}

void Menu::Settings() {
    std::cout << "options mode\n";
}

void Menu::QuitGame() {
    Engine::Instance()->Close();
}


