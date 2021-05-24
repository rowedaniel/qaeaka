#pragma once

#include "../../qaeaka-common/GameObjects/GameObject.h"

class VisualGameObject : public GameObject
{
public:
	void draw(sf::RenderTexture &texture);
};