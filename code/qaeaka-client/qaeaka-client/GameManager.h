#pragma once
#include "stdafx.h"
#include "ClientNetworkManager.h"
#include "GameObjects/Tile/VisualTile.h"
#include "GraphicsManager.h"

class GameManager
{
public:
	GameManager();
	
	void run_until_finished();

	std::vector<VisualTile*> tiles;

	void renderingThread();
	void logicThread();

private:

	ClientNetworkManager * networkManager;

	GraphicsManager * graphicsManager;

	void logic();
	void events();

	sf::Clock renderingClock;
	sf::Clock logicClock;

	/**/
};