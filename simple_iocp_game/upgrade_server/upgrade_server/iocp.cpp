#include "stdafx.h"
#include "iocp.h"

IOCP::IOCP()
{
	m_serverSocket = NULL;
	m_clientSocket = NULL;
	memset(&m_serverAddr, 0, sizeof(m_serverAddr));
	memset(&m_clientAddr, 0, sizeof(m_clientAddr));	
	for (int i = 0; i < MAX_USER; ++i) m_IDList.push(i);
}

void IOCP::ErrorDisplay(const char* msg, const int& err)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	cout << msg;
	wcout << L"ERROR " << lpMsgBuf << "\n";
	LocalFree(lpMsgBuf);
}

int IOCP::GetClientID()
{
	int clientID;
	if(m_IDList.try_pop(clientID)) return clientID;
	return -1;
}

void IOCP::Initialize()
{
	WSADATA WASData;
	int ret = WSAStartup(MAKEWORD(2, 2), &WASData);
	if (ret != 0) ErrorDisplay("WSAStartup Error : ", WSAGetLastError());

	m_serverSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&m_serverAddr, 0, sizeof(m_serverAddr));
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(PORT);
	m_serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	ret = bind(m_serverSocket, reinterpret_cast<sockaddr*>(&m_serverAddr), sizeof(m_serverAddr));
	if (ret != 0) ErrorDisplay("bind Error : ", WSAGetLastError());

	ret = listen(m_serverSocket, SOMAXCONN);
	if (ret != 0) ErrorDisplay("listen Error : ", WSAGetLastError());

	int addr_size = sizeof(m_clientAddr);

	m_iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_serverSocket), m_iocpHandle, 9999, 0);
	m_clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_acceptOver.overType = OVER_TYPE::ACCEPT;
	AcceptEx(m_serverSocket, m_clientSocket, m_acceptOver.sendBuf, 0, addr_size + 16, addr_size + 16, 0, &m_acceptOver.wsaOver);

	vector<thread> workerThreads;
	for (int i = 0; i < MAX_THREADS; ++i)
		workerThreads.emplace_back(&IOCP::Worker, this);
	for (auto& th : workerThreads)
		th.join();

	closesocket(m_serverSocket);
	WSACleanup();
}

void IOCP::Worker()
{
	while (true) {
		DWORD sizeOfData;
		ULONG_PTR key;
		WSAOVERLAPPED* over = nullptr;
		bool bret = GetQueuedCompletionStatus(m_iocpHandle, &sizeOfData, &key, &over, INFINITE);
		EXT_OVER* extOver = reinterpret_cast<EXT_OVER*>(over);
		if (bret == false) {
			if (OVER_TYPE::ACCEPT == extOver->overType)
				cout << "Accept Error\n";
			else {
				cout << "Logout on client[" << key << "]\n";
				// �ش� key ���� �α׾ƿ� ó�� �ʿ�
				if (OVER_TYPE::SEND == extOver->overType) delete extOver;
				continue;
			}
		}

		// �Ϸ�� �۾��� ���� ó��
		// ������ ����ü�� ���� ��� �۾��� ���� �Ϸ� ������� Ȯ�� 
		IOProcessing(extOver, sizeOfData, key);		
	}
}

void IOCP::IOProcessing(EXT_OVER*& extOver, const DWORD& sizeOfData, const ULONG_PTR key)
{
	switch (extOver->overType)
	{
		// Ŭ���̾�Ʈ ���� ��û
	case OVER_TYPE::ACCEPT:
	{
		int clientID = GetClientID();
		if (clientID != -1) {
			cout << "Ŭ���̾�Ʈ [" << clientID << "��] ���� �����û�� �����߽��ϴ�.\n";
			AddNewClient(0, m_clientSocket, clientID);
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_clientSocket), m_iocpHandle, clientID, 0);
			auto iter = m_clients.find(clientID);
			if (iter != m_clients.end()) iter->second.recv();
		}
		else {
			// �α��� ���� ó��
			cout << "���� ���� �ο��� �ʰ��Ͽ� �����û�� �ź��߽��ϴ�.\n";
		}
		m_clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		ZeroMemory(&extOver->wsaOver, sizeof(extOver->wsaOver));
		int addrSize = sizeof(SOCKADDR_IN);
		AcceptEx(m_serverSocket, m_clientSocket, extOver->sendBuf, 0, addrSize + 16, addrSize + 16, 0, &extOver->wsaOver);
	}
		break;
	case OVER_TYPE::RECV:
		if (sizeOfData == 0) {
			// �ǵ����� ���� ��Ȳ ���� ����
			break;
		}
		PacketAssembly(extOver, sizeOfData, key);
		break;
	case OVER_TYPE::SEND:
		break;
	}
}

void IOCP::AddNewClient(int prevRemainDataSize, SOCKET socket, int UID)
{
	CLIENT cl(prevRemainDataSize, socket, UID);
	auto iter = m_clients.find(UID);
	if (iter != m_clients.end()) iter->second = cl;
	else m_clients.insert(make_pair(UID, cl));
}

void IOCP::PacketAssembly(EXT_OVER*& extOver, const DWORD& sizeOfData, int UID)
{
	auto iter = m_clients.find(UID);
	int remainData = sizeOfData + iter->second.m_prevRemainDataSize;
	char* packet = extOver->sendBuf;
	int protocolSize = packet[0];
	while (remainData > 0 && protocolSize <= remainData) {
		PacketProcessing(UID, packet);
		packet = packet + protocolSize;
		remainData = remainData - protocolSize;
	}
	iter->second.m_prevRemainDataSize = remainData;
	if (remainData > 0) {
		memcpy(extOver->sendBuf, packet, remainData);
	}
	iter->second.recv();
}

void IOCP::PacketProcessing(int clientID, char* packet)
{
	switch (packet[1]) {
	case CS_LOGIN:
	{
		CS_LOGIN_PROTOCOL* p = reinterpret_cast<CS_LOGIN_PROTOCOL*>(packet);
		cout << "[" << clientID << "] ���� �����ϼ̽��ϴ�.\n";
	}
		break;
	}
}
