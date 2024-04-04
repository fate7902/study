#pragma once
#include "player.h"
#include "monster.h"

constexpr int VIEWRANGE = 3;
constexpr int CHASERANGE = 6;
constexpr int ATTACKRANGE = 1;

class ObjectManager
{
public:
	concurrent_unordered_map<int, Player>*	m_player;
	mutex									m_playerMutex;
	concurrent_unordered_map<int, Monster>* m_monster;

	concurrent_unordered_set<int>*			m_zone;
	mutex*									m_zoneMutex;

public:
	ObjectManager();
	~ObjectManager();

public:
	void monsterInitialize();

	// �� ������Ʈ�� �Ÿ� ��ȯ �Լ�
	double calcInRange(Object& objA, Object& objB);

	// ���� ��ȭ ����
	void changeZone(int zoneNumber, int key);

	// �������� �丮��Ʈ�� �������� �þ�ó��
	// �÷��̾� �̵� �� �þ߿��� ������ų� �ڽ��� �̵��� �˸������� �Լ�
	void checkViewlist(int key, unsigned time);

	// �÷��̾ �������� �ֺ� ���� Ȯ��
	// �÷��̾�, ���� ���� ����
	// �÷��̾� �̵� �� �þ߳��� ���� ���̴� ������Ʈ�� ã������ �Լ�
	void checkPlayerZone(int zoneNumber, int key);

	// ���͸� �������� �ֺ����� Ȯ��
	// ���� ������ ����
	// ���� �̵� �� Ÿ���� ���ϱ� ���� �Լ�
	void checkMonsterZone(int zoneNumber, int key);
};

