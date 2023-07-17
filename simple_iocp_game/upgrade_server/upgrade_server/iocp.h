#pragma once
#include "ext_over.h"

class IOCP
{
public:
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddr, clientAddr;
	HANDLE iocpHandle;
	EXT_OVER acceptOver;

public :
	IOCP() = default;
	~IOCP() = default;

	void Initialize();
	void Worker();
	void ErrorDisplay(const char* msg, int err);
};

