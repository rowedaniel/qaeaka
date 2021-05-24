#pragma once
#include "../../qaeaka-common/GameObjects/Tiles/Tile.h"

class VisualTile : public Tile {
public:
	VisualTile();
	VisualTile(std::string imgfile, int x, int y);
	~VisualTile();

	void draw(sf::RenderTexture & target);
	void draw();

private:
	sf::Texture texture;
	sf::Sprite sprite;
	
};