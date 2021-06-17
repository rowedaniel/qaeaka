#include "Element.h"
#include "Tile.h"

Element::Element()
{
	nGas = 100;
}

Element::~Element()
{
}

float Element::getGasAmount()
{
	return 0.0f;
}

float Element::getLiquidAmount()
{
	return 0.0f;
}

float Element::getSolidAmount()
{
	return 0.0f;
}

void Element::distribute(std::vector<Tile*> neighbors)
{
	return;
}
