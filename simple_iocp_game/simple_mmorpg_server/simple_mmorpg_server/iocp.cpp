#include "stdafx.h"
#include "iocp.h"

IOCP::IOCP()
{	
	ID_list = new LFVEC();
	for (int i = 0; i < MAX_USER; ++i) ID_list->emplace_back(i);
}

IOCP::~IOCP()
{
	delete clients;
	delete ID_list;
}

void IOCP::Error_Display(const char* msg, int err_no)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	cout << msg;
	wcout << L"ERROR " << lpMsgBuf << "\n";
	LocalFree(lpMsgBuf);
}

int IOCP::GetClientID()
{
	return ID_list->empty();
}

void IOCP::Disconnect(int id)
{
	for (int i = 0; i < MAX_USER; ++i) {
		if (clients[i].GetUsing() == false) continue;
		if (i == id) continue;
		if (!clients[i].FindViewlist(id)) continue;
		clients[i].RemoveViewlist(id);
		clients[i].send_remove_object_info(clients[id]);
	}
	clients[id].clear();
	ID_list->emplace_back(id);
}

void IOCP::worker()
{	
	while (true) {
		DWORD len;
		ULONG_PTR key;
		WSAOVERLAPPED* over = nullptr;
		bool bret = GetQueuedCompletionStatus(handle_iocp, &len, &key, &over, INFINITE);
		EXT_OVER* ext_over = reinterpret_cast<EXT_OVER*>(over);		
		if (bret == false) {
			if (OVER_TYPE::ACCEPT == ext_over->GetOverType())
				cout << "Accept Error\n";
			else {
				cout << "Logout on client[" << key << "]\n";			
				Disconnect(key);				
				if (OVER_TYPE::SEND == ext_over->GetOverType()) {
					delete ext_over->GetWsabuf().buf;
					delete ext_over;
				}
				continue;
			}			
		}
		DataProcessing(ext_over, key, len);		
	}	
}

