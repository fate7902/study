#include "stdafx.h"
#include "iocp.h"

void Iocp::initialize()
{	
	cout << "[Loading] Iocp::initialize()\n";
	m_objectManager.m_zone = new concurrent_unordered_set<int>[ZONE];
	m_objectManager.m_zoneMutex = new mutex[ZONE];
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

void Iocp::disconnect(int key)
{
	int zone = m_objectManager.m_player[key].m_zone;
	m_objectManager.m_zoneMutex[zone].lock();
	m_objectManager.m_zone[zone].unsafe_erase(key);
	m_objectManager.m_zoneMutex[zone].unlock();

	concurrent_unordered_set<int> oldlist = m_objectManager.m_player[key].m_viewlist;
	for (const auto& id : oldlist) {
		m_objectManager.m_player[id].m_viewlistMutex.lock();
		m_objectManager.m_player[id].m_viewlist.unsafe_erase(key);
		m_objectManager.m_player[id].m_viewlistMutex.unlock();
		m_objectManager.m_player[id].sendDeleteObjectPacket(key);
	}
	cout << "Logout on client[" << key << "]\n";
	m_availableID.push(key);
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
				// 로그아웃 처리 필요
				disconnect(static_cast<int>(key));
				continue;
			}
		}

		// 패킷 타입에 따른 처리 필요
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
			//cout << "[접속성공] 고유키 값 : " << assignmentID << " 사용 유저 접속!\n";
			m_objectManager.m_player.insert(make_pair(assignmentID, Player(assignmentID, 100)));
			m_objectManager.m_player[assignmentID].initialize(m_clientSock);			
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_clientSock), m_iocpHandle, assignmentID, 0);
			m_objectManager.m_player[assignmentID].asynRecv();
			m_clientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
		else {
			cout << "접속 한계로인한 접속 불가.\n";
		}
		ZeroMemory(&m_extOver.m_wsaOver, sizeof(m_extOver.m_wsaOver));		
		m_addrSize = sizeof(SOCKADDR_IN);
		AcceptEx(m_serverSock, m_clientSock, m_extOver.m_sendBuf, 0, m_addrSize + 16, m_addrSize + 16, 0, &m_extOver.m_wsaOver);
	}
	break;
	case OVERTYPE::RECV: 
	{
		if (len == 0) {
			// 접속 끊기
			disconnect(key);
			break;
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
		//cout << "[로그인성공] 고유키 값 : " << key << " 사용 유저 로그인성공!\n";
		CS_LOGIN_REQUEST_PACKET* p = reinterpret_cast<CS_LOGIN_REQUEST_PACKET*>(packet);
		m_objectManager.m_player[key].setPosition(rand() % 2000, rand() % 2000);
		int zoneNumber = m_objectManager.m_player[key].m_zone;
		//cout << "[존 확인] 코유키 값 : " << key << " 사용 유저 존 넘버 : " << zoneNumber << "\n";
		m_objectManager.m_zone[zoneNumber].insert(key);
		m_objectManager.m_player[key].sendLoginAllowPacket();

		// 접속한 유저와 유저의 시야처리
		// 자신이 속한 zone과 그 주위의 zone만 처리
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				int currentZone = zoneNumber + x + (MAPWIDTH / ZONESIZE) * y;
				if (currentZone < 0 || currentZone > 399 || (currentZone % 19 == 0 && x == 1) || (currentZone % 20 == 0 && x == -1)) continue;
				m_objectManager.m_zoneMutex[currentZone].lock();
				concurrent_unordered_set<int> copylist = m_objectManager.m_zone[currentZone];
				m_objectManager.m_zoneMutex[currentZone].unlock();
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

		// 접속한 유저와 몬스터의 시야처리 필요
	}
	break;
	case CS_MOVE_REQUEST:
	{
		//cout << "[이동] 고유키 값 : " << key << " 사용 유저 이동!\n";
		CS_MOVE_REQUEST_PACKET* p = reinterpret_cast<CS_MOVE_REQUEST_PACKET*>(packet);
		m_objectManager.m_player[key].setPosition(static_cast<MOVETYPE>(p->moveType));		
		m_objectManager.m_player[key].sendMoveAllowPacket(m_objectManager.m_player[key], p->clientTime);

		// 유저의 이동으로 인한 유저와의 시야변화처리
		// 1. 이동한 유저의 zone 변화 확인
		int newZone = m_objectManager.m_player[key].m_x.load() / ZONESIZE + (m_objectManager.m_player[key].m_y.load() / ZONESIZE) * (MAPWIDTH / ZONESIZE);
		if (m_objectManager.m_player[key].m_zone != newZone) {
			int oldZone = m_objectManager.m_player[key].m_zone;
			m_objectManager.m_zoneMutex[oldZone].lock();
			m_objectManager.m_zone[oldZone].unsafe_erase(key);
			m_objectManager.m_zoneMutex[oldZone].unlock();
			m_objectManager.m_player[key].m_zone = newZone;
			m_objectManager.m_zone[newZone].insert(key);
		}
		// 2. 기존의 viewlist에 있던 오브젝트와 거리 재확인
		concurrent_unordered_set<int> oldlist = m_objectManager.m_player[key].m_viewlist;
		for (const auto& id : oldlist) {
			if (!m_objectManager.calcInRange(m_objectManager.m_player[key], m_objectManager.m_player[id])) {
				// 이동 유저의 viewlist 처리
				m_objectManager.m_player[key].m_viewlistMutex.lock();
				m_objectManager.m_player[key].m_viewlist.unsafe_erase(id);
				m_objectManager.m_player[key].m_viewlistMutex.unlock();
				m_objectManager.m_player[key].sendDeleteObjectPacket(id);

				// 처리한 유저의 viewlist 처리
				m_objectManager.m_player[id].m_viewlistMutex.lock();
				m_objectManager.m_player[id].m_viewlist.unsafe_erase(key);
				m_objectManager.m_player[id].m_viewlistMutex.unlock();
				m_objectManager.m_player[id].sendDeleteObjectPacket(key);
			}
			else {
				m_objectManager.m_player[id].sendMoveAllowPacket(m_objectManager.m_player[key], p->clientTime);
			}
		}
		// 3. 접속시와 마찬가지로 주위 zone을 포함하여 새로 보이는 유저 확인
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				int currentZone = newZone + x + (MAPWIDTH / ZONESIZE) * y;
				if (currentZone < 0 || currentZone > 399 || (currentZone % 19 == 0 && x == 1) || (currentZone % 20 == 0 && x == -1)) continue;
				m_objectManager.m_zoneMutex[currentZone].lock();
				concurrent_unordered_set<int> copylist = m_objectManager.m_zone[currentZone];
				m_objectManager.m_zoneMutex[currentZone].unlock();
				for (const auto& id : copylist) {
					if (id == key) continue;
					if (!m_objectManager.calcInRange(m_objectManager.m_player[key], m_objectManager.m_player[id])) continue;
					if (m_objectManager.m_player[key].m_viewlist.find(id) != m_objectManager.m_player[key].m_viewlist.end()) continue;
					m_objectManager.m_player[key].m_viewlist.insert(id);
					m_objectManager.m_player[key].sendAddObjectPacket(m_objectManager.m_player[id]);
					m_objectManager.m_player[id].m_viewlist.insert(key);
					m_objectManager.m_player[id].sendAddObjectPacket(m_objectManager.m_player[key]);
				}
			}
		}
		
		// 유저의 이동으로 인한 몬스터와의 시야변화처리 필요
	}
	break;
	default: break;
	}
}
