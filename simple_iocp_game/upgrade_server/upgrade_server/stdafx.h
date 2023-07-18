#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <vector>
#include <thread>
#include <concurrent_queue.h>

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "MSWSock.lib")

#define Interface class

using namespace std;
using namespace concurrency;

constexpr int BUF_SIZE = 256;
constexpr int PORT = 4000;
constexpr int MAX_THREADS = 12;
constexpr int MAX_USER = 5000;

enum class OVER_TYPE {ACCEPT, SEND, RECV};