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
#include <atomic>

using namespace std;
using namespace Concurrency;

enum class MOVETYPE { UP, DOWN, LEFT, RIGHT };