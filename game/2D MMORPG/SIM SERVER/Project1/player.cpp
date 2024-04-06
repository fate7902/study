#include "stdafx.h"
#include "player.h"
#include "monster.h"

Player::Player()
{
	m_viewlist = new concurrent_unordered_set<int>;
}

Player::~Player()
{
	delete m_viewlist;
}

void Player::initialize(CHARACTERINFO& characterInfo)
{
	setPosition(characterInfo.x, characterInfo.y);
	setZone();
	m_ID = characterInfo.ID;
	m_PW = characterInfo.PW;
	m_lv = characterInfo.lv;
	m_hp = characterInfo.hp;
	m_exp = characterInfo.exp;
}

void Player::setSocket(SOCKET sock)
{
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

void Player::sendLoginAllowPacket(LOGINRESULT loginResult)
{
	SC_LOGIN_ALLOW_PACKET p;
	p.size = sizeof(SC_LOGIN_ALLOW_PACKET);
	p.type = SC_LOGIN_ALLOW;
	if (loginResult == LOGINRESULT::SUCCESS) {
		p.x = m_x.load();
		p.y = m_y.load();
		p.lv = m_lv;
		p.exp = m_exp;
		p.hp = m_hp;
		p.key = m_id;
	}
	p.loginResult = static_cast<int>(loginResult);
	p.key = m_id;
	sendPacket(&p);
}

void Player::sendMoveAllowPacket(Object& obj, unsigned time)
{
	SC_MOVE_ALLOW_PACKET p;
	p.size = sizeof(SC_MOVE_ALLOW_PACKET);
	p.type = SC_MOVE_ALLOW;
	p.x = obj.m_x.load();
	p.y = obj.m_y.load();
	p.key = obj.m_id;
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
	p.key = obj.m_id;
	if (p.key >= MAXUSER) {
		Monster* monster = dynamic_cast<Monster*>(&obj);
		p.monsterType = static_cast<int>(monster->m_monsterType);
	}
	sendPacket(&p);
}

void Player::sendDeleteObjectPacket(int id)
{
	SC_DELETEOBJECT_ALLOW_PACKET p;
	p.size = sizeof(SC_DELETEOBJECT_ALLOW_PACKET);
	p.type = SC_DELETEOBJECT_ALLOW;
	p.key = id;
	sendPacket(&p);
}