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


	
	// load tiles from server
	
	// TODO: put this somewhere better
	sf::IpAddress serverAddress("131.191.92.153");
	int serverPort = 53000;

	sf::UdpSocket socket;

	sf::Packet incomingPacket;
	sf::IpAddress senderAddress;
	unsigned short senderPort;

	enum ClientRequest { JoinGame = sf::Uint16(1) };
	enum ServerRequest {  };
	ClientRequest serverResponse;
	int intServerResponse;

	// send signal to server that we started the game
	sf::Packet outgoingPacket;
	sf::Uint16 testJoinGame = 1;
	outgoingPacket << testJoinGame;//ClientRequest::JoinGame;
	socket.send(outgoingPacket, serverAddress, serverPort);
	socket.receive(incomingPacket, senderAddress, senderPort);
	if (incomingPacket >> intServerResponse) {
		serverResponse = static_cast<ClientRequest>(intServerResponse);
		std::cout << "Packet received: " << serverResponse << std::endl;
		switch (serverResponse) {
		case ClientRequest::JoinGame:
		{
			sf::Uint16 numberOfTiles;
			incomingPacket >> numberOfTiles;
			tiles.reserve(numberOfTiles);
			sf::Uint16 x, y;
			for (int i = 0; i < numberOfTiles; ++i) {
				incomingPacket >> x;
				incomingPacket >> y;
				std::cout << "Creating new tile at x=" << x << ", y=" << y << std::endl;
				tiles.emplace_back("devtile.png", x, y);
			}
			break;
		}
		}
	}
	else {
		// error receiving packet
		std::cout << "Error receiving packet from: " << senderAddress << ", port: " << senderPort << std::endl;
	}



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

std::vector<VisualTile> GameManager::tiles;