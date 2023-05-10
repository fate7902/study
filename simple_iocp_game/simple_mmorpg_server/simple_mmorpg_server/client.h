#pragma once
#include "ext_over.h"

class CLIENT
{
private:
	atomic<pair<int, int>> position;
	atomic<bool> use;

    int prev_remain;
    SOCKET socket;
    EXT_OVER recv_over;

public:
	CLIENT();
	~CLIENT();

	bool GetUsing();
	void SetUsing(bool new_b);

	pair<int, int> GetPosition();
	void SetPosition(int new_x, int new_y);

	int GetPrevRemain();
	void SetPrevRemain(int val);

	void SetSocket(SOCKET s);

    void recv();

    void send(void* protocol);
	void send_login_info();
	void send_move_info();
};