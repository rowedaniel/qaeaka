#include "stdafx.h"

int main(int argc, char** argv[])
{
	std::cout << "Starting server." << std::endl;

	int port = 53000;

	// Create a socket to receive a message from anyone
	sf::UdpSocket socket;

	// Listen to messages on port 53000
	if (socket.bind(53000) != sf::Socket::Done)
	{
		std::cout << "Error starting server." << std::endl;
		return;
	}


	/*
	char in[size]
	std::size_t received;
	sf::IpAddress
	unsigned short senderPort
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done) 
	{ 
		// error 
	}
	*/



	return 0;
}