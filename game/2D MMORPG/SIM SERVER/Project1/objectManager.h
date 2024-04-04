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

	// 두 오브젝트의 거리 반환 함수
	double calcInRange(Object& objA, Object& objB);

	// 구역 변화 적용
	void changeZone(int zoneNumber, int key);

	// 소지중인 뷰리스트를 바탕으로 시야처리
	// 플레이어 이동 후 시야에서 사라지거나 자신의 이동을 알리기위한 함수
	void checkViewlist(int key, unsigned time);

	// 플레이어를 기준으로 주변 구역 확인
	// 플레이어, 몬스터 정보 전송
	// 플레이어 이동 후 시야내에 새로 보이는 오브젝트를 찾기위한 함수
	void checkPlayerZone(int zoneNumber, int key);

	// 몬스터를 기준으로 주변구역 확인
	// 몬스터 정보만 전송
	// 몬스터 이동 후 타겟을 정하기 위한 함수
	void checkMonsterZone(int zoneNumber, int key);
};

