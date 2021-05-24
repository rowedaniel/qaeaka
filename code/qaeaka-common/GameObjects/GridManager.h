#pragma once

#include "Tiles/Tile.h"

class GridManager {//: public GameObject {
public:
	GridManager();
	~GridManager();

	std::list<Tile*> tiles;
	
};