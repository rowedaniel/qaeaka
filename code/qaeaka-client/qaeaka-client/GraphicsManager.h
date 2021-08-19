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
	void draw(sf::Time elapsedTime);
	void close();

	bool isOpen();
	bool pollEvent(sf::Event & event);

	void rotateBy(float angle);



private:



	int windowWidth = 800;
	int windowHeight = 800;

	float rotation = 0.0f;
	float targetRotation = 0.0f;
	const float cameraRotateSpeed = 360.0f; // degrees / second

	sf::RenderWindow window;
	sf::RenderTexture postProcessingTexture;

	sf::Color defaultColor;

	sf::View view;

	GameManager * gameManager;

	void updateAngle(sf::Time elapsedTime);
};