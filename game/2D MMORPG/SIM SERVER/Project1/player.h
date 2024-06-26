#pragma once
#include "object.h"
#include "extendedOverlapped.h"

class Player : public Object
{
public:	
	atomic<int>									m_exp;
	shared_ptr<concurrent_unordered_set<int>>	m_viewlist;
	mutex										m_viewlistMutex;

	int											m_reaminPacketData;
	SOCKET										m_socket;
	ExtendedOverlapped							m_recvOver;

	string										m_ID, m_PW;
	int											m_lv;

public:
	Player() : m_viewlist(make_shared<concurrent_unordered_set<int>>()) {}
	Player(int id, int hp) : Object(id, hp), m_viewlist(make_shared<concurrent_unordered_set<int>>()) {}
	Player(const Player& other)
		: Object(other), m_exp(other.m_exp.load()),
		m_reaminPacketData(other.m_reaminPacketData),
		m_socket(other.m_socket), m_recvOver(other.m_recvOver),
		m_ID(other.m_ID), m_PW(other.m_PW), m_lv(other.m_lv) {
		m_viewlist = make_shared<concurrent_unordered_set<int>>(*other.m_viewlist);
	}
	virtual ~Player() override = default;

	void initialize(CHARACTERINFO& characterInfo);
	void setSocket(SOCKET sock);
	void asynRecv();
	void sendPacket(void* packet);
	void sendLoginAllowPacket(LOGINRESULT loginResult);
	void sendMoveAllowPacket(const shared_ptr<Object>& obj, unsigned time);
	void sendAddObjectPacket(const shared_ptr<Object>& obj);
	void sendDeleteObjectPacket(int id);
};

