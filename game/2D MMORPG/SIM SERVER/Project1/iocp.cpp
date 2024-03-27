#include "stdafx.h"
#include "iocp.h"

void Iocp::initialize()
{	
	cout << "[Loading] Iocp::initialize()\n";

	for (int i = 1; i <= MAXUSER; i++) m_availableID.push(i);

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

int Iocp::getIDAssignment()
{
	int id;
	if (m_availableID.try_pop(id)) return id;
	else return -1;
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
		processPacketIO(extOver, len, key);
	}
}

void Iocp::processPacketIO(ExtendedOverlapped*& extOver, DWORD len, ULONG_PTR key)
{
	switch (extOver->m_overType)
	{
	case OVERTYPE::ACCEPT:
	{
		//SOCKET clientSocket = reinterpret_cast<SOCKET>(extOver->m_wsaBuf.buf);
		int assignmentID = getIDAssignment();
		if (assignmentID != -1) {
			cout << "[접속성공] 고유키 값 : " << assignmentID << " 사용 유저 접속!\n";
			m_objectManager.m_client.m_x.store(1);
			m_objectManager.m_client.m_y.store(1);
			m_objectManager.m_client.m_id = assignmentID;
			m_objectManager.m_client.m_socket = m_clientSock;
			m_objectManager.m_client.m_reaminPacketData = 0;
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_clientSock), m_iocpHandle, assignmentID, 0);
			m_objectManager.m_client.asynRecv();
			m_clientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
		else {
			cout << "접속 한계로인한 접속 불가.\n";
		}
		ZeroMemory(&m_extOver.m_wsaOver, sizeof(m_extOver.m_wsaOver));		
		m_addrSize = sizeof(SOCKADDR_IN);
		AcceptEx(m_serverSock, m_clientSock, m_extOver.m_sendBuf, 0, m_addrSize + 16, m_addrSize + 16, 0, &m_extOver.m_wsaOver);
	}
	break;
	case OVERTYPE::RECV: 
	{
		if (len == 0) {
			// 접속 끊기
		}
		int remainPacketData = len + m_objectManager.m_client.m_reaminPacketData;
		char* p = extOver->m_sendBuf;
		while (remainPacketData > 0) {
			int packetSize = p[0];
			if (packetSize <= remainPacketData) {
				processPacket(p, key);
				p = p + packetSize;
				remainPacketData = remainPacketData - packetSize;
			}
			else break;
		}
		m_objectManager.m_client.m_reaminPacketData = remainPacketData;
		if (remainPacketData > 0) {
			memcpy(extOver->m_sendBuf, p, remainPacketData);
		}
		m_objectManager.m_client.asynRecv();
	}
	break;
	case OVERTYPE::SEND: break;
	default: cout << "[Unknowed Packet Error] check the over Type of packet. \n"; break;
	}
}

void Iocp::processPacket(char* packet, ULONG_PTR key)
{
	switch (packet[1])
	{
	case CS_LOGIN_REQUEST:
	{
		cout << "[로그인성공] 고유키 값 : " << key << " 사용 유저 로그인성공!\n";
		CS_LOGIN_REQUEST_PACKET* p = reinterpret_cast<CS_LOGIN_REQUEST_PACKET*>(packet);
		m_objectManager.m_client.m_x.store(2);
		m_objectManager.m_client.m_y.store(6);
		m_objectManager.m_client.sendLoginAllowPacket();
	}
	break;
	default: break;
	}
}
