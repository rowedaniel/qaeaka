#pragma once
#include "../../stdafx.h"

class Tile;

class Element
{
public:
	Element(Tile * tile);
	~Element();

	enum ID { Debug = 0, Hydrogen = 1 };

	ID get_id();

	float get_gas_amount();
	float get_gas_mass();
	float get_gas_density();

	float getLiquidAmount();
	float getSolidAmount();


	void distribute(std::vector<Tile*> neighbors);
	void apply_distribution();

private:

	// things which change
	float nGas;
	float nLiquid;
	float nSolid;

	float nGasChange;
	float nLiquidChange;
	float nSolidChange;

	// constant properties
	ID id = Debug;
	float molarMass = 1.0f;


	// other misc. stuff
	Tile * ownerTile;
};