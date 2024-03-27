#pragma once
#include "object.h"
#include "extendedOverlapped.h"

class Player : public Object
{
public:	
	atomic<int>			m_exp;

	int					m_reaminPacketData;
	SOCKET				m_socket;
	ExtendedOverlapped	m_recvOver;

public:
	Player() = default;
	Player(int id, int hp) : Object(id, hp) {}
	~Player() = default;

	void asynRecv();
	void sendPacket(void* packet);
	void sendLoginAllowPacket();
};

