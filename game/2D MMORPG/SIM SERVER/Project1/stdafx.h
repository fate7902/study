/*
* 미리 컴파일된 헤더 사용
* 자주 사용되지만 변경이 되지 않는 부분
*/

#pragma once
// 네트워크 관련 헤더
#include <WS2tcpip.h>
#include <MSWSock.h>
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "MSWSock.lib")

// 일반적인 헤더
#include <iostream>
#include <thread>
#include <vector>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <concurrent_unordered_set.h>
#include <concurrent_priority_queue.h>
#include <atomic>
#include <mutex>
#include <chrono>

// DB관련 헤더
#include <sqlext.h>

// 루아 스크립트 관련
extern "C" {
#include "include/lua.h"
#include "include/lauxlib.h"
#include "include/lualib.h"
}

#pragma comment (lib, "lua54.lib")

using namespace std;
using namespace Concurrency;
using namespace chrono;

constexpr auto SCREENWIDTH = 9;
constexpr auto SCREENHEIGHT = 9;
constexpr int MAPWIDTH = 2000;
constexpr int MAPHEIGHT = 2000;
constexpr int ZONESIZE = 50;
constexpr int ZONE = MAPWIDTH / ZONESIZE * MAPHEIGHT / ZONESIZE;
constexpr int MAXUSER = 5000;
constexpr int MAXMONSTER = 200000;
constexpr int MAXMONSTERSPECIES = 3;

enum class MOVETYPE { UP, DOWN, LEFT, RIGHT };
enum class MONSTERTYPE { EASY, NORMAL, HARD };
enum class MONSTERSTATE { NONE, IDLE, CHASE, RETURN };
enum class EVENTTYPE { ACTIVE, RESPAWN, ATTACK };
enum class DBREQUESTTYPE { SAVE };

struct TIMER {
	int							activeID;
	EVENTTYPE					eventType;
	system_clock::time_point	actTime;

	bool operator<(const TIMER& other) const {
		return actTime > other.actTime;
	}
};

struct CHARACTERINFO {
	string						ID;
	string						PW;
	int							x, y;
	int							lv;
	int							exp;
	int							hp;
};

struct DBREQUEST {
	int							requestID;
	DBREQUESTTYPE				requestType;
	system_clock::time_point	actTime;
	bool						bCompulsory;
	CHARACTERINFO				characterInfo;

	bool operator<(const DBREQUEST& other) const {
		return actTime > other.actTime;
	}
};