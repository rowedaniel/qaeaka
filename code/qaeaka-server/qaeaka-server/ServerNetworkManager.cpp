#include "ServerNetworkManager.h"

ServerNetworkManager::ServerNetworkManager()
{
	// Listen to messages on port 53000
	if (socket.bind(serverPort) != sf::Socket::Done)
	{
		std::cout << "Error starting server." << std::endl;
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
		//add_client(senderAddress, senderPort)
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
	return;
}
