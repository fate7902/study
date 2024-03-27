#pragma once
#include "player.h"
#include "monster.h"

constexpr int VIEWRANGE = 3;

class ObjectManager
{
public:
	Player				m_client;

public:
	ObjectManager() = default;
	~ObjectManager() = default;

protected:
	// 두 오브젝트가 시야범위 안에 존재하는 지 측정하는 함수
	bool calcInRange(Object& objA, Object& objB);
};

