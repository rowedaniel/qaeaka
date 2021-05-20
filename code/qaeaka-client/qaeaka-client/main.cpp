#include "stdafx.h"

int main(int argc, char** argv[])
{
	std::cout << "Starting client." << std::endl;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
	if (status != sf::Socket::Done)
	{
		// error...
	}

	return 0;
}