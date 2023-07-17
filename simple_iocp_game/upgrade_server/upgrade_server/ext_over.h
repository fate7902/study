#pragma once
#include "stdafx.h"

class EXT_OVER
{
public:
	WSAOVERLAPPED wsaOver;
	WSABUF wsaBuf;
	char sendBuf[BUF_SIZE];
	OVER_TYPE overType;

public:
	EXT_OVER() {
		wsaBuf.len = BUF_SIZE;
		wsaBuf.buf = sendBuf;
		overType = OVER_TYPE::RECV;
		ZeroMemory(&wsaOver, sizeof(wsaOver));
	}
	~EXT_OVER() = default;
};
