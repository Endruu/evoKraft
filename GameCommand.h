#pragma once

#include <string>

class GameCommand
{
public:

    enum CommandType
    {
        NOTHING = 0,
        STOPACCELERATION = 1,
        ACCELERATE = 2,
        DECELERATE = 3,
        ROTATELEFT = 4,
        ROTATERIGHT = 5,
        STOPROTATION = 6,
        FIRE = 7
    };

	GameCommand();
    explicit GameCommand(CommandType command, float targetRotation = 0.0f);
	~GameCommand();

	std::string serialize();

	CommandType m_command;
	float m_targetRotation;
};

