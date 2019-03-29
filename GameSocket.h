#pragma once

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>

class GameSocket
{
public:
	GameSocket();
	~GameSocket();

	bool connect(std::string& host, std::string& port, std::string& instance, std::string& name);
	bool sendControl(uint8_t type, std::string msg);
	bool send(std::string msg);
	bool receive(std::string& str);
	void disconnect();

	static int getInteger(std::string str);
	static int get4or5ByteInteger(std::string str);

private:
	int internalRecv(std::string& buf);

	SOCKET m_socket;
};

