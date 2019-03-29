#pragma once

#include "GameSocket.h"
#include "GameCommand.h"
#include "GameState.h"

class Game
{
public:
	Game(GameSocket gs);
	~Game();

	bool run();
	GameCommand calculateStep(GameState& state);

private:
	GameSocket m_socket;
	int m_playerId;

	int m_mapWidth;
	int m_mapHeight;
};

