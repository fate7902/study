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
	// �� ������Ʈ�� �þ߹��� �ȿ� �����ϴ� �� �����ϴ� �Լ�
	bool calcInRange(Object& objA, Object& objB);
};

