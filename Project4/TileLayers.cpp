#include "TileLayers.h"
#include "TextureManager.h"
TileLayer::TileLayer(int tilesize, int colCount, int rowCount, tilemap tilemap, tilesetlist tilesets) : m_tileSize(tilesize), m_colCount(colCount), m_rowCount(rowCount), m_tilemap(tilemap), m_tilesets(tilesets)
{
	for (unsigned int i = 0; i < m_tilesets.size(); i++) {
		TextureManager::GetInstance()->Load(m_tilesets[i].name,"textures/map/"+m_tilesets[i].source);
	}
	
	
}

void TileLayer::render()
{
	for (unsigned int i = 0; i < m_rowCount; i++) {
		for (unsigned int j = 0; j < m_colCount; j++) {
			int tileID = m_tilemap[i][j];
			int temp = tileID;
			if (tileID == 0) continue;
			else {
				int index = 0;
				if (m_tilesets.size() > 1) {
					for (unsigned int k = 1; k < m_tilesets.size(); k++) {
						if (tileID >= m_tilesets[k].firstID && tileID < m_tilesets[k].lastID) {
							tileID = tileID + m_tilesets[k].tileCount - m_tilesets[k].lastID;
							index = k;
							break;
						}
					}
				}
				Tileset ts = m_tilesets[index];
				int tileRow = tileID / ts.numCols;
				int tileCol = tileID - tileRow * ts.numCols - 1;
				//check if this is the last col
				if (tileID % ts.numCols == 0) {
					tileRow--;
					tileCol = ts.numCols - 1;
				}
				TextureManager::GetInstance()->DrawTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
			}
			
		}
	}
}

void TileLayer::update()
{
}
