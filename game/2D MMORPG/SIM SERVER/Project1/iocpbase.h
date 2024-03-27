/*
* IOCP 서버를 구현하는 데 있어 필요한 부분을 OOP 방식으로 구현하기 위한 헤더
* 다른 프로젝트에서 IOCP 서버를 만든다고 가정하여 어느 프로젝트이던
* 반드시 들어가고 변하지 않는 부분만 따로 추리고자 하였음
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