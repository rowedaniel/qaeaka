#pragma once
#include "stdafx.h"

class NetworkManager {
public:
	enum Request { Failure = (sf::Uint16)0, ClientJoinGame = (sf::Uint16)1 };

	virtual void send_packet(Request request);
	virtual void receive_packet();

protected:

	const int serverPort = 53000;

	sf::UdpSocket socket;


	// recievePacket() should receive a message from the client/server and return which request it was. incomingPacket is both an input and an output.
	virtual std::tuple<Request, sf::IpAddress, int> get_request(sf::Packet & incomingPacket);
	virtual void handle_request(Request request, sf::IpAddress senderAddress, int senderPort, sf::Packet & incomingPacket);
};