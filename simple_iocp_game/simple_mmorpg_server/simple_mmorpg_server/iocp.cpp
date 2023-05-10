#include "stdafx.h"
#include "iocp.h"

IOCP::IOCP()
{
	for (int i = 0; i < MAX_USER; ++i) ID_list.emplace_back(i);
}

IOCP::~IOCP()
{

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
	return ID_list.empty();
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
				// 해당 key 유저 로그아웃 처리 필요
				if (OVER_TYPE::SEND == ext_over->GetOverType()) delete ext_over;
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
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(client_socket), handle_iocp, client_id, 0);
			clients[client_id].recv();
			client_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
		else {
			// 로그인 실패 관련 처리
		}
		ZeroMemory(&ext_over->GetWSAOverlapped(), sizeof(ext_over->GetWSAOverlapped()));		
		int addr_size = sizeof(SOCKADDR_IN);
		AcceptEx(server_socket, client_socket, ext_over->GetSendBuf(), 0, addr_size + 16, addr_size + 16, 0, &ext_over->GetWSAOverlapped());
		break;
	}
	case OVER_TYPE::RECV:
	{
		// 접속 종료 처리
		if (0 == len) { }
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
		break;
	}
}

void IOCP::ProtocolProcessing(const int& client_id, char* protocol)
{
	switch (protocol[1]) {
	case CS_LOGIN:
	{
		CS_LOGIN_PROTOCOL* p = reinterpret_cast<CS_LOGIN_PROTOCOL*>(protocol);
		cout << "[" << p->name << "] 님이 접속하셨습니다.\n";
		clients[client_id].SetPosition(0, 0);
		clients[client_id].send_login_info();
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
		clients[client_id].send_move_info();
		break;
	}
	}
}

void IOCP::Initialize(CLIENT* cl)
{
	clients = cl;

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
	for (auto& th : worker_threads)
		th.join();

	closesocket(server_socket);
	WSACleanup();
}
