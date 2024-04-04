/*
* IOCP ��ſ��� ��Ŷ�� ���� ������ ������� ���
* ������ ������ ����ü�� Ȯ���� �پ��� I/O �۾��� ���� ó���� �����ϰ� �ϱ� ����
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
