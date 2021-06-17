#include "NetworkManager.h"
void NetworkManager::send_packet(Request request)
{
}

void NetworkManager::receive_packet()
{
	sf::Packet incomingPacket;
	auto info = get_request(incomingPacket);
	Request request = std::get<0>(info);
	sf::IpAddress senderAddress = std::get<1>(info);
	int senderPort = std::get<2>(info);
	handle_request(request, senderAddress, senderPort, incomingPacket);
}




std::tuple<NetworkManager::Request, sf::IpAddress, int> NetworkManager::get_request(sf::Packet & incomingPacket)
{
	sf::IpAddress senderAddress;
	unsigned short senderPort;
	socket.receive(incomingPacket, senderAddress, senderPort);
	std::cout << "Receiving packet from: " << senderAddress << ", port: " << senderPort << ", Packet size: " << incomingPacket.getDataSize() << std::endl;

	sf::Uint16 intResponseBuffer; // not sure if buffer is the right word here
	Request request;
	if (incomingPacket >> intResponseBuffer) {
		std::cout << "Request type id is: " << intResponseBuffer << std::endl;
		request = static_cast<Request>(intResponseBuffer);
		return std::make_tuple(request, senderAddress, senderPort);
	}
	return std::make_tuple(Request::Failure, senderAddress, senderPort);
}

void NetworkManager::handle_request(Request request, sf::IpAddress senderAddress, int senderPort, sf::Packet & incomingPacket)
{
	std::cout << "In parent respondToRequest." << std::endl;
	switch (request) {
	case Failure:
	{
		// error receiving packet
		std::cout << "Error receiving packet" << std::endl;
		break;
	}
	}
}
