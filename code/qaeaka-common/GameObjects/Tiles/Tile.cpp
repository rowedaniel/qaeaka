#include "Tile.h"

Tile::Tile()
{
	Tile(0, 0);
}

Tile::Tile(int x, int y)
{
	update_pos(x, y);
}

Tile::~Tile()
{
}

Tile::GridPos Tile::getGridPos()
{
	// TODO: test to see if this is a reference or not (hopefully not)
	return gridPos;
}

bool Tile::has_element(Element::ID id)
{
	for (auto it : elements) {
		if (it->get_id() == id) {
			return true;
		}
	}
	return false;
}

Element * Tile::get_element(Element::ID id)
{
	for (auto it : elements) {
		if (it->get_id() == id) {
			return it;
		}
	}
	// error: element not found
	return *elements.begin();
}

void Tile::update_pos(int x, int y)
{
	gridPos.x = x;
	gridPos.y = y;
	setPosition(floor(x * edgeSize * 1.5f),
				floor(y * halfHeight * 2.0f  +  (x%2)*halfHeight));
}
