#pragma once
#include <SDL.h>
#include<vector>
#include "TileLayers.h"
#include "gameMap.h"
#include "Engine.h"
class Collision
{
public:
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	bool mapCollision(SDL_Rect a);
	inline static Collision* getInstance() {
		if (s_Instance == nullptr) s_Instance : new Collision();
		return s_Instance;
	}
private:
	Collision();
	static Collision* s_Instance;
	tilemap m_layerTilemap;
	TileLayer* m_collisionLayer;
	
};

