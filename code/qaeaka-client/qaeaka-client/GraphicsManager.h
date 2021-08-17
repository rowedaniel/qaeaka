#pragma once
#include "stdafx.h"

class GameManager;

class GraphicsManager
{
public:
	GraphicsManager(GameManager * GM);
	~GraphicsManager();

	void update_window_size(float width, float height);
	void create_window();
	void activateWindow();
	void draw();
	void close();

	bool isOpen();
	bool pollEvent(sf::Event & event);



private:



	int windowWidth = 800;
	int windowHeight = 800;

	sf::RenderWindow window;
	sf::RenderTexture postProcessingTexture;

	sf::Color defaultColor;

	sf::View view;

	GameManager * gameManager;
};