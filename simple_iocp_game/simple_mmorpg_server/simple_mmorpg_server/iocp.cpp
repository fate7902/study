#include "stdafx.h"
#include "iocp.h"

IOCP::IOCP()
{
	
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
	while (true);
	LocalFree(lpMsgBuf);
}

void IOCP::worker()
{
	while (true) {
		DWORD num_bytes;
		ULONG_PTR key;
		WSAOVERLAPPED* over = nullptr;
		bool bret = GetQueuedCompletionStatus(handle_iocp, &num_bytes, &key, &over, INFINITE);
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

		// 각종 처리 필요
		switch (ext_over->GetOverType())
		{
		case OVER_TYPE::ACCEPT:
			break;
		case OVER_TYPE::RECV:
			break;
		case OVER_TYPE::SEND:
			break;
		}
	}
}

void IOCP::Initialize()
{
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
