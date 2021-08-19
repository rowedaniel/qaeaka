#include "GraphicsManager.h"
#include "GameManager.h"



GraphicsManager::GraphicsManager(GameManager * GM)
{
	gameManager = GM;

	view.reset(sf::FloatRect(50.0f, 50.0f, (float)windowWidth, (float)windowHeight));
	view.setRotation(0.0f);
}

GraphicsManager::~GraphicsManager()
{
}

void GraphicsManager::update_window_size(float width, float height)
{
	windowWidth = width;
	windowHeight = height;
	view.setSize(sf::Vector2f((float)windowWidth, (float)windowHeight));
}

void GraphicsManager::create_window()
{
	window.create( sf::VideoMode(windowWidth, windowHeight, 32), "Qaeaka");
	// setup post processing texture
	if (!postProcessingTexture.create(windowWidth, windowHeight)) {
		// error
	}

	// deactivate OpenGl context for the main thread (whatever that means)
	window.setActive(false);
	postProcessingTexture.setView(view);
}

void GraphicsManager::activateWindow()
{

	// activate OpenGl context for only this thread (I think)
	window.setActive(true);
}

bool GraphicsManager::isOpen()
{
	return window.isOpen();
}

bool GraphicsManager::pollEvent(sf::Event & event)
{
	return window.pollEvent(event);
}

void GraphicsManager::rotateBy(float angle)
{
	targetRotation += angle;
	std::cout << "rotating to: " << targetRotation << std::endl;
}




void GraphicsManager::updateAngle(sf::Time elapsedTime)
{
	const float rotateAmount = cameraRotateSpeed * elapsedTime.asSeconds();

	// if the angle is close to the target angle, just set it to the target
	if(std::abs(rotation - targetRotation) < rotateAmount){

		// make sure the target rotation is between 0 and 360 degrees
		while (targetRotation > 360.0f) { targetRotation -= 360.0f;  }
		while (targetRotation < 0.0f)   { targetRotation += 360.0f; }

		rotation = targetRotation;

	}
	// if the angle is far from the target angle, move it in that direction
	else if (rotation < targetRotation) {
		rotation += rotateAmount;
	}
	else {
		rotation -= rotateAmount;
	}


	view.setRotation(rotation);
	postProcessingTexture.setView(view);
}



void GraphicsManager::draw(sf::Time elapsedTime)
{
	// updated camera angle and stuff
	updateAngle(elapsedTime);

	// clear the screen
	postProcessingTexture.clear(defaultColor);

	// draw sprites
	for (auto it:gameManager->tiles) {
		it->draw(postProcessingTexture);
	}
	  
	// update freshly drawn sprites
	postProcessingTexture.display();


	// push the post processing texture to the actual screen
	const sf::Texture & texture = postProcessingTexture.getTexture();
	sf::Sprite sprite(texture);
	//sprite.setRotation(120.0f);
	//sprite.setScale(1.0f, 0.5f);
	window.draw(sprite);
	window.display();
}

void GraphicsManager::close()
{
	window.close();
}
