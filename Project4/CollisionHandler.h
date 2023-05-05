#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "GameMap.h"

class CollisionHandler {

public:
    bool MapCollision(SDL_Rect a);
    bool CheckCollision(SDL_Rect a, SDL_Rect b);
    int ConditionCollision(SDL_Rect a,int index);
    TileMap GetCollisionTilemap() { return m_CollisionTilemap; }
    inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

private:
    CollisionHandler();
    TileMap m_CollisionTilemap;
    TileLayer* m_CollisionLayer;
    TileLayer* m_CollisionLayerBack;
    TileMap m_CollisionTilemapBack;
    static CollisionHandler* s_Instance;
    friend class Enemies;
};

#endif // COLLISIONHANDLER_H
