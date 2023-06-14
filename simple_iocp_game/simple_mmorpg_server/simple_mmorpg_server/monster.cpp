#include "stdafx.h"
#include "monster.h"

MONSTER::MONSTER()
{
	position = { 0 , 0 };
	viewlist = new LFVEC();
}

MONSTER::~MONSTER()
{
	delete viewlist->Getvec();
	delete viewlist;
}

pair<int, int> MONSTER::GetPosition()
{
	return position.load();
}

void MONSTER::SetPosition(int new_x, int new_y)
{
	pair<int, int> old_pos = position.load();
	pair<int, int> new_pos{ new_x, new_y };
	while (!position.compare_exchange_strong(old_pos, new_pos)) {
		old_pos = position.load();
	}
}

bool MONSTER::CalcDistance(const pair<int, int>& pos1, const pair<int, int>& pos2)
{
	int dx = pos1.first - pos2.first;
	int dy = pos1.second - pos2.second;
	return (dx * dx <= 4) && (dy * dy <= 4);
}

int MONSTER::GetID()
{
	return ID;
}

void MONSTER::SetID(int id)
{
	ID = id;
}

int MONSTER::GetState()
{
	return state.load();
}

void MONSTER::SetState(bool new_state)
{
	bool old_state = state.load();
	while (!state.compare_exchange_strong(old_state, new_state)) {
		old_state = state.load();
	}
}

void MONSTER::AddViewlist(int id)
{
	viewlist->emplace_back(id);
}

bool MONSTER::FindViewlist(int id)
{
	return viewlist->exist(id);
}

void MONSTER::RemoveViewlist(int id)
{
	viewlist->erase(id);
}

int MONSTER::EmptyViewlist()
{
	vector<int>* old_vec = viewlist->Getvec();
	if (old_vec == nullptr || old_vec->empty()) return 0;
	return 1;	
}

void MONSTER::SetLua(lua_State* l)
{
	L = l;
}

lua_State* MONSTER::GetLua()
{
	return L;
}
