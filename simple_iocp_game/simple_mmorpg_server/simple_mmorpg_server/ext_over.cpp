#include "stdafx.h"
#include "ext_over.h"

EXT_OVER::EXT_OVER()
{
	wsabuf.len = BUF_SIZE;
	wsabuf.buf = send_buf;
	over_type = OVER_TYPE::RECV;
	ZeroMemory(&over, sizeof(over));
}

EXT_OVER::EXT_OVER(char* protocol)
{
	wsabuf.len = protocol[0];
	wsabuf.buf = send_buf;
	ZeroMemory(&over, sizeof(over));
	over_type = OVER_TYPE::SEND;
	memcpy(send_buf, protocol, protocol[0]);
}

EXT_OVER::~EXT_OVER()
{

}

WSAOVERLAPPED& EXT_OVER::GetWSAOverlapped()
{
	return over;
}

WSABUF& EXT_OVER::GetWsabuf()
{
	return wsabuf;
}

char* EXT_OVER::GetSendBuf() 
{
	return send_buf;
}

OVER_TYPE EXT_OVER::GetOverType()
{
	return over_type;
}

void EXT_OVER::SetOverType(OVER_TYPE type) 
{
	over_type = type;
}

void EXT_OVER::SetID(int new_id)
{
	id = new_id;
}
