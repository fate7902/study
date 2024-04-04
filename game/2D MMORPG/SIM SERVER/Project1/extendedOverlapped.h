/*
* IOCP 통신에서 패킷에 대한 정보를 담기위한 헤더
* 기존의 오버랩 구조체를 확장해 다양한 I/O 작업에 대한 처리를 가능하게 하기 위함
*/

#pragma once
#include "packetInfo.h"

constexpr int BUFSIZE = 256;

class ExtendedOverlapped
{
public:
	WSAOVERLAPPED		m_wsaOver;
	WSABUF				m_wsaBuf;
	char				m_sendBuf[BUFSIZE];
	OVERTYPE			m_overType;
	int					m_activeID;

public:
	ExtendedOverlapped();
	ExtendedOverlapped(char* protocol);
	~ExtendedOverlapped() = default;
};
