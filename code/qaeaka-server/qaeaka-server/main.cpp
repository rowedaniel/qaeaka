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
		return 0;
	}


	
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;

	while (true) {
		if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		{
			std::cout << "Error recieving message." << std::endl;
			return 0;
		}
		std::cout << "Message recieved from " << sender << ": \"" << in << "\"" << std::endl;




		if (socket.send(in, sizeof(in), sender, senderPort) != sf::Socket::Done) {
			std::cout << "Error sending message." << std::endl;
			return 0;
		}
	}



	return 0;
}