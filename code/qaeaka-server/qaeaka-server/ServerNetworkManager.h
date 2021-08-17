#pragma once
#include "../../qaeaka-common/NetworkManager.h"
#include "../../qaeaka-common/GameObjects/GridManager.h"

class ServerNetworkManager : public NetworkManager {
public:
	ServerNetworkManager(GridManager * GM);


	void send_packet(Request request, sf::IpAddress address, int port);
private:
	void handle_request(Request request, sf::IpAddress senderAddress, int senderPort, sf::Packet & incomingPacket);
	void send_ClientJoinGame(sf::Packet & outgoingPacket);

	// links to other things
	GridManager * gridManager;
};