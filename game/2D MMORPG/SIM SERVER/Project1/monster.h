#pragma once
#include "object.h"

class Monster : public Object
{
public:
	int						m_initX, m_initY;
	int						m_targetID;
	MONSTERTYPE				m_monsterType;
	MONSTERSTATE			m_monsterState;

public:
	Monster();
	Monster(int id, int hp) : Object(id, hp) {}
	virtual ~Monster() override;

public:
	void initialize();
};
