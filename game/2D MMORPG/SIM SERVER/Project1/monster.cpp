#include "stdafx.h"
#include "monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
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
