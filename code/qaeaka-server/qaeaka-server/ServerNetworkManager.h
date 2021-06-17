#pragma once
#include "../../qaeaka-common/NetworkManager.h"

class ServerNetworkManager : public NetworkManager {
public:
	ServerNetworkManager();


	void send_packet(Request request, sf::IpAddress address, int port);
private:
	int serverPort;

	void handle_request(Request request, sf::IpAddress senderAddress, int senderPort, sf::Packet & incomingPacket);
	void send_ClientJoinGame(sf::Packet & outgoingPacket);
};