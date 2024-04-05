#pragma once
#include "stdafx.h"
#include "player.h"
#include "monster.h"

constexpr int PORT = 4000;
constexpr auto SERVERIP = "127.0.0.1";
constexpr int BUF = 256;

class Network
{
public:
	TcpSocket									m_socket;
	Socket::Status								m_status;

	Player										m_player;
	int											m_id;
	Player*										m_otherPlayer;
	concurrent_unordered_map<int, Monster>*		m_monster;
	Texture*									m_monsterTexture;

public:
	Network() = default;
	~Network();

	void initialize();
	void sendPacket(void* packet);
	void sendLogin();
	void sendMove(MOVETYPE moveType);

	void recv();
	void recvPacketChecking(char* recvPacket, size_t received);
	void processPacket(char* processedPacket);
};

