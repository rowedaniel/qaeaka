#include "Element.h"
#include "Tile.h"

Element::Element(Tile * tile)
{
	ownerTile = tile;
}

Element::~Element()
{
}



Element::ID Element::get_id()
{
	return id;
}

float Element::get_gas_amount()
{
	return nGas;
}

float Element::get_gas_mass()
{
	return molarMass * get_gas_amount();
}

float Element::get_gas_density()
{
	// NOTE: possible error
	return get_gas_mass() / ownerTile->volume;
}



float Element::getLiquidAmount()
{
	return nLiquid;
}

float Element::getSolidAmount()
{
	return nSolid;
}


void Element::distribute(std::vector<Tile*> neighbors)
{

	// first, distribute gas (bc it's easiest)
	// TODO: decide whether or not to even distribute liquid.
	float densityChange = 0;
	for (Tile * neighbor : neighbors) {

		// for gasses, density is mols * molar mass / tile volume
		const float density = get_gas_density();
		float neighborDensity = 0;
		if (neighbor->has_element(id)) {
			neighborDensity = neighbor->get_element(id)->get_gas_density();
		}
		// for now, keep the diffusion coefficient constant.
		const float diffusionCoefficient = 0.1f;
		// the diffusion equation used here is d/(dt) density = sum for each neighbor[ (partial pressure difference) * diffusion coefficient of connection ]
		densityChange += (neighborDensity - density) * diffusionCoefficient;
	}
	nGasChange = densityChange * ownerTile->volume / molarMass;
}

void Element::apply_distribution()
{
	nGas += nGasChange;
}
