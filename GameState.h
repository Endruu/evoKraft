#pragma once

#include "GameObject.h"

#include <string>
#include <vector>

class GameState
{
public:
	std::vector<GameObject> players;
	std::vector<GameObject> turrets;
	std::vector<GameObject> obstacles;
	std::vector<GameObject> lasers;

	GameState();
	~GameState();

	void parse(std::string msg);
	void print();
};

