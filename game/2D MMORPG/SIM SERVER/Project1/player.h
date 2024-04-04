#pragma once
#include "object.h"
#include "extendedOverlapped.h"

class Player : public Object
{
public:	
	atomic<int>						m_exp;
	concurrent_unordered_set<int>*	m_viewlist;
	mutex							m_viewlistMutex;

	int								m_reaminPacketData;
	SOCKET							m_socket;
	ExtendedOverlapped				m_recvOver;

public:
	Player();
	Player(int id, int hp) : Object(id, hp){
		m_viewlist = new concurrent_unordered_set<int>;
	}
	Player(const Player& other)
		: Object(other), m_exp(other.m_exp.load()),
		m_reaminPacketData(other.m_reaminPacketData),
		m_socket(other.m_socket), m_recvOver(other.m_recvOver) {
		m_viewlist = new concurrent_unordered_set<int>(*other.m_viewlist);
	}
	virtual ~Player() override;

	void initialize(SOCKET sock);
	void asynRecv();
	void sendPacket(void* packet);
	void sendLoginAllowPacket();
	void sendMoveAllowPacket(Object& obj, unsigned time);
	void sendAddObjectPacket(Object& obj);
	void sendDeleteObjectPacket(int id);
};

