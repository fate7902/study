#include "stdafx.h"
#include "iocp.h"

void Iocp::initialize()
{	
	cout << "[Loading] Iocp::initialize()\n";

	for (int i = 1; i <= MAXUSER; i++) m_availableID.push(i);

	IocpBase::initialize();

	m_clientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_extOver.m_overType = OVERTYPE::ACCEPT;
	AcceptEx(m_serverSock, m_clientSock, m_extOver.m_sendBuf, 0, m_addrSize + 16, m_addrSize + 16, 0, &m_extOver.m_wsaOver);

	vector<thread> worker_threads;
	for (int i = 0; i < MAXTHREAD; ++i)
		worker_threads.emplace_back(&Iocp::worker, this);	
	for (auto& th : worker_threads)
		th.join();
}

int Iocp::getIDAssignment()
{
	int id;
	if (m_availableID.try_pop(id)) return id;
	else return -1;
}

void Iocp::worker()
{
	while (true) {
		DWORD len;
		ULONG_PTR key;
		WSAOVERLAPPED* wsaOver = nullptr;
		bool bret = GetQueuedCompletionStatus(m_iocpHandle, &len, &key, &wsaOver, INFINITE);
		ExtendedOverlapped* extOver = reinterpret_cast<ExtendedOverlapped*>(wsaOver);
		if (bret == false) {
			if (OVERTYPE::ACCEPT == extOver->m_overType)
				cout << "Accept Error\n";
			else {
				cout << "Logout on client[" << key << "]\n";
				// �α׾ƿ� ó�� �ʿ�
				continue;
			}
		}

		// ��Ŷ Ÿ�Կ� ���� ó�� �ʿ�
		processPacketIO(extOver, len, static_cast<int>(key));
	}
}

void Iocp::processPacketIO(ExtendedOverlapped*& extOver, DWORD len, int key)
{
	switch (extOver->m_overType)
	{
	case OVERTYPE::ACCEPT:
	{
		//SOCKET clientSocket = reinterpret_cast<SOCKET>(extOver->m_wsaBuf.buf);
		int assignmentID = getIDAssignment();
		if (assignmentID != -1) {
			cout << "[���Ӽ���] ����Ű �� : " << assignmentID << " ��� ���� ����!\n";
			m_objectManager.m_player.insert(make_pair(assignmentID, Player(assignmentID, 100)));
			m_objectManager.m_player[assignmentID].initialize(m_clientSock);			
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_clientSock), m_iocpHandle, assignmentID, 0);
			m_objectManager.m_player[assignmentID].asynRecv();
			m_clientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
		else {
			cout << "���� �Ѱ������ ���� �Ұ�.\n";
		}
		ZeroMemory(&m_extOver.m_wsaOver, sizeof(m_extOver.m_wsaOver));		
		m_addrSize = sizeof(SOCKADDR_IN);
		AcceptEx(m_serverSock, m_clientSock, m_extOver.m_sendBuf, 0, m_addrSize + 16, m_addrSize + 16, 0, &m_extOver.m_wsaOver);
	}
	break;
	case OVERTYPE::RECV: 
	{
		if (len == 0) {
			// ���� ����
		}
		int remainPacketData = len + m_objectManager.m_player[key].m_reaminPacketData;
		char* p = extOver->m_sendBuf;
		while (remainPacketData > 0) {
			int packetSize = p[0];
			if (packetSize <= remainPacketData) {
				processPacket(p, key);
				p = p + packetSize;
				remainPacketData = remainPacketData - packetSize;
			}
			else break;
		}
		m_objectManager.m_player[key].m_reaminPacketData = remainPacketData;
		if (remainPacketData > 0) {
			memcpy(extOver->m_sendBuf, p, remainPacketData);
		}
		m_objectManager.m_player[key].asynRecv();
	}
	break;
	case OVERTYPE::SEND: break;
	default: cout << "[Unknowed Packet Error] check the over Type of packet. \n"; break;
	}
}

