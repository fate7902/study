#include "stdafx.h"
#include "iocp.h"

void Iocp::initialize()
{	
	cout << "[Loading] Iocp::initialize()\n";

	IocpBase::initialize();	

	m_clientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_extOver.m_overType = OVERTYPE::ACCEPT;
	AcceptEx(m_serverSock, m_clientSock, m_extOver.m_sendBuf, 0, m_addrSize + 16, m_addrSize + 16, 0, &m_extOver.m_wsaOver);

	vector<thread> worker_threads;
	for (int i = 0; i < MAXTHREAD; ++i)
		worker_threads.emplace_back(&Iocp::worker, this);	
	for (auto& th : worker_threads)
		th.join();
}

void Iocp::worker()
{
	while (true) {
		DWORD len;
		ULONG_PTR key;
		WSAOVERLAPPED* wsaOver = nullptr;
		bool bret = GetQueuedCompletionStatus(m_iocpHandle, &len, &key, &wsaOver, INFINITE);
		ExtendedOverlapped* extOver = reinterpret_cast<ExtendedOverlapped*>(wsaOver);
		if (bret == false) {
			if (OVERTYPE::ACCEPT == extOver->m_overType)
				cout << "Accept Error\n";
			else {
				cout << "Logout on client[" << key << "]\n";
				// 로그아웃 처리 필요
				continue;
			}
		}

		// 패킷 타입에 따른 처리 필요
		switch (extOver->m_overType)
		{
		case OVERTYPE::ACCEPT: break;
		case OVERTYPE::SEND: break;
		case OVERTYPE::RECV: break;
		default: cout << "[Unknowed Packet Error] check the over Type of packet. \n"; break;
		}
	}
}
