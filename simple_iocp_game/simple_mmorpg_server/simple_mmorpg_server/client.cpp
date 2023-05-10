#include "stdafx.h"
#include "client.h"

CLIENT::CLIENT()
{
    position = { 0 , 0 };
    use = false;
}

CLIENT::~CLIENT()
{
}

bool CLIENT::GetUsing()
{
    return use.load();
}

void CLIENT::SetUsing(bool new_b)
{
    bool old_use = use.load();
    while (!use.compare_exchange_strong(old_use, new_b)) {
        old_use = use.load();
    }
}

pair<int, int> CLIENT::GetPosition()
{
    return position.load();
}

void CLIENT::SetPosition(int new_x, int new_y)
{
    pair<int, int> old_pos = position.load();
    pair<int, int> new_pos{ new_x, new_y };
    while (!position.compare_exchange_strong(old_pos, new_pos)) {
        old_pos = position.load();
    }
}

int CLIENT::GetPrevRemain()
{
    return 0;
}

void CLIENT::SetPrevRemain(int val)
{
    prev_remain = val;
}

void CLIENT::SetSocket(SOCKET s)
{
    socket = s;
}

void CLIENT::recv()
{
    DWORD recv_flag = 0;
    memset(&recv_over.GetWSAOverlapped(), 0, sizeof(recv_over.GetWSAOverlapped()));
    recv_over.GetWsabuf().len = BUF_SIZE - prev_remain;
    recv_over.GetWsabuf().buf = recv_over.GetSendBuf() + prev_remain;
    WSARecv(socket, &recv_over.GetWsabuf(), 1, 0, &recv_flag,
        &recv_over.GetWSAOverlapped(), 0);
}

void CLIENT::send(void* protocol)
{
    EXT_OVER* sdata = new EXT_OVER{ reinterpret_cast<char*>(protocol) };
    WSASend(socket, &sdata->GetWsabuf(), 1, 0, 0, &sdata->GetWSAOverlapped(), 0);
}

void CLIENT::send_login_info()
{
    SC_LOGIN_PROTOCOL p;
    p.x = position.load().first;
    p.y = position.load().second;
    p.size = sizeof(SC_LOGIN_PROTOCOL);
    p.type = SC_LOGIN;
    send(&p);
}

void CLIENT::send_move_info()
{
    SC_MOVE_PROTOCOL p;
    p.x = position.load().first;
    p.y = position.load().second;
    p.size = sizeof(SC_LOGIN_PROTOCOL);
    p.type = SC_TRANS;
    send(&p);
}
