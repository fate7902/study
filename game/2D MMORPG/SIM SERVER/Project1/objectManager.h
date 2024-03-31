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
	// �� ������Ʈ�� �þ߹��� �ȿ� �����ϴ� �� �����ϴ� �Լ�
	bool calcInRange(Object& objA, Object& objB);
};

