#include "VisualTile.h"

VisualTile::VisualTile(std::string imgfile, int x, int y) : Tile(x, y)
{
	// load texture
	if (!texture.loadFromFile(imgfile)) {
		// error
		std::cout << "Error loading from file: " << imgfile << std::endl;
	}
	texture.setSmooth(true);
	sprite = sf::Sprite(texture, sf::IntRect(0, 0, 128, 128));
	sprite.setPosition(Tile::getPosition());
}

VisualTile::~VisualTile()
{
}

void VisualTile::draw(sf::RenderTexture & target)
{
	target.draw(sprite);
}

void VisualTile::draw()
{
}
