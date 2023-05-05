#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"
#include "GameObject.h"
#include "Warrior.h"
#include <unordered_map>
#include <SDL_ttf.h>
#include <wincrypt.h>
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine {

public:
    static Engine* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
    }

    bool Init();
    void Clean();
    void Quit();

    void Update();
    void Render();
    void Events();
    void addCharacter(GameObject* object);
    void removeCharacter(GameObject* object);
    inline Warrior* GetPlayer() { return player; }
    inline GameMap* GetMap() { return m_LevelMap; }
    inline bool IsRunning() { return m_IsRunning; }
    inline TTF_Font* GetFont() { return font; }
    inline int GetEnemyNumberNextWave();
    inline SDL_Renderer* GetRenderer() { return m_Renderer; }
    int WavesLeft() { return m_EnemyWaveLeft; }
    void SpawnEnemy(int n);
private:
    Engine() {}
    int m_EnemyWaveLeft;
    int m_ThisWaveEnemy;
    bool m_IsRunning = false;
    Warrior* player = nullptr;
    GameMap* m_LevelMap;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    TTF_Font* font = nullptr;
    static Engine* s_Instance;
    std::unordered_map<int, GameObject*> m_GameObjects;
};

#endif // ENGINE_H
