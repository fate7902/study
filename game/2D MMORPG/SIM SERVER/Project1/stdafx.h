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
#include <atomic>
#include <mutex>

using namespace std;
using namespace Concurrency;

constexpr auto SCREENWIDTH = 9;
constexpr auto SCREENHEIGHT = 9;
constexpr int MAPWIDTH = 2000;
constexpr int MAPHEIGHT = 2000;
constexpr int ZONESIZE = 50;

enum class MOVETYPE { UP, DOWN, LEFT, RIGHT };