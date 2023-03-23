#include "stdafx.h"
#include "ext_over.h"

EXT_OVER::EXT_OVER()
{
	wsabuf.len = BUF_SIZE;
	wsabuf.buf = send_buf;
	over_type = OVER_TYPE::RECV;
	ZeroMemory(&over, sizeof(over));
}

EXT_OVER::~EXT_OVER()
{

}

WSAOVERLAPPED& EXT_OVER::GetWSAOverlapped()
{
	return over;
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
