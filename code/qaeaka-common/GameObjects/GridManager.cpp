#include "GridManager.h"

GridManager::GridManager()
{
	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 4; ++y)
		{
			tiles.push_back(new Tile(x,y));
		}
	}

	for (auto it : tiles) {
		Tile::GridPos pos = it->getGridPos();
		std::cout << "Created new tile with x: " << pos.x << ", y: " << pos.y << std::endl;
	}
}

GridManager::~GridManager()
{
}
