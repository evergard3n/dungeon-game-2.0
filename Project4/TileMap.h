#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "TileLayer.h"

class TileMap {

public:

    TileMap() {}

    void Render() {
        for (auto layer : m_MapLayers)
            layer->Render();
    }

    void Update() {
        for (auto layer : m_MapLayers)
            layer->Update();
    }

    void Clean() {
        for (auto layer : m_MapLayers)
            delete layer;
        m_MapLayers.clear();
    }

    std::vector<TileLayer*> GetLayers() {
        return m_MapLayers;
    }

private:
    friend class Parser;
    std::vector<TileLayer*> m_MapLayers;
};

#endif // TILEMAP_H
