#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "GameState.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Engine {

public:
    ~Engine();
    void Init();

    inline void Close() { m_IsRunning = false; }
    inline bool IsRunning() { return m_IsRunning; }

    inline SDL_Window* GetWindow() { return m_Window; }
    inline SDL_Renderer* GetRenderer() { return m_Renderer; }

    inline SDL_Rect GetViewPort() { return m_ScreenViewPort; }
    inline void SetViewPort(SDL_Rect viewport) { m_ScreenViewPort = viewport; }

    inline static Engine* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine(); }

private:
    Engine() {}
    bool m_IsRunning;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Rect m_ScreenViewPort;
    static Engine* s_Instance;
};

#endif // ENGINE_H
