#include "mapParser.h"

mapParser* mapParser::s_instance = nullptr;

bool mapParser::load() {
    if (!parse("MAP", "textures/map/help.tmx"))
        return false;
    return true;
}

bool mapParser::parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();

    int colcount, rowcount, tilesize = 0;
    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    // Parse Tile sets
    tilesetlist tilesets;
   
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            tilesets.push_back(parseTileset(e));
        }
    }

    // Parse Layers
    gameMap* gamemap = new gameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            TileLayer* tilelayer = parseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_mapLayers.push_back(tilelayer);
        }
    }

    m_mapDict[id] = gamemap;
    return true;
}

TileLayer* mapParser::parseTileLayer(TiXmlElement* xmlLayer, tilesetlist tilesets, int tilesize, int rowcount, int colcount) {
    //int layerID = 0;
    //xmlLayer->Attribute("id", &layerID);

    TiXmlElement* data = nullptr;
    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            data = e;
            break;
        }
    }

    // Parse Layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;
    
    tilemap tilemap(rowcount, std::vector<int>(colcount, 0));
    for (int row = 0; row < rowcount; row++) {
        for (int col = 0; col < colcount; col++) {
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good())
                break;
        }
    }

    return (new TileLayer(tilesize, colcount, rowcount, tilemap, tilesets));
}

Tileset mapParser::parseTileset(TiXmlElement* xmlTileset) {
    Tileset tileset;
    tileset.name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.firstID);
    xmlTileset->Attribute("tilecount", &tileset.tileCount);
    tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.numCols);
    tileset.numRows = tileset.tileCount / tileset.numCols;
    xmlTileset->Attribute("tilewidth", &tileset.tileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.source = image->Attribute("source");
    return tileset;
}

void mapParser::clean() {
    std::map<std::string, gameMap*>::iterator it;
    for (it = m_mapDict.begin(); it != m_mapDict.end(); it++)
        it->second = nullptr;

    m_mapDict.clear();
}

