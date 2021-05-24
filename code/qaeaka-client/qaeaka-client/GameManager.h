#pragma once
#include "stdafx.h"
#include "GameObjects/Tile/VisualTile.h"

class GameManager
{
public:
	static void run_until_finished();

private:
	static int windowWidth;
	static int windowHeight;

	static sf::RenderWindow window;
	static sf::RenderTexture postProcessingTexture;

	static sf::Color defaultColor;

	static std::vector<VisualTile> tiles;

	static void renderingThread();
	static void logicThread();

	static void logic();
	static void events();
	static void draw();

};