void IOCP::DataProcessing(EXT_OVER*& ext_over, const ULONG_PTR& key, const DWORD& len)
{
	// 각종 처리 필요
	switch (ext_over->GetOverType())
	{
	case OVER_TYPE::ACCEPT:
	{
		int client_id = GetClientID();
		if (client_id != -1) {
			cout << "Client [" << client_id << "번] 님이 입장하셨습니다.\n";						
			clients[client_id].SetPrevRemain(0);
			clients[client_id].SetSocket(client_socket);
			clients[client_id].SetID(client_id);
			clients[client_id].SetUsing(true);
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(client_socket), handle_iocp, client_id, 0);
			clients[client_id].recv();
			client_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
		else {
			// 로그인 실패 관련 처리			
			client_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
		ZeroMemory(&ext_over->GetWSAOverlapped(), sizeof(ext_over->GetWSAOverlapped()));		
		int addr_size = sizeof(SOCKADDR_IN);
		AcceptEx(server_socket, client_socket, ext_over->GetSendBuf(), 0, addr_size + 16, addr_size + 16, 0, &ext_over->GetWSAOverlapped());
		break;
	}
	case OVER_TYPE::RECV:
	{
		// 접속 종료 처리
		if (0 == len) { 
			cout << "A Logout on client[" << key << "]\n";
			Disconnect(key);
			break;
		}
		int remain_data = len + clients[key].GetPrevRemain();
		char* p = ext_over->GetSendBuf();
		int protocol_size = p[0];
		while (remain_data > 0 && protocol_size <= remain_data) {
			ProtocolProcessing(static_cast<int>(key), p);
			p = p + protocol_size;
			remain_data = remain_data - protocol_size;
		}
		clients[key].SetPrevRemain(remain_data);
		if (remain_data > 0) {
			memcpy(ext_over->GetSendBuf(), p, remain_data);
		}
		clients[key].recv();
		break;
	}
	case OVER_TYPE::SEND:
	{
		// 접속 종료 처리
		if (0 == len) {
			cout << "B Logout on client[" << key << "]\n";
			Disconnect(key);
		}
		delete ext_over;
		break;
	}
	case OVER_TYPE::MONSTER_MOVE:
	{
		auto L = monsters[key].GetLua();
		lua_getglobal(L, "TESTmove");
		lua_pcall(L, 0, 0, 0);
		lua_getglobal(L, "monster");
		lua_getfield(L, -1, "x");
		lua_getfield(L, -2, "y");
		int x = lua_tointeger(L, -2);
		int y = lua_tointeger(L, -1);
		lua_pop(L, 2);
		monsters[key].SetPosition(x, y);
		auto p = monsters[key].GetPosition();
		//cout << p.first << ", " << p.second << "\n";

		TIMER_EVENT k;
		k.ev = EVENT_TYPE::EV_MOVE;
		k.monster_id = key;
		k.act_time = system_clock::now() + 1000ms;		
		timer_queue.emplace(k);		

		delete ext_over;
		break;
	}
	}
}

void IOCP::ProtocolProcessing(const int& client_id, char* protocol)
{
	switch (protocol[1]) {
	case CS_LOGIN:
	{
		CS_LOGIN_PROTOCOL* p = reinterpret_cast<CS_LOGIN_PROTOCOL*>(protocol);
		cout << "[" << p->name << "] 님이 접속하셨습니다.\n";
		clients[client_id].SetPosition(rand() % 2000, rand() % 2000);
		clients[client_id].send_login_info(clients[client_id]);

		// 로그인한 유저와 이미 접속중인 유저간의 거리측정을 통해
		// 서로의 시야 안에 있는 지 측정 후 리스트 저장
		pair<int, int> pos = clients[client_id].GetPosition();
		for (int i = 0; i < MAX_USER; ++i) {
			if (clients[i].GetUsing() == false) continue;
			if (i == client_id) continue;
			if(!clients[client_id].CalcDistance(pos, clients[i].GetPosition())) continue;
			clients[client_id].AddViewlist(i);
			clients[i].AddViewlist(client_id);
			// 서로에게 해당 정보 전송
			clients[client_id].send_add_object_info(clients[i]);
			clients[i].send_add_object_info(clients[client_id]);
		}
		break;
	}
	case CS_MOVE:
	{
		CS_MOVE_PROTOCOL* p = reinterpret_cast<CS_MOVE_PROTOCOL*>(protocol);
		pair<int, int> old_pos = clients[client_id].GetPosition();
		switch (p->move_type) {
		case MOVE_TYPE::LEFT:
			if (old_pos.first - 1 >= 0) clients[client_id].SetPosition(old_pos.first - 1, old_pos.second);
			break;
		case MOVE_TYPE::RIGHT:
			if (old_pos.first + 1 <= MAP_WIDTH) clients[client_id].SetPosition(old_pos.first + 1, old_pos.second);
			break;
		case MOVE_TYPE::UP:
			if (old_pos.second - 1 >= 0) clients[client_id].SetPosition(old_pos.first, old_pos.second - 1);
			break;
		case MOVE_TYPE::DOWN:
			if (old_pos.second + 1 <= MAP_HEIGHT) clients[client_id].SetPosition(old_pos.first, old_pos.second + 1);
			break;
		}
		clients[client_id].send_move_info(clients[client_id], p->client_time);

		// 변화한 위치 값으로 인한 시야 범위 재측정
		pair<int, int> pos = clients[client_id].GetPosition();
		// 새로 시야에 들어오는 지 확인
		for (int i = 0; i < MAX_USER; ++i) {
			if (clients[i].GetUsing() == false) continue;
			if (i == client_id) continue;
			if (!clients[client_id].CalcDistance(pos, clients[i].GetPosition())) continue;
			clients[client_id].AddViewlist(i);
			clients[i].AddViewlist(client_id);
			// 서로에게 해당 정보 전송
			clients[client_id].send_add_object_info(clients[i]);
			clients[i].send_add_object_info(clients[client_id]);
		}
		// 시야에서 벗어나는 지 확인
		for (int i = 0; i < MAX_USER; ++i) {
			if (clients[i].GetUsing() == false) continue;
			if (i == client_id) continue;
			if (!clients[client_id].FindViewlist(i)) continue;
			if (!clients[client_id].CalcDistance(pos, clients[i].GetPosition())) {
				clients[client_id].RemoveViewlist(i);
				clients[i].RemoveViewlist(client_id);
				// 서로에게 해당 정보 전송
				clients[client_id].send_remove_object_info(clients[i]);
				clients[i].send_remove_object_info(clients[client_id]);
			}
		}		
		break;
	}
	}
}

void IOCP::Initialize(CLIENT* cl, MONSTER* ms)
{
	clients = cl;
	monsters = ms;
	Monster_Initialize();
	
	WSADATA WASData;
	ret = WSAStartup(MAKEWORD(2, 2), &WASData);
	if (ret != 0) Error_Display("WSAStartup Error : ", WSAGetLastError());
	
	server_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_NUM);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	ret = bind(server_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	if (ret != 0) Error_Display("bind Error : ", WSAGetLastError());
	
	ret = listen(server_socket, SOMAXCONN);
	if (ret != 0) Error_Display("listen Error : ", WSAGetLastError());
	
	int addr_size = sizeof(client_addr);	
	
	handle_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(server_socket), handle_iocp, 9999, 0);
	client_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	accept_over.SetOverType(OVER_TYPE::ACCEPT);	
	AcceptEx(server_socket, client_socket, accept_over.GetSendBuf(), 0, addr_size + 16, addr_size + 16, 0, &accept_over.GetWSAOverlapped());
	
	vector<thread> worker_threads;
	for (int i = 0; i < THREADS_NUM; ++i)
		worker_threads.emplace_back(&IOCP::worker, this);
	thread monster_thread{ &IOCP::Monster_Thread, this };
	monster_thread.join();
	thread timer_thread{ &IOCP::do_timer, this };
	timer_thread.join();
	for (auto& th : worker_threads)
		th.join();

	closesocket(server_socket);
	WSACleanup();
}

