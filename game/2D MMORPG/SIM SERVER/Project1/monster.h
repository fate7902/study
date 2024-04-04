#pragma once
#include "object.h"

class Monster : public Object
{
public:
	lua_State*				m_luaState;
	int						m_initX, m_initY;
	int						m_targetID;
	MONSTERTYPE				m_monsterType;
	MONSTERSTATE			m_monsterState;

public:
	Monster();
	Monster(int id, int hp) : Object(id, hp) {
		m_luaState = luaL_newstate();
		luaL_openlibs(m_luaState);
		if (luaL_loadfile(m_luaState, "monster.lua") || lua_pcall(m_luaState, 0, 0, 0)) {
			cout << "[2루아스크립트 오류] " << lua_tostring(m_luaState, -1) << "\n";
		}
	}
	virtual ~Monster() override;

public:
	void initialize();
};
