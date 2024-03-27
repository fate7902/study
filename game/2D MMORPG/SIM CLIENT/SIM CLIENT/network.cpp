#include "stdafx.h"
#include "network.h"

Network::Network()
{
}

void Network::initialize()
{
	m_status = m_socket.connect(SERVERIP, PORT);
	m_socket.setBlocking(false);
	if (m_status != Socket::Done) {
		cout << "서버와 연결할 수 없습니다.\n";
		while (true);
	}
	sendLogin();
}

void Network::sendPacket(void* packet)
{
	unsigned char* p = reinterpret_cast<unsigned char*>(packet);
	size_t sent = 0;
	if (m_socket.send(packet, p[0], sent) != Socket::Done) {
		cout << "패킷 전송 실패!\n";
	}
}

void Network::sendLogin()
{
	CS_LOGIN_REQUEST_PACKET p;
	p.size = sizeof(CS_LOGIN_REQUEST_PACKET);
	p.type = CS_LOGIN_REQUEST;
	sendPacket(&p);
}

void Network::recv()
{
	char recvPacket[BUF];
	size_t	received;

	auto ret = m_socket.receive(recvPacket, BUF, received);
	if (ret == Socket::Error) {
		cout << "Recv 에러!";
		while (true);
	}
	if (ret != Socket::NotReady)
		if (received > 0) recvPacketChecking(recvPacket, received);
}

void Network::recvPacketChecking(char* recvPacket, size_t received)
{
	char* ptr = recvPacket;
	static size_t currentReceivedPacketSize = 0;
	static size_t savedPacketSize = 0;
	static char processedPacket[BUF];

	while (0 != received) {
		if (0 == currentReceivedPacketSize) currentReceivedPacketSize = ptr[0];
		if (received + savedPacketSize >= currentReceivedPacketSize) {
			memcpy(processedPacket + savedPacketSize, ptr, currentReceivedPacketSize - savedPacketSize);
			processPacket(processedPacket);
			ptr += currentReceivedPacketSize - savedPacketSize;
			received -= currentReceivedPacketSize - savedPacketSize;
			currentReceivedPacketSize = 0;
			savedPacketSize = 0;
		}
		else {
			memcpy(processedPacket + savedPacketSize, ptr, received);
			savedPacketSize += received;
			received = 0;
		}
	}
}

void Network::processPacket(char* processedPacket)
{
	switch (processedPacket[1])
	{
	// 패킷 처리
	case SC_LOGIN_ALLOW:
	{
		cout << "로그인 성공\n";
		SC_LOGIN_ALLOW_PACKET* p = reinterpret_cast<SC_LOGIN_ALLOW_PACKET*>(processedPacket);
		m_player->setPosition(p->x, p->y);
	}
	break;
	default: break;
	}
}
