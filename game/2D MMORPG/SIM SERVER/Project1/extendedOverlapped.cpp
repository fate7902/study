#include "stdafx.h"
#include "extendedOverlapped.h"

ExtendedOverlapped::ExtendedOverlapped()
{
	m_wsaBuf.len = BUFSIZE;
	m_wsaBuf.buf = m_sendBuf;
	m_overType = OVERTYPE::RECV;
	ZeroMemory(&m_wsaOver, sizeof(m_wsaOver));
}

ExtendedOverlapped::ExtendedOverlapped(char* protocol)
{
	m_wsaBuf.len = protocol[0];
	m_wsaBuf.buf = m_sendBuf;
	ZeroMemory(&m_wsaOver, sizeof(m_wsaOver));
	m_overType = OVERTYPE::SEND;
	memcpy(m_sendBuf, protocol, protocol[0]);
}
