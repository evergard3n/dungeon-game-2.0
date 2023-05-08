#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"
#include <vector>
#include "Vector2D.h"

enum Axis { HORIZONTAL, VERTICAL };
enum MouseButtons { LEFT, MIDDLE, RIGHT };

class Input {

public:
    void Listen();
    int GetAxisKey(Axis axis);
    inline bool GetKeyDown(SDL_Scancode key) { return (m_KeyStates[key]) ? true : false; }

    inline Vector2D GetMousePosition() { return m_MousePosition; }
    inline Vector2D GetMouseLastPosition() { return m_MouseLastPosition; }
    inline bool GetMouseButtonDown(MouseButtons button) { return m_MouseButtonStates[button]; }
    inline static Input* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input(); }

private:
    Input();

    // keyboard event
    void KeyUp();
    void KeyDown();

    // window event
    void WindowEvent(SDL_Event event);

    // mouse button event
    void MouseMotion(SDL_Event event);
    void MouseButtonUp(SDL_Event event);
    void MouseButtonDown(SDL_Event event);

private:
    const Uint8* m_KeyStates;
    static Input* s_Instance;
    Vector2D m_MousePosition;
    Vector2D m_MouseLastPosition;
    std::vector<bool> m_MouseButtonStates;
};

#endif // INPUT_H
