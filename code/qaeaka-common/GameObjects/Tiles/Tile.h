#pragma once
#include "../GameObject.h"

class Tile : public GameObject
{
public:
	Tile();
	Tile(int x, int y);
	~Tile();

	struct GridPos {
		int x;
		int y;
	};
	GridPos getGridPos();

private:
	const float edgeSize = 64.0f;
	const float width = edgeSize * 2.0f;
	const float halfHeight = edgeSize * 0.86603f;

	GridPos gridPos;
	/*
	Lightlevel level;
	std::vector<Fluid> fluids;
	// maybe make nonmoving entities owned by tiles
	*/

	void updatePos(int x, int y);

};