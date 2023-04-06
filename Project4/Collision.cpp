#include "Collision.h"
#include "Engine.h"
Collision* Collision::s_Instance = nullptr;
Collision::Collision() {
	m_collisionLayer = (TileLayer*)Engine::GetInstance()->getMap()->getMapLayers().front();
	m_layerTilemap = m_collisionLayer->getTilemap();
}

bool Collision::checkCollision(SDL_Rect a, SDL_Rect b)
{
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
	return (x_overlaps && y_overlaps);
}
bool Collision::mapCollision(SDL_Rect a)
{
	int tilesize = 32;
	int rowcount = 20;
	int colcount = 60;

	int left_tile = a.x / tilesize;
	int right_tile = (a.x + a.w) / tilesize;

	int top_tile = a.y / tilesize;
	int bot_tile = (a.y + a.h) / tilesize;

	if (left_tile < 0) left_tile = 0;
	if (right_tile > colcount)right_tile = colcount;

	if (top_tile < 0) top_tile = 0;
	if (bot_tile > rowcount)bot_tile = rowcount;

	for (int i = left_tile; i <= right_tile; i++) {
		for (int j = top_tile; j <= bot_tile; j++) {
			if (m_layerTilemap[j][i] > 0) return true;
		}
	}
	
	return false;
}
