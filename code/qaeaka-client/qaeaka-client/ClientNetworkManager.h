#pragma once
#include "../../qaeaka-common/NetworkManager.h"

class GameManager;

class ClientNetworkManager : public NetworkManager 
{
public:

	//ClientNetworkManager();
	ClientNetworkManager(GameManager * GM);
	
	void send_packet(Request request);
private:
	sf::IpAddress serverAddress;

	void handle_request(Request request, sf::IpAddress senderAddress, int senderPort, sf::Packet & incomingPacket);

	void send_ClientJoinGame(sf::Packet & outgoingPacket);

	GameManager * gameManager;
	
};