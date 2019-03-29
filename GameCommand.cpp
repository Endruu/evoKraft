#include "GameCommand.h"

GameCommand::GameCommand()
{
	m_targetRotation = 0;
	m_command = CommandType::NOTHING;
}

GameCommand::GameCommand(CommandType command, float targetRotation) :
    m_command(command), m_targetRotation(targetRotation)
{
}

GameCommand::~GameCommand()
{
}

std::string GameCommand::serialize() {
	std::string s = "";
	s += '\2';
	s += (unsigned char)(m_command % 256);
	double tr = (double)m_targetRotation + 16777216.0;
	int ipart = (int)tr;
	int fpart = (int)((tr - ipart) * 16777216);
	for (int i = 0; i < 4; i++) {
		s += (unsigned char)(ipart % 256);
		ipart /= 256;
	}
	for (int i = 0; i < 3; i++) {
		s += (unsigned char)(fpart % 256);
		fpart /= 256;
	}
	return s;
}