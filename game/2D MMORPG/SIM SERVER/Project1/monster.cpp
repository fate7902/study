#include "stdafx.h"
#include "monster.h"

Monster::Monster()
{
	m_luaState = luaL_newstate();
	luaL_openlibs(m_luaState);
	luaL_dofile(m_luaState, "monster.lua");
	if (luaL_loadfile(m_luaState, "monster.lua") || lua_pcall(m_luaState, 0, 0, 0)) {
		cout << "[1루아스크립트 오류] " << lua_tostring(m_luaState, -1) << "\n";
	}
}

Monster::~Monster()
{
	lua_close(m_luaState);
}

void Monster::initialize()
{
	setPosition(rand() % 2000, rand() % 2000);	
	setZone();
	m_initX = m_x.load();
	m_initY = m_y.load();
	m_monsterType = static_cast<MONSTERTYPE>(rand() % 3);
	m_monsterState = MONSTERSTATE::NONE;
	m_targetID = -1;
}
