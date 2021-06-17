#include "ClientNetworkManager.h"
#include "GameManager.h"

ClientNetworkManager::ClientNetworkManager()
{
	do
	{
		std::cout << "Type the address or name of the server to connect to: ";
		std::cin >> serverAddress;
	} while (serverAddress == sf::IpAddress::None);
	std::cout << "Connecting to: " << serverAddress << std::endl;
}

void ClientNetworkManager::send_packet(Request request)
{
	sf::Packet packet;
	packet << (sf::Uint16)request;

	std::cout << "Sending packet of type: " << request << std::endl;

	switch (request)
	{
	case NetworkManager::ClientJoinGame:
		send_ClientJoinGame(packet);
		break;
	default:
		// error
		std::cout << "Error sending packet to " << serverAddress << ", port: " << serverPort << std::endl;
		break;
	}

	socket.send(packet, serverAddress, serverPort);
}



void ClientNetworkManager::handle_request(Request request, sf::IpAddress senderAddress, int senderPort, sf::Packet & incomingPacket)
{
	std::cout << "In child respondToRequest, packet size is: " << incomingPacket.getDataSize() << std::endl;
	switch (request) {
	case Request::ClientJoinGame:
	{
		sf::Uint16 numberOfTiles;
		incomingPacket >> numberOfTiles;
		std::cout << "Building " << numberOfTiles << " tiles." << std::endl;

		
		GameManager::tiles.reserve(numberOfTiles);
		for (int i = 0; i < numberOfTiles; ++i) {
			sf::Uint16 x;
			sf::Uint16 y;
			incomingPacket >> x;
			incomingPacket >> y;
			std::cout << "Creating new tile at x=" << x << ", y=" << y << std::endl;
			GameManager::tiles.emplace_back("../../../devtile.png", x, y);
		}
		break;
	}
	default:
	{
		NetworkManager::handle_request(request, senderAddress, senderPort, incomingPacket);
		break;
	}
	}
}

void ClientNetworkManager::send_ClientJoinGame(sf::Packet & outgoingPacket)
{
	return;
}