void Iocp::processPacket(char* packet, int key)
{
	switch (packet[1])
	{
	case CS_LOGIN_REQUEST:
	{
		cout << "[�α��μ���] ����Ű �� : " << key << " ��� ���� �α��μ���!\n";
		CS_LOGIN_REQUEST_PACKET* p = reinterpret_cast<CS_LOGIN_REQUEST_PACKET*>(packet);
		m_objectManager.m_player[key].setPosition(rand() % 8, rand() % 8);
		int zoneNumber = m_objectManager.m_player[key].m_zone;		
		m_objectManager.m_zone[zoneNumber].insert(key);
		m_objectManager.m_player[key].sendLoginAllowPacket();

		// ������ ������ ������ �þ�ó��
		// �ڽ��� ���� zone�� �� ������ zone�� ó��
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				int currentZone = zoneNumber + x + (MAPWIDTH / 50) * y;
				if (currentZone < 0) continue;
				concurrent_unordered_set<int> copylist = m_objectManager.m_zone[currentZone];
				for (const auto& id : copylist) {
					if (id == key) continue;
					if (!m_objectManager.calcInRange(m_objectManager.m_player[key], m_objectManager.m_player[id])) continue;
					m_objectManager.m_player[key].m_viewlist.insert(id);
					m_objectManager.m_player[key].sendAddObjectPacket(m_objectManager.m_player[id]);
					m_objectManager.m_player[id].m_viewlist.insert(key);
					m_objectManager.m_player[id].sendAddObjectPacket(m_objectManager.m_player[key]);
				}
			}
		}		

		// ������ ������ ������ �þ�ó�� �ʿ�
	}
	break;
	case CS_MOVE_REQUEST:
	{
		cout << "[�̵�] ����Ű �� : " << key << " ��� ���� �̵�!\n";
		CS_MOVE_REQUEST_PACKET* p = reinterpret_cast<CS_MOVE_REQUEST_PACKET*>(packet);
		m_objectManager.m_player[key].setPosition(static_cast<MOVETYPE>(p->moveType));		
		m_objectManager.m_player[key].sendMoveAllowPacket();

		// ������ �̵����� ���� �������� �þߺ�ȭó��
		// 1. �̵��� ������ zone ��ȭ Ȯ��
		int newZone = m_objectManager.m_player[key].m_x.load() % 50 + (m_objectManager.m_player[key].m_y.load() % 50) * (MAPWIDTH / 50);
		if (m_objectManager.m_player[key].m_zone != newZone) {
			int oldZone = m_objectManager.m_player[key].m_zone;
			m_objectManager.m_zoneMutex[oldZone].lock();
			m_objectManager.m_zone[oldZone].unsafe_erase(key);
			m_objectManager.m_zoneMutex[oldZone].unlock();
			m_objectManager.m_player[key].m_zone = newZone;
			m_objectManager.m_zone[newZone].insert(key);
		}
		// 2. ������ viewlist�� �ִ� ������Ʈ�� �Ÿ� ��Ȯ��
		concurrent_unordered_set<int> oldlist = m_objectManager.m_player[key].m_viewlist;
		for (const auto& id : oldlist) {
			if (m_objectManager.calcInRange(m_objectManager.m_player[key], m_objectManager.m_player[id])) continue;
			// �̵� ������ viewlist ó��
			m_objectManager.m_player[key].m_viewlistMutex.lock();
			m_objectManager.m_player[key].m_viewlist.unsafe_erase(id);
			m_objectManager.m_player[key].m_viewlistMutex.unlock();
			m_objectManager.m_player[key].sendDeleteObjectPacket(id);

			// ó���� ������ viewlist ó��
			m_objectManager.m_player[id].m_viewlistMutex.lock();
			m_objectManager.m_player[id].m_viewlist.unsafe_erase(key);
			m_objectManager.m_player[id].m_viewlistMutex.unlock();
			m_objectManager.m_player[id].sendDeleteObjectPacket(key);
		}
		// 3. ���ӽÿ� ���������� ���� zone�� �����Ͽ� ���� ���̴� ���� Ȯ��
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				int currentZone = newZone + x + (MAPWIDTH / 50) * y;
				if (currentZone < 0) continue;
				concurrent_unordered_set<int> copylist = m_objectManager.m_zone[currentZone];
				for (const auto& id : copylist) {
					if (id == key) continue;
					if (!m_objectManager.calcInRange(m_objectManager.m_player[key], m_objectManager.m_player[id])) continue;
					if (m_objectManager.m_player[key].m_viewlist.find(id) == m_objectManager.m_player[key].m_viewlist.end()) continue;
					m_objectManager.m_player[key].m_viewlist.insert(id);
					m_objectManager.m_player[key].sendAddObjectPacket(m_objectManager.m_player[id]);
					m_objectManager.m_player[id].m_viewlist.insert(key);
					m_objectManager.m_player[id].sendAddObjectPacket(m_objectManager.m_player[key]);
				}
			}
		}
		
		// ������ �̵����� ���� ���Ϳ��� �þߺ�ȭó�� �ʿ�
	}
	break;
	default: break;
	}
}
