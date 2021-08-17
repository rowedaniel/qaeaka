#include "ServerNetworkManager.h"

ServerNetworkManager::ServerNetworkManager(GridManager * GM) : NetworkManager()
{
	// set all the important links
	gridManager = GM;

	// Listen to messages on port 53000
	if (socket.bind(serverPort) != sf::Socket::Done)
	{
		std::cout << "Error starting server." << std::endl;
		return;
	}
}

void ServerNetworkManager::send_packet(Request request, sf::IpAddress address, int port)
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
		std::cout << "Error sending packet to " << address << ", port: " << port << std::endl;
		break;
	}

	socket.send(packet, address, port);
}


void ServerNetworkManager::handle_request(Request request, sf::IpAddress senderAddress, int senderPort, sf::Packet & incomingPacket)
{

	std::cout << "In child respondToRequest, packet size is: " << incomingPacket.getDataSize() << std::endl;
	switch (request) {
	case Request::ClientJoinGame:
	{
		std::cout << "Recieved ClientJoinGame request!" << std::endl;
		send_packet(Request::ClientJoinGame, senderAddress, senderPort);
	}
	default:
	{
		NetworkManager::handle_request(request, senderAddress, senderPort, incomingPacket);
		break;
	}
	}
}


void ServerNetworkManager::send_ClientJoinGame(sf::Packet & outgoingPacket)
{
	sf::Uint16 size = (sf::Uint16)gridManager->tiles.size();
	outgoingPacket << size;

	std::cout << "Sending: " << size << " tiles:" << std::endl;

	for (auto it : gridManager->tiles) {
		Tile::GridPos pos = it->getGridPos();
		sf::Uint16 x = pos.x;
		sf::Uint16 y = pos.y;
		outgoingPacket << x;
		outgoingPacket << y;
	}
}
