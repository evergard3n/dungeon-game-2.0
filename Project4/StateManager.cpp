#include "StateManager.h"

StateMgr* StateMgr::s_Instance = nullptr;

void StateMgr::PopState() {
    SDL_Delay(100);
    if (m_GameStates.size() > 1) {
        if (m_GameStates.back()->Exit()) {
            delete m_GameStates.back();
            m_GameStates.pop_back();
        }
    }
}

void StateMgr::PushState(GameState* current) {
    SDL_Delay(100);
    m_GameStates.push_back(current);
    m_GameStates.back()->Init();
}

void StateMgr::ChangeState(GameState* target) {
    SDL_Delay(100);
    if (!m_GameStates.empty()) {
        if (m_GameStates.back()->Exit()) {
            delete m_GameStates.back();
            m_GameStates.pop_back();
        }
    }
    m_GameStates.push_back(target);
    m_GameStates.back()->Init();
}

void StateMgr::Render() {
    m_GameStates.back()->Render();
}

void StateMgr::Update() {
    m_GameStates.back()->Update();
}

