#pragma once
#include "ext_over.h"
#include "lfvec.h"

class CLIENT
{
private:
	atomic<pair<int, int>> position;
	atomic<bool> use;

	int ID;
	LFVEC viewlist;

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
	bool CalcDistance(const pair<int, int>& pos1, const pair<int, int>& pos2);

	int GetID();
	void SetID(int id);

	void AddViewlist(int id);
	bool FindViewlist(int id);
	void RemoveViewlist(int id);

	int GetPrevRemain();
	void SetPrevRemain(int val);

	void SetSocket(SOCKET s);

    void recv();

    void send(void* protocol);
	void send_login_info(CLIENT& cl);
	void send_move_info(CLIENT& cl);
	void send_add_object_info(CLIENT& cl);
	void send_remove_object_info(CLIENT& cl);
};