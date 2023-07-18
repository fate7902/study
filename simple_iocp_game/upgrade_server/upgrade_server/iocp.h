#pragma once
#include "ext_over.h"

class IOCP
{
public:
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddr, clientAddr;
	HANDLE iocpHandle;
	EXT_OVER acceptOver;
	concurrent_queue<int> IDList;

public :
	IOCP() = default;
	~IOCP() = default;

	void ErrorDisplay(const char* msg, const int& err);
	int GetClientID();
	void Initialize();
	void Worker();
	void IOProcessing(EXT_OVER*& extOver, const DWORD& sizeOfData, const ULONG_PTR key);
	void PacketProcessing(const int& clientID, char* packet);
};

