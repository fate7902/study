#include "stdafx.h"
#include "player.h"

Player::Player()
{
	m_viewlist = new concurrent_unordered_set<int>;
}

Player::~Player()
{
	delete m_viewlist;
}

void Player::initialize(SOCKET sock)
{
	setPosition(0, 0);
	m_socket = sock;
	m_reaminPacketData = 0;
}

void Player::asynRecv()
{
	DWORD recvFlag = 0;
	memset(&m_recvOver.m_wsaOver, 0, sizeof(m_recvOver.m_wsaOver));
	m_recvOver.m_wsaBuf.len = BUFSIZE - m_reaminPacketData;
	m_recvOver.m_wsaBuf.buf = m_recvOver.m_sendBuf + m_reaminPacketData;
	WSARecv(m_socket, &m_recvOver.m_wsaBuf, 1, 0, &recvFlag, &m_recvOver.m_wsaOver, 0);
}

void Player::sendPacket(void* packet)
{
	ExtendedOverlapped* sendData = new ExtendedOverlapped{ reinterpret_cast<char*>(packet) };
	WSASend(m_socket, &sendData->m_wsaBuf, 1, 0, 0, &sendData->m_wsaOver, 0);
}

void Player::sendLoginAllowPacket()
{
	SC_LOGIN_ALLOW_PACKET p;
	p.size = sizeof(SC_LOGIN_ALLOW_PACKET);
	p.type = SC_LOGIN_ALLOW;
	p.x = m_x.load();
	p.y = m_y.load();
	p.id = m_id;
	sendPacket(&p);
}

void Player::sendMoveAllowPacket(Object& obj, unsigned time)
{
	SC_MOVE_ALLOW_PACKET p;
	p.size = sizeof(SC_MOVE_ALLOW_PACKET);
	p.type = SC_MOVE_ALLOW;
	p.x = obj.m_x.load();
	p.y = obj.m_y.load();
	p.id = obj.m_id;
	p.clientTime = time;
	sendPacket(&p);
}

void Player::sendAddObjectPacket(Object& obj)
{
	SC_ADDOBJECT_ALLOW_PACKET p;
	p.size = sizeof(SC_ADDOBJECT_ALLOW_PACKET);
	p.type = SC_ADDOBJECT_ALLOW;
	p.x = obj.m_x.load();
	p.y = obj.m_y.load();
	p.id = obj.m_id;
	sendPacket(&p);
}

void Player::sendDeleteObjectPacket(int id)
{
	SC_DELETEOBJECT_ALLOW_PACKET p;
	p.size = sizeof(SC_DELETEOBJECT_ALLOW_PACKET);
	p.type = SC_DELETEOBJECT_ALLOW;
	p.id = id;
	sendPacket(&p);
}