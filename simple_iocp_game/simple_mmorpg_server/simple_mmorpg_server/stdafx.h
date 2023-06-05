#pragma once
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include "protocol.h"

extern "C" {
#include "include/lua.h"
#include "include/lauxlib.h"
#include "include/lualib.h"
}
#pragma comment (lib, "lua54.lib")
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "MSWSock.lib")

using namespace std;
using namespace chrono;

constexpr int MAX_USER = 5000;
constexpr int MAX_MONSTER = 100;
constexpr int MAP_WIDTH = 2000;
constexpr int MAP_HEIGHT = 2000;

enum class OVER_TYPE { ACCEPT, SEND, RECV, MONSTER_MOVE };
enum class EVENT_TYPE { EV_MOVE };
