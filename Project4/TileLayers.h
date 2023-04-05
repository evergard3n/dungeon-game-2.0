#pragma once
#include "layer.h"
#include <string>
#include <vector>
using namespace std;
struct Tileset
{
	int firstID, lastID;
	int numRows, numCols;
	int tileCount, tileSize;
	string name, source;
};
using tilesetlist = vector<Tileset>;
using tilemap = vector<vector<int>>;
class TileLayer : public layer
{
public:
	TileLayer(int tilesize, int rowCount, int colCount, tilemap tilemap, tilesetlist tilesets);
	virtual void render();
	virtual void update();
	inline tilemap getTilemap() {
		return m_tilemap;
	}
private:
	int m_tileSize;
	int m_rowCount, m_colCount;
	tilemap m_tilemap;
	tilesetlist m_tilesets;
};