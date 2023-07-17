#include "stdafx.h"
#include "iocp.h"

void IOCP::Initialize()
{
	WSADATA WASData;
	int ret = WSAStartup(MAKEWORD(2, 2), &WASData);
	if (ret != 0) ErrorDisplay("WSAStartup Error : ", WSAGetLastError());

	serverSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	ret = bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
	if (ret != 0) ErrorDisplay("bind Error : ", WSAGetLastError());

	ret = listen(serverSocket, SOMAXCONN);
	if (ret != 0) ErrorDisplay("listen Error : ", WSAGetLastError());

	int addr_size = sizeof(clientAddr);

	iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(serverSocket), iocpHandle, 9999, 0);
	clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	acceptOver.overType = OVER_TYPE::ACCEPT;
	AcceptEx(serverSocket, clientSocket, acceptOver.sendBuf, 0, addr_size + 16, addr_size + 16, 0, &acceptOver.wsaOver);

	vector<thread> workerThreads;
	for (int i = 0; i < MAX_THREADS; ++i)
		workerThreads.emplace_back(&IOCP::Worker, this);
	for (auto& th : workerThreads)
		th.join();

	closesocket(serverSocket);
	WSACleanup();
}

void IOCP::Worker()
{
	while (true) {
		DWORD num_bytes;
		ULONG_PTR key;
		WSAOVERLAPPED* over = nullptr;
		bool bret = GetQueuedCompletionStatus(iocpHandle, &num_bytes, &key, &over, INFINITE);
		EXT_OVER* extOver = reinterpret_cast<EXT_OVER*>(over);
		if (bret == false) {
			if (OVER_TYPE::ACCEPT == extOver->overType)
				cout << "Accept Error\n";
			else {
				cout << "Logout on client[" << key << "]\n";
				// 해당 key 유저 로그아웃 처리 필요
				if (OVER_TYPE::SEND == extOver->overType) delete extOver;
				continue;
			}
		}

		// 각종 처리 필요
		switch (extOver->overType)
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

void IOCP::ErrorDisplay(const char* msg, int err)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	cout << msg;
	wcout << L"ERROR " << lpMsgBuf << "\n";
	LocalFree(lpMsgBuf);
}
