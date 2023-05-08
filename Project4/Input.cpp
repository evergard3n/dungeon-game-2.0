#include "Input.h"
#include "Engine.h"
#include "Camera.h"

Input* Input::s_Instance = nullptr;

Input::Input() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    m_MouseButtonStates = { false, false, false };
}

void Input::Listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_WINDOWEVENT: WindowEvent(event); break;
        case SDL_QUIT: Engine::Instance()->Close(); break;
        case SDL_MOUSEBUTTONDOWN: MouseButtonDown(event); break;
        case SDL_MOUSEBUTTONUP: MouseButtonUp(event); break;
        case SDL_MOUSEMOTION: MouseMotion(event); break;
        case SDL_KEYDOWN: KeyDown(); break;
        case SDL_KEYUP: KeyUp(); break;
        }
    }
}

void Input::KeyUp() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::MouseMotion(SDL_Event event) {
    m_MouseLastPosition = m_MousePosition;
    m_MousePosition.X = event.motion.x;
    m_MousePosition.Y = event.motion.y;
}

void Input::MouseButtonUp(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT)
        m_MouseButtonStates[LEFT] = false;

    if (event.button.button == SDL_BUTTON_MIDDLE)
        m_MouseButtonStates[MIDDLE] = false;

    if (event.button.button == SDL_BUTTON_RIGHT)
        m_MouseButtonStates[RIGHT] = false;
}

void Input::MouseButtonDown(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT)
        m_MouseButtonStates[LEFT] = true;

    if (event.button.button == SDL_BUTTON_MIDDLE)
        m_MouseButtonStates[MIDDLE] = true;

    if (event.button.button == SDL_BUTTON_RIGHT)
        m_MouseButtonStates[RIGHT] = true;
}

void Input::WindowEvent(SDL_Event event) {
    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        const SDL_Rect viewport = { 0, 0, event.window.data1, event.window.data2 };
        Engine::Instance()->SetViewPort(viewport);
        Camera::Instance()->SetViewPort(viewport);
    }
}

int Input::GetAxisKey(Axis axis) {
    switch (axis) {
    case HORIZONTAL:
        if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT))
            return 1;
        if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT))
            return -1;
        break;

    case VERTICAL:
        if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP))
            return 1;
        if (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN))
            return -1;
        break;

    default:
        return 0;
    }
}

