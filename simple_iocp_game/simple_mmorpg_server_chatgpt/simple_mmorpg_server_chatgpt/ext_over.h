#pragma once
#include "stdafx.h"

constexpr int BUF_SIZE = 256;

class EXT_OVER
{
private:
	WSAOVERLAPPED over;
	WSABUF wsabuf;
	char send_buf[BUF_SIZE];
	OVER_TYPE over_type;

public:
	EXT_OVER();
	~EXT_OVER() = default;

	WSAOVERLAPPED& GetWSAOverlapped();
	char* GetSendBuf();

	OVER_TYPE GetOverType() const;
	void SetOverType(const OVER_TYPE& over_type);
};
