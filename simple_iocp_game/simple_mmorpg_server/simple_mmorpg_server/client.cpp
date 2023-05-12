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

bool CLIENT::CalcDistance(const pair<int, int>& pos1, const pair<int, int>& pos2)
{
    int dx = pos1.first - pos2.first;
    int dy = pos1.second - pos2.second;
    return (dx * dx <= 4) && (dy * dy <= 4);
}

int CLIENT::GetID()
{
    return ID;
}

int CLIENT::GetPrevRemain()
{
    return prev_remain;
}

void CLIENT::SetID(int id)
{
    ID = id;
}

void CLIENT::AddViewlist(int id)
{
    viewlist.insert(id);
}

bool CLIENT::FindViewlist(int id)
{
    return viewlist.exist(id);
}

void CLIENT::RemoveViewlist(int id)
{
    viewlist.erase(id);
}

void CLIENT::SetPrevRemain(int val)
{
    prev_remain = val;
}

void CLIENT::SetSocket(SOCKET s)
{
    socket = s;
}

void CLIENT::clear()
{
    position = { 0 , 0 };
    ID = -1;
    prev_remain = 0;
    socket = NULL;
    viewlist.clear();
    use = false;
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

void CLIENT::send_login_info(CLIENT& cl)
{
    SC_LOGIN_PROTOCOL p;
    p.id = cl.GetID();
    p.x = position.load().first;
    p.y = position.load().second;
    p.size = sizeof(SC_LOGIN_PROTOCOL);
    p.type = SC_LOGIN;
    send(&p);
}

void CLIENT::send_move_info(CLIENT& cl, unsigned client_time)
{
    SC_MOVE_PROTOCOL p;
    p.id = cl.GetID();
    p.x = position.load().first;
    p.y = position.load().second;
    p.size = sizeof(SC_MOVE_PROTOCOL);
    p.type = SC_TRANS;
    p.client_time = client_time;    
    send(&p);
}

void CLIENT::send_add_object_info(CLIENT& cl)
{
    SC_ADD_OBJECT_PROTOCOL p;
    p.id = cl.GetID();
    p.x = cl.GetPosition().first;
    p.y = cl.GetPosition().second;
    p.size = sizeof(SC_ADD_OBJECT_PROTOCOL);
    p.type = SC_ADD_OBJECT;
    send(&p);
}

void CLIENT::send_remove_object_info(CLIENT& cl)
{
    SC_REMOVE_OBJECT_PROTOCOL p;
    p.id = cl.GetID();
    p.size = sizeof(SC_REMOVE_OBJECT_PROTOCOL);
    p.type = SC_REMOVE_OBJECT;
    send(&p);
}
