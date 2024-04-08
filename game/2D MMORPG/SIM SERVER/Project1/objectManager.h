#pragma once
#include "player.h"
#include "monster.h"

constexpr int VIEWRANGE = 3;
constexpr int CHASERANGE = 6;
constexpr int ATTACKRANGE = 1;

class ObjectManager
{
public:
	concurrent_unordered_map<int, Player*>*	m_player;
	mutex									m_playerMutex;
	concurrent_unordered_map<int, Player*>* m_logoutPlayer;
	mutex									m_logoutPlayerMutex;
	concurrent_unordered_map<int, Monster>* m_monster;

	concurrent_unordered_set<int>*			m_zone;
	mutex*									m_zoneMutex;

	lua_State*								m_luaState[MAXMONSTERSPECIES];
	mutex*									m_luaMutex;

	concurrent_priority_queue<TIMER>		m_timer;
	atomic<bool>*							m_bZone;

public:
	ObjectManager();
	~ObjectManager();

public:
	void monsterInitialize();

	// �� ������Ʈ�� �Ÿ� ��ȯ �Լ�
	double calcInRange(Object& objA, Object& objB);

	// ���� ��ȭ ����
	void changeZone(int zoneNumber, int key);

	// �Ѱܹ��� ����Ű��(key)�� ���� ��ġ ����(zone)�� �������� �ֺ� ������Ʈ���� �þ��ľ�
	void checkViewAtPlayer(int zoneNumber, int key, unsigned time);

	// �Ѱܹ��� ����Ű��(key)�� ���� ��ġ ����(zone)�� �������� �ֺ� �÷��̾���� �þ��ľ�
	// ���� Ÿ���� HARD�̸鼭 IDLE�� �����ΰ�� ��������� �ִ��� �Բ� �˻�
	// ���� ���°� �������̸� ��������� �����Ÿ� �̳����� ��˻� ����
	void checkViewAtMonster(int zoneNumber, int key);

	// �ش� ������ ó�� �湮�ϴ� �� Ȯ���� ���� ����
	void checkFirstVisitZone(int zoneNumber);
};

