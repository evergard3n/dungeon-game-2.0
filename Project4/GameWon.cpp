#include "GameWon.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "StateManager.h"
#include "Button.h"





GameWon::GameWon() {}
bool GameWon::Init() {

    m_ClearColor = { 16, 45, 70 };
    m_Ctxt = Engine::Instance()->GetRenderer();
    //Parser::Instance()->ParseTextures("assets/gui_textures.tml");

    Button* playbtn = new Button(250, 100, StartGame, { "playag_n", "playag_h", "playag_p" });
    //Button* settbtn = new Button(250, 250, Settings, { "opt_n", "opt_h", "opt_p" });
    Button* quitbtn = new Button(250, 300, QuitGame, { "quit_n", "quit_h", "quit_p" });
    TextureMgr::Instance()->Add("background4", "textures2/bocchi bg go.png");
    m_GuiObjects.push_back(playbtn);
    //m_GuiObjects.push_back(settbtn);
    m_GuiObjects.push_back(quitbtn);

    std::cout << "menu initialized!" << std::endl;
    return true;
}
void GameWon::Render() {
    SDL_SetRenderDrawColor(m_Ctxt, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    SDL_RenderClear(m_Ctxt);
    TextureMgr::Instance()->Draw(new Transform(0, 0, 1980, 1020, "background4"));
    for (auto object : m_GuiObjects)
        object->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void GameWon::Update() {
    for (auto object : m_GuiObjects)
        object->Update(0);
}

bool GameWon::Exit() {
    m_GuiObjects.clear();
    TextureMgr::Instance()->Clean();
    return true;
}

// Callbacks
void GameWon::StartGame() {
    StateMgr::Instance()->PushState(new Play());
}

void GameWon::Settings() {
    std::cout << "options mode\n";
}

void GameWon::QuitGame() {
    Engine::Instance()->Close();
}


