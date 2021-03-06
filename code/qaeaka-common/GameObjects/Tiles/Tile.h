#pragma once
#include "../GameObject.h"
#include "Element.h"

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

	bool has_element(Element::ID id);
	Element* get_element(Element::ID id);

	std::list<Element*> elements;
	std::vector<Tile*> neighbors;

	const float volume = 100.0f; // in Liters

protected:
	const float edgeSize = 128.0f;
	const float width = edgeSize * 2.0f;
	const float halfHeight = 111.0f; //edgeSize * 0.875; //0.8660254f;

	GridPos gridPos;
	/*
	Lightlevel level;
	std::vector<Fluid> fluids;
	std::vector<Gas> gasses;
	int temperature;
	int radiation;
	// maybe make nonmoving entities owned by tiles
	*/

	void update_pos(int x, int y);

};