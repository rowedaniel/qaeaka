#pragma once
#include "../../qaeaka-common/NetworkManager.h"

class ClientNetworkManager : public NetworkManager {
public:
	ClientNetworkManager();

	void send_packet(Request request);
private:
	sf::IpAddress serverAddress;

	void handle_request(Request request, sf::IpAddress senderAddress, int senderPort, sf::Packet & incomingPacket);

	void send_ClientJoinGame(sf::Packet & outgoingPacket);
};