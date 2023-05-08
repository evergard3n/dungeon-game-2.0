#include "Parser.h"
#include "TextureManager.h"
#include "ObjectFactory.h"
Parser* Parser::s_Instance = nullptr;
using ObjectPtr = GameObject*;

bool Parser::ParseTextures(std::string source) {

    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("texture")) {
            std::string id = e->Attribute("id");
            std::string source = e->Attribute("source");
            TextureMgr::Instance()->Add(id, source);
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return true;
}

TileMap* Parser::ParseMap(std::string source) {

    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cerr << "Failed to load: " << source << std::endl;
        return nullptr;
    }

    TiXmlElement* root = xml.RootElement();

    int colcount, rowcount, tilesize = 0;
    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    // Parse Tile sets
    TilesetsList tilesets;
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            tilesets.push_back(ParseTileset(e));
        }
    }

    // Parse Layers
    TileMap* gamemap = new TileMap();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return gamemap;
}

bool Parser::ParseGameObjects(std::string source, ObjectList* target) {

    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cout << "Failed to load: " << source << " " << xml.ErrorDesc() << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();

    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("object")) {

            int x, y, width, height, flip = 0;
            double scX, scY, sratio, rot = 0.0f;

            std::string objType = e->Attribute("type");
            std::string texID = e->Attribute("texture");

            e->Attribute("x", &x);
            e->Attribute("y", &y);
            e->Attribute("w", &width);
            e->Attribute("h", &height);

            e->Attribute("flip", &flip);
            e->Attribute("scX", &scX);
            e->Attribute("scY", &scY);

            e->Attribute("sratio", &sratio);
            e->Attribute("rot", &rot);

            Transform* tfr = new Transform(x, y, width, height, texID, (SDL_RendererFlip)flip, scX, scY, rot, sratio);
            ObjectPtr object = ObjectFactory::Instance()->CreateObject(objType, tfr);

            if (object != nullptr)
                target->push_back(object);
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return true;
}

Tileset Parser::ParseTileset(TiXmlElement* xmlTileset) {
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);
    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.Width);
    tileset.Height = tileset.TileCount / tileset.Width;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer* Parser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetsList tilesets, int tilesize, int rowcount, int colcount) {

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

    TileMatrix tilemap(rowcount, std::vector<int>(colcount, 0));
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


