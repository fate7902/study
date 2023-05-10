#pragma once
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <iostream>
#include <vector>
#include <thread>
#include "protocol.h"

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "MSWSock.lib")

using namespace std;

constexpr int MAX_USER = 5000;
constexpr int MAP_WIDTH = 2000;
constexpr int MAP_HEIGHT = 2000;

enum class OVER_TYPE {ACCEPT, SEND, RECV};
