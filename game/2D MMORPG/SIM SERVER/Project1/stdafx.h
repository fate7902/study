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

using namespace std;