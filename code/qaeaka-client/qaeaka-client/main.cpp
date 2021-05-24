#include "stdafx.h"
#include "GameManager.h"

int main(int argc, char** argv[])
{
	std::cout << "Starting client." << std::endl;

	GameManager::run_until_finished();


	/*
	sf::IpAddress server("131.191.92.153");
	int port = 53000;

	sf::UdpSocket socket;


	std::string msg_text;
	char msg[128];

	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;

	while (msg_text != "q") {
		memset(msg, '\0', 128);
		std::getline(std::cin, msg_text);
		msg_text.copy(msg, msg_text.size() + 1);
		if (socket.send(msg, sizeof(msg), server, port) != sf::Socket::Done) { 
			std::cout << "Error sending message." << std::endl;
			return 0;
		}


		if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		{
			std::cout << "Error recieving message." << std::endl;
			return 0;
		}
		std::cout << "Message recieved from " << sender << ": \"" << in << "\"" << std::endl;
	}
	*/

	return 0;
}