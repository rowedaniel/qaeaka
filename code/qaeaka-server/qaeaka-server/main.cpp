#include "stdafx.h"
#include "../../qaeaka-common/GameObjects/GridManager.h"
#include "ServerNetworkManager.h"

int main(int argc, char** argv[])
{

	GridManager gridmanager = GridManager();

	std::cout << "Starting server." << std::endl;
	ServerNetworkManager networkManager(&gridmanager);

	while (true) {
		networkManager.receive_packet();
	}

	return 0;
}