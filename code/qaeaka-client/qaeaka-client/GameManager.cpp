#include "GameManager.h"

void GameManager::run_until_finished()
{

	window.create(sf::VideoMode(windowWidth, windowHeight, 32), "Qaeaka");
	// setup post processing texture
	if (!postProcessingTexture.create(windowWidth, windowHeight)) {
		// error
	}

	// deactivate OpenGl context for the main thread (whatever that means)
	window.setActive(false);

	networkManager.send_packet(ClientNetworkManager::ClientJoinGame);
	networkManager.receive_packet();

	


	// launch rendering thread
	sf::Thread thread(&GameManager::renderingThread);
	thread.launch();

	// logic thread stays part of this thread
	logicThread();


}

void GameManager::renderingThread()
{
	// activate OpenGl context for only this thread (I think)
	window.setActive(true);

	// main render loop
	while (window.isOpen()) {
		// TODO: add timing to this
		draw();
		window.display();
	}
}

void GameManager::logicThread()
{
	while (window.isOpen()) {
		logic();
		events();
	}
}

void GameManager::draw()
{
	// clear the screen
	postProcessingTexture.clear(defaultColor);

	// draw sprites
	for (auto it = tiles.begin(); it != tiles.end(); ++it) {
		it->draw(postProcessingTexture);
	}

	// update freshly drawn sprites
	postProcessingTexture.display();


	// push the post processing texture to the actual screen
	const sf::Texture & texture = postProcessingTexture.getTexture();
	sf::Sprite sprite(texture);
	window.draw(sprite);
}

void GameManager::logic()
{
}

void GameManager::events()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}


// C++ quirk: static member vars have to be instantiated here
int GameManager::windowWidth = 800;
int GameManager::windowHeight = 800;
sf::RenderWindow GameManager::window;
sf::RenderTexture GameManager::postProcessingTexture;
sf::Color GameManager::defaultColor = sf::Color::Black;

ClientNetworkManager GameManager::networkManager;
std::vector<VisualTile> GameManager::tiles;