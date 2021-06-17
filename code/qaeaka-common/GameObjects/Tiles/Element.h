#pragma once
#include "../../stdafx.h"

class Tile;

class Element
{
public:
	Element();
	~Element();

	float getGasAmount();
	float getLiquidAmount();
	float getSolidAmount();

	void distribute(std::vector<Tile*> neighbors);

private:
	float nGas;
	float nLiquid;
	float nSolid;
};