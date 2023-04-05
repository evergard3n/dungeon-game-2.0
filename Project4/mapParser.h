#pragma once
#include <map>
#include <string>
#include "gameMap.h"
#include "TileLayers.h"
#include "tinyxml1.h"

using namespace std;
class mapParser
{
public:
	bool load();
	void clean();
	inline gameMap* getMaps(string id) {
		return m_mapDict[id];
	}
	inline static mapParser* getInstance() {
		return s_instance = (s_instance != nullptr) ? s_instance : new mapParser();
	}
private:
	bool parse(string id, string source);
	Tileset parseTileset(TiXmlElement* xmlTileset);
	TileLayer* parseTileLayer(TiXmlElement* xmlLayer, tilesetlist tilesets, int tilesize, int rowcount, int colcount);
	mapParser(){}
	static mapParser* s_instance;
	map<string, gameMap*> m_mapDict;
};

