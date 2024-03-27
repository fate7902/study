/*
* IOCP ������ �����ϴ� �� �־� �ʿ��� �κ��� OOP ������� �����ϱ� ���� ���
* �ٸ� ������Ʈ���� IOCP ������ ����ٰ� �����Ͽ� ��� ������Ʈ�̴�
* �ݵ�� ���� ������ �ʴ� �κи� ���� �߸����� �Ͽ���
*/

#pragma once
#include "packetInfo.h"

class IocpBase 
{
protected:
	SOCKET				m_serverSock, m_clientSock;
	SOCKADDR_IN			m_serverAddr, m_clientAddr;
	HANDLE				m_iocpHandle;
	int					m_port, m_addrSize;


protected:
	IocpBase() = default;
	IocpBase(int port);
	~IocpBase();

	void initialize();

private:
	void errorDisplay(const char* msg, int err_no);

};