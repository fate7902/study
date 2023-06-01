#pragma once
#include "ext_over.h"
#include "client.h"
#include "monster.h"
#include "lfvec.h"

constexpr int PORT_NUM = 4000;
constexpr int THREADS_NUM = 12;

struct TIMER_EVENT {
	int monster_id;
	EVENT_TYPE ev;
	system_clock::time_point act_time;
	int target_id;

	constexpr bool operator < (const TIMER_EVENT& _Left) const
	{
		return (act_time > _Left.act_time);
	}

};

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

	priority_queue<TIMER_EVENT> timer_queue;
	mutex timer_l;

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