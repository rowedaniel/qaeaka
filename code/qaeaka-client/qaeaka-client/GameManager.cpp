#include "GameManager.h"




GameManager::GameManager() : networkManager( new ClientNetworkManager(this) ), graphicsManager( new GraphicsManager(this) )
{
}

void GameManager::run_until_finished()
{

	graphicsManager->create_window();



	networkManager->send_packet(ClientNetworkManager::ClientJoinGame);
	while (tiles.size() == 0) {
		networkManager->receive_packet();
	}

	



	// launch rendering thread
	sf::Thread thread(&GameManager::renderingThread, this);
	thread.launch();

	// logic thread stays part of this thread
	logicThread();


}

void GameManager::renderingThread()
{
	graphicsManager->activateWindow();

	// main render loop
	renderingClock.restart();
	while (graphicsManager->isOpen()) {
		sf::Time elapsedTime = renderingClock.getElapsedTime();
		// TODO: make this timing better
		// the framerate is hardcoded
		// don't bother rendering if no time has passed
		if (elapsedTime.asMilliseconds() < 16) { continue; }

		graphicsManager->draw(renderingClock.getElapsedTime());
		renderingClock.restart();
	}
}

void GameManager::logicThread()
{
	while (graphicsManager->isOpen()) {
		logic();
		events();
	}
}


void GameManager::logic()
{
}

void GameManager::events()
{
	sf::Event event;
	while (graphicsManager->pollEvent(event)) {
		switch (event.type) {
		case(sf::Event::Closed):
		{
			graphicsManager->close();
			break;
		}
		case(sf::Event::Resized):
		{
			graphicsManager->update_window_size(event.size.width, event.size.height);
			break;
		}
		case(sf::Event::KeyPressed):
		{
			switch (event.key.code) {
			case(sf::Keyboard::Q):
			{
				// rotate screen to the left
				graphicsManager->rotateBy(60);
				break;
			}
			case(sf::Keyboard::E):
			{
				// rotate screen to the right
				graphicsManager->rotateBy(-60);
				break;
			}
			}
			break;
		}
		}
	}
}

/*
// C++ quirk: static member vars have to be instantiated here
int GameManager::windowWidth = 800;
int GameManager::windowHeight = 800;
sf::RenderWindow GameManager::window;
sf::RenderTexture GameManager::postProcessingTexture;
sf::Color GameManager::defaultColor = sf::Color::Black;

ClientNetworkManager GameManager::networkManager;
std::vector<VisualTile> GameManager::tiles;
*/