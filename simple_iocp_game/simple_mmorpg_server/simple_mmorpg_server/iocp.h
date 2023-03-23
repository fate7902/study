#pragma once
#include "ext_over.h"

constexpr int PORT_NUM = 4000;
constexpr int THREADS_NUM = 12;

class IOCP
{
private:
	int ret;
	SOCKET server_socket, client_socket;
	SOCKADDR_IN server_addr, client_addr;
	HANDLE handle_iocp;
	EXT_OVER accept_over;

public:
	IOCP();
	~IOCP();

	void Initialize();

protected:
	void Error_Display(const char* msg, int err_no);
	void worker();
};