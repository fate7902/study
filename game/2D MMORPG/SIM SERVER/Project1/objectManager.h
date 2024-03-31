#pragma once
#include "player.h"
#include "monster.h"

constexpr int VIEWRANGE = 3;
constexpr int ZONE = MAPWIDTH / 50 * MAPHEIGHT / 50;

class ObjectManager
{
public:
	concurrent_unordered_map<int, Player>	m_player;
	mutex									m_playerMutex;

	concurrent_unordered_set<int>			m_zone[ZONE];
	mutex									m_zoneMutex[ZONE];

public:
	ObjectManager() = default;
	~ObjectManager() = default;

public:
	// 두 오브젝트가 시야범위 안에 존재하는 지 측정하는 함수
	bool calcInRange(Object& objA, Object& objB);
};

