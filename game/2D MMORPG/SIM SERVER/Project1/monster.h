#pragma once
#include "object.h"

class Monster : public Object
{
public:
	Monster() = default;
	Monster(int id, int hp) : Object(id, hp) {}
	~Monster() = default;
};
