#define WIN32_LEAN_AND_MEAN

#include "GameSocket.h"

#include "DebugTrace.h"

#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

GameSocket::GameSocket() {}


GameSocket::~GameSocket() {}

bool GameSocket::connect(std::string& host, std::string& port, std::string& instance, std::string& name) {
	int iResult;
	WSADATA wsaData;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
		return false;
	}

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	struct addrinfo *result = NULL;
	iResult = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0) {
		std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
		WSACleanup();
		return false;
	}

	struct addrinfo *ptr;
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		// Create a SOCKET for connecting to server
		m_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (m_socket == INVALID_SOCKET) {
			std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return false;
		}

		// Connect to server.
		iResult = ::connect(m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);
	if (m_socket == INVALID_SOCKET) {
		std::cerr << "Unable to connect to server!" << std::endl;
		WSACleanup();
		return false;
	}

	std::string rec = "";

	if (!this->sendControl(3, name)) {
		return false;
	}

	if (!this->receive(rec)) {
		return false;
	}

	if (rec != "ok") {
		std::cerr << rec << std::endl;
		return false;
	}

	if (!this->sendControl(4, instance)) {
		return false;
	}

	if (!this->receive(rec)) {
		return false;
	}

	if (rec != "ok") {
		std::cerr << rec << std::endl;
		return false;
	}

	return true;
}

bool GameSocket::sendControl(uint8_t type, std::string msg) {
	std::string sm = "";
	sm += (unsigned char)type;
	sm += (unsigned char)(msg.length() % 256);
	sm += msg;
	return this->send(sm);
}

bool GameSocket::send(std::string msg) {

#if DEBUG > 0
	for (size_t i=0; i<msg.length(); ++i) {
		if ((unsigned char)msg[i] > 31) {
			debug << msg[i];
		} else {
			debug << "#(" << ((unsigned int)(msg[i]) % 256) << ")";
		}
	}
	debug << std::endl;
#endif

	int iResult = ::send(m_socket, msg.c_str(), msg.length(), 0);
	if (iResult == SOCKET_ERROR) {
		std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
		closesocket(m_socket);
		WSACleanup();
		return false;
	}

	return true;
}

bool GameSocket::receive(std::string& recv) {
	std::string buf = "";

	debug << "Receive started" << std::endl;

	int l = this->internalRecv(buf);
	if (l < 4) {
		return false;
	}

	int msgLen = getInteger(buf);

	std::string s = buf.substr(4, l - 4);
	debug << "Receiving: " << msgLen << " bytes" << std::endl;

	msgLen -= l;
	while (msgLen > 0) {
		l = this->internalRecv(buf);
		if (l < 1) {
			return false;
		}
		s += buf.substr(0, l);
		msgLen -= l;
	}

	debug << "Receive done" << std::endl;

	recv = s;
	return true;
}

int GameSocket::internalRecv(std::string& buf) {
	char rbuf[4096];
	int iResult = recv(m_socket, rbuf, 4096, 0);
	if (iResult > 0) {
		buf = std::string(rbuf, iResult);
		debug << "Read " << iResult << " bytes" << std::endl;

		for (int dbg = 0; dbg < iResult; ++dbg) {
			debug << "[" << (unsigned char)rbuf[dbg] << "]";
		}

		return iResult;
	}
	else if (iResult == 0) {
		debug << "Connection closed." << std::endl;
		this->disconnect();
		return 0;
	}
	else {
		std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
		this->disconnect();
		return -1;
	}
}

int GameSocket::getInteger(std::string str) {
	int res = ((unsigned char)str[0] * (1 << 0)) + ((unsigned char)str[1] * (1 << 8)) + ((unsigned char)str[2] * (1 << 16)) + ((unsigned char)str[3] * (1 << 24)) - 16777216;
	debug << "Parsed int: " << res << std::endl;
	return res;
};

int GameSocket::get4or5ByteInteger(std::string str) {
	int res = getInteger(str);
	if (res < 0) {
		res = getInteger(str.substr(1, 4));
	}

	return res;
};

void GameSocket::disconnect() {
	closesocket(m_socket);
	WSACleanup();
}
