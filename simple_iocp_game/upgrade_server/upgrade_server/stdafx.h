#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "MSWSock.lib")

#define Interface class

using namespace std;
using namespace concurrency;

constexpr int BUF_SIZE = 256;
constexpr int PORT = 4000;
constexpr int MAX_THREADS = 12;
constexpr int MAX_USER = 5000;
constexpr int MAX_MONSTER = 200000;
constexpr int NAME_SIZE = 10;
constexpr int MAP_WIDTH = 2000;
constexpr int MAP_HEIGHT = 2000;

enum class OVER_TYPE {ACCEPT, SEND, RECV};