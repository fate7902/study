#pragma once
#include "player.h"
#include "monster.h"

constexpr int VIEWRANGE = 3;

class ObjectManager
{
public:
	concurrent_unordered_map<int, Player>*	m_player;
	mutex									m_playerMutex;

	concurrent_unordered_set<int>*			m_zone;
	mutex*									m_zoneMutex;

public:
	ObjectManager();
	~ObjectManager();

public:
	// �� ������Ʈ�� �þ߹��� �ȿ� �����ϴ� �� �����ϴ� �Լ�
	bool calcInRange(Object& objA, Object& objB);
};

