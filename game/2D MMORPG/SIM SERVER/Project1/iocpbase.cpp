#include "stdafx.h"
#include "iocpbase.h"

IocpBase::IocpBase(int port)
{
	m_port = port;
}

IocpBase::~IocpBase()
{
	closesocket(m_serverSock);
	WSACleanup();
}

void IocpBase::initialize()
{
	cout << "[Loading] IocpBase::initialize()\n";
	WSADATA WASData;
	int ret = WSAStartup(MAKEWORD(2, 2), &WASData);
	if (ret != 0) errorDisplay("WSAStartup Error : ", WSAGetLastError());

	m_serverSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_serverSock == INVALID_SOCKET) errorDisplay("Create Socket Error : ", WSAGetLastError());

	memset(&m_serverAddr, 0, sizeof(m_serverAddr));
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(m_port);
	m_serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	ret = bind(m_serverSock, reinterpret_cast<sockaddr*>(&m_serverAddr), sizeof(m_serverAddr));
	if (ret != 0) errorDisplay("bind Error : ", WSAGetLastError());

	ret = listen(m_serverSock, SOMAXCONN);
	if (ret != 0) errorDisplay("listen Error : ", WSAGetLastError());

	m_addrSize = sizeof(m_clientAddr);
	m_iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_serverSock), m_iocpHandle, 9999, 0);
}

void IocpBase::errorDisplay(const char* msg, int err_no)
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
