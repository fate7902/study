#include "stdafx.h"
#include "object.h"

Object::Object(int id, int hp)
{
	m_id = id;
	m_hp.store(hp);
}

void Object::setHP(int val, int op)
{
	switch (op)
	{
	case 0: m_hp.store(val); break;
	case 1: m_hp.fetch_add(val); break;
	case 2: m_hp.fetch_sub(val); break;
	}
}

void Object::setPosition(int x, int y)
{
	m_x.store(x);
	m_y.store(y);
}

void Object::setPosition(MOVETYPE movetype)
{
	switch (movetype) {
	case MOVETYPE::UP: m_y.fetch_sub(1); break;
	case MOVETYPE::DOWN: m_y.fetch_add(1);  break;
	case MOVETYPE::LEFT: m_x.fetch_sub(1);  break;
	case MOVETYPE::RIGHT: m_x.fetch_add(1);  break;
	}
}
