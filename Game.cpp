#include "Game.h"

#include <string>
#include <iostream>

using namespace std;

Game::Game(GameSocket gs) : m_socket(gs)
{
}

Game::~Game()
{
}

bool Game::run() {
	string buf;

	// wait for newgame
	while (buf.substr(0, 7) != "newgame") {
		if (!m_socket.receive(buf)) {
			return false;
		}
	}

	std::cout << "New game starting..." << std::endl;

	if (!m_socket.sendControl(1, "getPlayerId")) {
		return false;
	}

	if (!m_socket.receive(buf)) {
		return false;
	}

	// get player id
	m_playerId = GameSocket::get4or5ByteInteger(buf);
	std::cout << "Player ID: " << m_playerId << std::endl;

	if (!m_socket.sendControl(1, "getMapWidth")) {
		return false;
	}

	if (!m_socket.receive(buf)) {
		return false;
	}
	m_mapWidth = GameSocket::get4or5ByteInteger(buf); // this does not make sense at all, but can't make it work any other way

	if (!m_socket.sendControl(1, "getMapHeight")) {
		return false;
	}

	if (!m_socket.receive(buf)) {
		return false;
	}

	m_mapHeight = GameSocket::get4or5ByteInteger(buf);
	std::cout << "Map size: " << m_mapWidth << " x " << m_mapHeight << std::endl;

	// wait for game state
	if (!m_socket.sendControl(1, "getGameState")) {
		return false;
	}

	if (!m_socket.receive(buf)) {
		return false;
	}

	if (buf.substr(0, 7) == "endgame") {
		return false;
	}

	GameState gs;
	gs.parse(buf);

#if DEBUG > 0
	gs.print();
#endif

	while (true) {
		GameCommand cmd = this->calculateStep(gs);
		if (cmd.m_command != GameCommand::CommandType::NOTHING) {
			string ser = cmd.serialize();
			m_socket.send(ser);
			m_socket.receive(buf); //waiting for ok

			if (buf.substr(0, 7) == "endgame") {
				return true;
			} else if (buf != "ok") {
				std::cout << "Error: " << buf << std::endl;
			}
		}

		if (!m_socket.sendControl(1, "getGameState")) {
			return false;
		}

		if (!m_socket.receive(buf)) {
			return false;
		}

		if (buf.substr(0, 7) == "endgame") {
			return true;
		}
		else {
			gs.parse(buf);
#if DEBUG > 0
			gs.print();
#endif
		}
	}
}