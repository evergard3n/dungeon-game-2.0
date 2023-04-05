#pragma once
#include "layer.h"
#include <vector>
using namespace std;
class gameMap
{
public:
	gameMap(){}
	void render() {
		for (unsigned int i = 0; i < m_mapLayers.size(); i++) m_mapLayers[i]->render();
	}void update() {
		for (unsigned int i = 0; i < m_mapLayers.size(); i++) m_mapLayers[i]->update();
	}
	vector<layer*> getMapLayers() {
		return m_mapLayers;
	}
private:
	friend class mapParser;
	vector<layer*> m_mapLayers;
	
};