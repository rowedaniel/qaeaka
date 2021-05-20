#include "stdafx.h"

int main(int argc, char** argv[])
{
	std::cout << "Starting client." << std::endl;

	sf::IpAddress server("127.0.0.1");
	int port = 53000;

	sf::UdpSocket socket;

	// if(socket.send(msg, sizeof(msg), server, port) != Socket::Done) { /* error */ }

	return 0;
}