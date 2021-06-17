#pragma once
#include "stdafx.h"
#include "ClientNetworkManager.h"
#include "GameObjects/Tile/VisualTile.h"

class GameManager
{
public:
	static void run_until_finished();

	static std::vector<VisualTile> tiles;

private:
	static int windowWidth;
	static int windowHeight;

	static sf::RenderWindow window;
	static sf::RenderTexture postProcessingTexture;

	static sf::Color defaultColor;

	static ClientNetworkManager networkManager;

	static void renderingThread();
	static void logicThread();

	static void logic();
	static void events();
	static void draw();

};