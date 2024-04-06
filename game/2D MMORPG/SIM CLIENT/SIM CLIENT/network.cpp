#include "stdafx.h"
#include "network.h"

extern int g_x, g_y;

Network::~Network()
{
	delete[] m_otherPlayer;
	delete m_monster;
	delete m_monsterTexture;
}

void Network::initialize()
{
	m_status = m_socket.connect(SERVERIP, PORT);
	m_socket.setBlocking(false);
	if (m_status != Socket::Done) {
		cout << "서버와 연결할 수 없습니다.\n";
		while (true);
	}
	m_monster = new concurrent_unordered_map<int, Monster>;
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
	char ID[MAXIDLEN], PW[MAXPWLEN];
	cout << "아이디 : ";
	cin.getline(p.ID, MAXIDLEN);
	cout << "비밀번호 : ";
	cin.getline(p.PW, MAXPWLEN);
	sendPacket(&p);
}

void Network::sendMove(MOVETYPE moveType)
{
	CS_MOVE_REQUEST_PACKET p;
	p.size = sizeof(CS_MOVE_REQUEST_PACKET);
	p.type = CS_MOVE_REQUEST;
	p.moveType = static_cast<int>(moveType);
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
		SC_LOGIN_ALLOW_PACKET* p = reinterpret_cast<SC_LOGIN_ALLOW_PACKET*>(processedPacket);
		if (p->loginResult == static_cast<int>(LOGINRESULT::FAILED)) exit(1);
		m_player.setPosition(p->x, p->y);
		m_player.m_showing = true;
		m_player.m_id = p->key;
		m_id = p->key;
		g_x = m_player.m_x - 4;
		g_y = m_player.m_y - 4;
	}
	break;
	case SC_MOVE_ALLOW:
	{		
		SC_MOVE_ALLOW_PACKET* p = reinterpret_cast<SC_MOVE_ALLOW_PACKET*>(processedPacket);
		if (m_id == p->key) {
			m_player.setPosition(p->x, p->y);
			g_x = m_player.m_x - 4;
			g_y = m_player.m_y - 4;
		}
		else if(p->key < MAXUSER){
			m_otherPlayer[p->key].setPosition(p->x, p->y);
		}
		else {
			(*m_monster)[p->key].setPosition(p->x, p->y);
		}
	}
	break;
	case SC_ADDOBJECT_ALLOW:
	{
		//cout << "오브젝트 추가\n";
		SC_ADDOBJECT_ALLOW_PACKET* p = reinterpret_cast<SC_ADDOBJECT_ALLOW_PACKET*>(processedPacket);
		if (p->key < MAXUSER) {
			m_otherPlayer[p->key].setPosition(p->x, p->y);
			m_otherPlayer[p->key].m_id = p->key;
			m_otherPlayer[p->key].m_showing = true;
		}
		else {
			switch (static_cast<MONSTERTYPE>(p->monsterType))
			{
			case MONSTERTYPE::EASY: m_monster->insert(make_pair(p->key, Monster(*m_monsterTexture, 46, 66, 96, 90))); break;
			case MONSTERTYPE::NORMAL: m_monster->insert(make_pair(p->key, Monster(*m_monsterTexture, 142, 66, 100, 90))); break;
			case MONSTERTYPE::HARD: m_monster->insert(make_pair(p->key, Monster(*m_monsterTexture, 242, 66, 98, 90))); break;
			}
			(*m_monster)[p->key].setScale(0.5f, 0.5f);
			(*m_monster)[p->key].setPosition(p->x, p->y);
			(*m_monster)[p->key].m_id = p->key;
			(*m_monster)[p->key].m_type = static_cast<MONSTERTYPE>(p->monsterType);
			(*m_monster)[p->key].m_showing = true;
		}
	}
	break;
	case SC_DELETEOBJECT_ALLOW:
	{
		//cout << "오브젝트 삭제\n";
		SC_DELETEOBJECT_ALLOW_PACKET* p = reinterpret_cast<SC_DELETEOBJECT_ALLOW_PACKET*>(processedPacket);
		if (p->key < MAXUSER) {
			m_otherPlayer[p->key].m_showing = false;
		}
		else {
			m_monster->unsafe_erase(p->key);
		}
	}
	break;
	default: break;
	}
}
