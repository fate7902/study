#include "stdafx.h"
#include "network.h"

void Network::initialize()
{
	m_status = m_socket.connect(SERVERIP, PORT);
	m_socket.setBlocking(false);
	if (m_status != Socket::Done) {
		cout << "서버와 연결할 수 없습니다.\n";
		while (true);
	}
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
	}
}
