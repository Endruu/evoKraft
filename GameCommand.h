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

    static GameCommand nothing() { return GameCommand{ GameCommand::NOTHING }; };
    static GameCommand stopAcceleration() { return GameCommand{ GameCommand::STOPACCELERATION }; };
    static GameCommand accelerate() { return GameCommand{ GameCommand::ACCELERATE }; };
    static GameCommand decelerate() { return GameCommand{ GameCommand::DECELERATE }; };
    static GameCommand rotateLeft(float);
    static GameCommand rotateRight(float);
    static GameCommand stopRotation() { return GameCommand{ GameCommand::STOPROTATION }; };
    static GameCommand fire() { return GameCommand{ GameCommand::FIRE }; };

	CommandType m_command;
	float m_targetRotation;
};

