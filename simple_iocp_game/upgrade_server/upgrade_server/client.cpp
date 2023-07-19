#include "stdafx.h"
#include "client.h"

void CLIENT::recv()
{
    DWORD recv_flag = 0;
    memset(&m_recvOver.wsaOver, 0, sizeof(m_recvOver.wsaOver));
    m_recvOver.wsaBuf.len = BUF_SIZE - m_prevRemainDataSize;
    m_recvOver.wsaBuf.buf = m_recvOver.sendBuf + m_prevRemainDataSize;
    WSARecv(m_socket, &m_recvOver.wsaBuf, 1, 0, &recv_flag, &m_recvOver.wsaOver, 0);
}
