#pragma once
#include "ext_over.h"

constexpr int PORT_NUM = 4000;
constexpr int THREADS_NUM = 12;

struct TEMP_CLIENT
{
    int x = 0, y = 0;
    char name[10] = { 0 };
    int id = 0;
    int prev_remain = 0;
    SOCKET socket = INVALID_SOCKET;
    EXT_OVER recv_over = {};
    bool use = false;

    void do_recv()
    {
        DWORD recv_flag = 0;
        memset(&recv_over.GetWSAOverlapped(), 0, sizeof(recv_over.GetWSAOverlapped()));
        recv_over.GetWsabuf().len = BUF_SIZE - prev_remain;
        recv_over.GetWsabuf().buf = recv_over.GetSendBuf() + prev_remain;
        WSARecv(socket, &recv_over.GetWsabuf(), 1, 0, &recv_flag,
            &recv_over.GetWSAOverlapped(), 0);
    }

    void do_send(void* protocol)
    {
        EXT_OVER* sdata = new EXT_OVER{ reinterpret_cast<char*>(protocol) };
        WSASend(socket, &sdata->GetWsabuf(), 1, 0, 0, &sdata->GetWSAOverlapped(), 0);
    }
};

class IOCP
{
protected:
	int ret, addr_size;
	SOCKET server_socket, client_socket;
	SOCKADDR_IN server_addr, client_addr;
	HANDLE handle_iocp;
	EXT_OVER accept_over;
    TEMP_CLIENT temp_client[10]{};

public:
	IOCP();
	~IOCP() = default;

	void Member_Initialize();
	void Initialize();

protected:
	void Error_Display(const char* msg, int err_no);
    int GetClientID();
	void worker();
    void DataProcessing(EXT_OVER*& ext_over, const ULONG_PTR& key, const DWORD& len);
    void ProtocolProcessing(const int& client_id, char* protocol);
};