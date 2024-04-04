/*
* �̸� �����ϵ� ��� ���
* ���� �������� ������ ���� �ʴ� �κ�
*/

#pragma once
// ��Ʈ��ũ ���� ���
#include <WS2tcpip.h>
#include <MSWSock.h>
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "MSWSock.lib")

// �Ϲ����� ���
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

// ��� ��ũ��Ʈ ����
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

enum class MOVETYPE { UP, DOWN, LEFT, RIGHT };
enum class MONSTERTYPE { EASY, NORMAL, HARD };
enum class MONSTERSTATE { NONE, IDLE, CHASE, RETURN };
enum class EVENTTYPE { ACTIVE, RESPAWN, ATTACK };