void IOCP::Monster_Thread() {
	for (int i = MAX_USER; i < MAX_USER + MAX_MONSTER; ++i) {		
		TIMER_EVENT k;
		k.ev = EVENT_TYPE::EV_MOVE;
		k.monster_id = i;
		k.act_time = system_clock::now() + 1000ms;
		timer_queue.emplace(k);
	}
}

void IOCP::process_event(TIMER_EVENT k)
{
	switch (k.ev) {
	case EVENT_TYPE::EV_MOVE:
	{
		auto ext_over = new EXT_OVER;
		ext_over->SetOverType(OVER_TYPE::MONSTER_MOVE);
		ext_over->SetID(k.monster_id);
		PostQueuedCompletionStatus(handle_iocp, 1, k.monster_id, &ext_over->GetWSAOverlapped());
		break;
	}
	}
}

void IOCP::do_timer()
{
	while (true) {
		TIMER_EVENT k;

		if (timer_queue.pop(k)) {
			process_event(k);
		}
		else {
			this_thread::sleep_for(10ms);
		}
	}
}

void IOCP::Monster_Initialize()
{
	cout << "Monster intialization begin.\n";
	for (int i = MAX_USER; i < MAX_USER + MAX_MONSTER; ++i) {
		monsters[i].SetID(i);
		monsters[i].SetPosition(rand() % 2000, rand() % 2000);
		lua_State* L = luaL_newstate();
		monsters[i].SetLua(L);

		luaL_openlibs(L);
		if (luaL_dofile(L, "monsterAI.lua") != LUA_OK) {
			printf("Failed to load Lua script: %s\n", lua_tostring(L, -1));
			lua_close(L);
		}
		else {			
			lua_getglobal(L, "SetPosition");
			auto pos = monsters[i].GetPosition();
			//cout << pos.first << ", " << pos.second << "\n";
			lua_pushnumber(L, pos.first);
			lua_pushnumber(L, pos.second);
			if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
				std::cerr << "Failed to call SetPosition: " << lua_tostring(L, -1) << std::endl;
				lua_close(L);				
			}
			else {
				lua_getglobal(L, "monster");
				lua_getfield(L, -1, "x");
				lua_getfield(L, -2, "y");
				int x = lua_tointeger(L, -2);
				int y = lua_tointeger(L, -1);
				lua_pop(L, 2);
				//cout << x << ", " << y << "\n";
			}
		}
	}
	cout << "NPC initialization complete\n";
}