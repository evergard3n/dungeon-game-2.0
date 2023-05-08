#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Transform.h"
#include <iostream>
#include <string>
#include "SDL.h"
#include <map>
#include <SDL_ttf.h>
using TextureMap = std::map<std::string, SDL_Texture*>;

class TextureMgr {

public:
    void Clean();
    SDL_Texture* Load(std::string filename);
    bool Add(std::string id, std::string filename);
    void QueryTexture(std::string id, int* out_w, int* out_h);

    void Draw(Transform* tf);
    void DrawFrame(Transform* tf, int row, int frame);
    void DrawTile(std::string tilesetID, int x, int y, int tilesize, int row, int col, float speedRatio = 1.0f);
    void LoadText(std::string id, std::string text, int x, int y, SDL_Color text_color, TTF_Font* font);
    void DrawStatic(Transform* tf);
    inline TextureMap GetTextureMap() { return m_TextureMap; }
    inline SDL_Texture* GetTexture(std::string id) { return m_TextureMap[id]; }
    inline static TextureMgr* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureMgr(); }

private:
    TextureMgr();
    TextureMap m_TextureMap;
    SDL_Renderer* m_Renderer;
    static TextureMgr* s_Instance;
};

#endif // TEXTUREMANAGER_H
