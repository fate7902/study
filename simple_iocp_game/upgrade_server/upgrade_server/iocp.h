#pragma once
#include "ext_over.h"
#include "client.h"
#include "monster.h"

class IOCP
{
public:
	SOCKET m_serverSocket, m_clientSocket;
	SOCKADDR_IN m_serverAddr, m_clientAddr;
	HANDLE m_iocpHandle;
	EXT_OVER m_acceptOver;
	concurrent_queue<int> m_IDList;
	concurrent_unordered_map<int, CLIENT> m_clients;

public :
	IOCP();
	~IOCP() = default;

	void ErrorDisplay(const char* msg, const int& err);
	int GetClientID();

	void Initialize();
	void Worker();

	void IOProcessing(EXT_OVER*& extOver, const DWORD& sizeOfData, const ULONG_PTR key);
	void AddNewClient(int prevRemainDataSize, SOCKET socket, int UID);
	void PacketAssembly(EXT_OVER*& extOver, const DWORD& sizeOfData, int UID);

	void PacketProcessing(int clientID, char* packet);
};

