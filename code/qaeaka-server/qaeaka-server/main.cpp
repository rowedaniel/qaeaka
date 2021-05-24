#include "stdafx.h"
#include "../../qaeaka-common/GameObjects/GridManager.h"

int main(int argc, char** argv[])
{
	std::cout << "Starting server." << std::endl;

	GridManager gridmanager = GridManager();


	

	const int port = 53000;

	// Create a socket to receive a message from anyone
	sf::UdpSocket socket;

	// Listen to messages on port 53000
	if (socket.bind(53000) != sf::Socket::Done)
	{
		std::cout << "Error starting server." << std::endl;
		return 0;
	}

	sf::Packet incomingPacket;
	sf::IpAddress senderAddress;
	unsigned short senderPort;

	enum ClientRequest { JoinGame = sf::Uint16(1) }; 
	enum ServerRequest {  };
	ClientRequest clientRequest;
	sf::Uint16 intClientRequests;
	
	while (true) {
		socket.receive(incomingPacket, senderAddress, senderPort);
		if (incomingPacket >> intClientRequests) {
			clientRequest = static_cast<ClientRequest>(intClientRequests);
			std::cout << "Packet received: " << clientRequest << std::endl;
			switch (clientRequest)
			{
			case ClientRequest::JoinGame:
			{
				sf::Packet outgoingPacket;
				outgoingPacket << clientRequest;
				sf::Uint16 size = gridmanager.tiles.size();
				outgoingPacket << size;

				std::cout << "Sending: " << size << " tiles:" << std::endl;

				for (auto it : gridmanager.tiles) {
					Tile::GridPos pos = it->getGridPos();
					sf::Int16 x = pos.x;
					sf::Int16 y = pos.y;
					std::cout << "x: " << x << " y: " << y << std::endl;;
					outgoingPacket << x << y;
				}
				socket.send(outgoingPacket, senderAddress, senderPort);
				break;
			}
			}
		}
		else {
			// error receiving packet
			std::cout << "Error receiving packet from: " << senderAddress << ", port: " << senderPort << std::endl;
		}

	}
	/*
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
	
	*/

	return 0;
}