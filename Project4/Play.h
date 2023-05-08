#ifndef PLAY_H
#define PLAY_H

#include <map>
#include <iostream>
#include "TileMap.h"
#include "GameObject.h"
#include "GameState.h"
#include "Enemies.h"
#include "Warrior.h"
#include "Timer.h"
#include "Input.h"
#include "Camera.h"
#include "Parser.h"
#include "TileLayer.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "CollisionHandler.h"
#include "StateManager.h"
#include "Menu.h"
#include <unordered_map>
#include "Button.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
class Play : public GameState {

public:
    Play();
    
    void Events();
    virtual bool Init();
    virtual bool Exit();
    virtual void Update();
    void addCharacter(Enemy* enemy);
    void removeCharacter(Enemy* enemy);
    virtual void Render();
    inline int GetEnemyNumberNextWave();
    inline int WavesLeft() { return m_EnemyWaveLeft; }
    void spawnEnemy(int n);
    Vector2D GetPlayerPos();
    //static Warrior* GetPlayer() { return m_Player; }
    
    
private:
    static void OpenMenu();
    static void Options();
    static void QuitGame();
    
private:
    Warrior* m_Player;
    //static Play* s_Instance;
    //Menu* menu;
    bool ShowInfo;
    int m_EnemyWaveLeft;
    int m_ThisWaveEnemy;
    TileMap* m_TilelMap;
    ObjectList m_UiObjects;
    ObjectList m_GameObjects;
    Button* menubtn;
    TTF_Font* font;
    std::string s;
    std::string s2;
    friend class Enemy;
    Mix_Music* music;
    Mix_Chunk* sfx_1;
    Mix_Chunk* sfx_2;
    bool PlayingMusic;
    std::unordered_map<int, Enemy*> m_Enemies;
};

#endif // PLAY_H
