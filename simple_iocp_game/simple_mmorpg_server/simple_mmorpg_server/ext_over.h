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
	int id;
public:
	EXT_OVER();
	EXT_OVER(char* protocol);
	~EXT_OVER();

	WSAOVERLAPPED& GetWSAOverlapped();
	WSABUF& GetWsabuf();
	char* GetSendBuf();

	OVER_TYPE GetOverType();
	void SetOverType(OVER_TYPE over_type);

	void SetID(int new_id);
};
