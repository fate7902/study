#include "stdafx.h"
#include "player.h"

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
	p.x = m_x;
	p.y = m_y;
	sendPacket(&p);
}
