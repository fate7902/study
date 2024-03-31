#pragma once
#include "player.h"
constexpr int PORT = 4000;
constexpr auto SERVERIP = "127.0.0.1";
constexpr int BUF = 256;

class Network
{
public:
	TcpSocket			m_socket;
	Socket::Status		m_status;

	Player*				m_player;

public:
	Network();
	~Network() = default;

	void initialize();
	void sendPacket(void* packet);
	void sendLogin();
	void sendMove(MOVETYPE moveType);

	void recv();
	void recvPacketChecking(char* recvPacket, size_t received);
	void processPacket(char* processedPacket);
};

