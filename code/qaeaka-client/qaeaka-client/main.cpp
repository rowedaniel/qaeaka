#include "stdafx.h"
#include "GameManager.h"

int main(int argc, char** argv[])
{
	std::cout << "Starting client." << std::endl;
	GameManager gameManager;
	gameManager.run_until_finished();


	return 0;
}