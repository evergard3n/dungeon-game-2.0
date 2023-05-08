#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "TileMap.h"

class CollisionHandler {

public:
    bool MapCollision(SDL_Rect a);
    bool CheckCollision(SDL_Rect a, SDL_Rect b);
    void SetCollisionLayer(TileLayer* layer);
    int ConditionCollision(SDL_Rect a, TileLayer* tilelayer);
    inline static CollisionHandler* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

private:
    CollisionHandler() {}

    int m_MapTileSize;
    int m_MapWidth, m_MapHeight;
    TileMatrix m_CollisionTilemap;
    static CollisionHandler* s_Instance;
};

#endif // COLLISIONHANDLER_H
