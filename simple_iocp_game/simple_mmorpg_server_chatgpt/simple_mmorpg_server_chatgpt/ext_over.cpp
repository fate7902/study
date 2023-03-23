#include "stdafx.h"
#include "ext_over.h"

EXT_OVER::EXT_OVER() : wsabuf{ BUF_SIZE,  send_buf }, over{}, over_type{ OVER_TYPE::RECV }
{
	ZeroMemory(&over, sizeof(over));
}

WSAOVERLAPPED& EXT_OVER::GetWSAOverlapped()
{
	return over;
}

char* EXT_OVER::GetSendBuf()
{
	return send_buf;
}

OVER_TYPE EXT_OVER::GetOverType() const
{
	return over_type;
}

void EXT_OVER::SetOverType(const OVER_TYPE& type)
{
	over_type = type;
}
