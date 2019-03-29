#ifndef UTEST

#include "GameSocket.h"
#include "Game.h"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	GameSocket socket;

	std::string host = "163.242.138.233";
	std::string port = "8124";

	std::string teamName = "evoKulacs";
	std::string instanceName = "iowaspace";

	if (argc > 1) {
		instanceName = argv[1];
	}

    if (!socket.connect(host, port, instanceName, teamName))
    {
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.ignore();
        return 1;
    }

    Game game(socket);
    while (game.run())
    {
        std::cout << "Game finished." << std::endl << std::endl;
    };
    socket.disconnect();

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore();

    return 0;
}
#else

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#endif
