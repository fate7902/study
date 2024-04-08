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

	// 두 오브젝트의 거리 반환 함수
	double calcInRange(Object& objA, Object& objB);

	// 구역 변화 적용
	void changeZone(int zoneNumber, int key);

	// 넘겨받은 유저키값(key)과 유저 위치 구역(zone)을 기준으로 주변 오브젝트와의 시야파악
	void checkViewAtPlayer(int zoneNumber, int key, unsigned time);

	// 넘겨받은 몬스터키값(key)과 몬스터 위치 구역(zone)을 기준으로 주변 플레이어와의 시야파악
	// 몬스터 타입이 HARD이면서 IDLE인 상태인경우 추적대상이 있는지 함께 검사
	// 몬스터 상태가 추적중이면 추적대상이 추적거리 이내인지 재검사 실행
	void checkViewAtMonster(int zoneNumber, int key);

	// 해당 구역을 처음 방문하는 지 확인후 몬스터 생성
	void checkFirstVisitZone(int zoneNumber);
};

