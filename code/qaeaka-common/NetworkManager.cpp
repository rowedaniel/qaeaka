
#include "NetworkManager.h"
NetworkManager::NetworkManager()
{
	socket.setBlocking(false);
}
NetworkManager::~NetworkManager()
{
}
void NetworkManager::send_packet(Request request)
{
}

void NetworkManager::receive_packet()
{
	sf::Packet incomingPacket;
	Request request = Request::NotFinished;
	// handle all queued requests
	while (request != Request::Failure) {

		// see if request succeeded.
		auto info = get_request(incomingPacket);
		Request request = std::get<0>(info);
		if (request == Request::Failure) { break; }

		// request was successful, so handle it.
		sf::IpAddress senderAddress = std::get<1>(info);
		int senderPort = std::get<2>(info);
		std::cout << "Handling request #" << request << "From: ip: " << senderAddress << ", port: " << senderPort << ", Packet size: " << incomingPacket.getDataSize() << std::endl;
		handle_request(request, senderAddress, senderPort, incomingPacket);
	}
}




std::tuple<NetworkManager::Request, sf::IpAddress, int> NetworkManager::get_request(sf::Packet & incomingPacket)
{
	sf::IpAddress senderAddress;
	unsigned short senderPort = 0;
	if (socket.receive(incomingPacket, senderAddress, senderPort) == sf::Socket::NotReady) {
		// in non-blocking mode, socket wasn't ready.
		return std::make_tuple(Request::Failure, senderAddress, senderPort);
	}

	sf::Uint16 intResponseBuffer; // not sure if buffer is the right word here
	Request request;
	if (incomingPacket >> intResponseBuffer) {
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
		std::cout << "Error receiving packet. Request was: " << request << std::endl;
		break;
	}
	}
}
