#pragma once
#include "lfvec.h"

class MONSTER
{
private:
	atomic<pair<int, int>> position;
	int ID;
	LFVEC* viewlist;
	lua_State* L;

public:
	MONSTER();
	~MONSTER();

	pair<int, int> GetPosition();
	void SetPosition(int new_x, int new_y);
	bool CalcDistance(const pair<int, int>& pos1, const pair<int, int>& pos2);

	int GetID();
	void SetID(int id);

	void AddViewlist(int id);
	bool FindViewlist(int id);
	void RemoveViewlist(int id);

	void SetLua(lua_State* l);
	lua_State* GetLua();
};