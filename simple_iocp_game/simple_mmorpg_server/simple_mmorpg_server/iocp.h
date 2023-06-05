#pragma once
#include "ext_over.h"
#include "client.h"
#include "monster.h"
#include "lfvec.h"
#include "lfpq.h"

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

	CLIENT* clients;
	MONSTER* monsters;
	LFVEC* ID_list;	

	LFPQ timer_queue;

public:
	IOCP();
	~IOCP();

	void Initialize(CLIENT* cl, MONSTER* ms);

protected:
	void Monster_Initialize();

	void Error_Display(const char* msg, int err_no);
	int GetClientID();
	void Disconnect(int id);

	void worker();
	void DataProcessing(EXT_OVER*& ext_over, const ULONG_PTR& key, const DWORD& len);
	void ProtocolProcessing(const int& client_id, char* protocol);

	void Monster_Thread();
	void process_event(TIMER_EVENT k);
	void do_timer();

};