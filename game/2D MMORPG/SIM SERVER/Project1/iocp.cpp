#include "stdafx.h"
#include "iocp.h"

void Iocp::initialize()
{	
	cout << "[Loading] Iocp::initialize()\n";
	m_bZone = new atomic<bool>[ZONE];
	m_availableID = new concurrent_queue<int>;
	for (int i = 1; i <= MAXUSER; i++) m_availableID->push(i);

	IocpBase::initialize();

	m_clientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_extOver.m_overType = OVERTYPE::ACCEPT;
	AcceptEx(m_serverSock, m_clientSock, m_extOver.m_sendBuf, 0, m_addrSize + 16, m_addrSize + 16, 0, &m_extOver.m_wsaOver);

	vector<thread> workerThreads;
	thread timerThread{ &Iocp::timerWorker, this };
	for (int i = 0; i < MAXTHREAD; ++i)
		workerThreads.emplace_back(&Iocp::worker, this);
	for (auto& th : workerThreads)
		th.join();
	timerThread.join();
}

int Iocp::getIDAssignment()
{
	int id;
	if (m_availableID->try_pop(id)) return id;
	else return -1;
}

void Iocp::disconnect(int key)
{
	int zone = (*m_objectManager.m_player)[key].m_zone;
	m_objectManager.m_zoneMutex[zone].lock();
	m_objectManager.m_zone[zone].unsafe_erase(key);
	m_objectManager.m_zoneMutex[zone].unlock();
	delete &(*m_objectManager.m_player)[key];

	concurrent_unordered_set<int>* oldlist = (*m_objectManager.m_player)[key].m_viewlist;
	for (const auto& id : *oldlist) {
		(*m_objectManager.m_player)[id].m_viewlistMutex.lock();
		(*m_objectManager.m_player)[id].m_viewlist->unsafe_erase(key);
		(*m_objectManager.m_player)[id].m_viewlistMutex.unlock();
		(*m_objectManager.m_player)[id].sendDeleteObjectPacket(key);
	}
	cout << "Logout on client[" << key << "]\n";
	m_availableID->push(key);
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
			if (extOver->m_overType == OVERTYPE::ACCEPT)
				cout << "[�����߻�] ���� ����\n";
			else {				
				cout << "[�����߻�] GQCS ����\n";
				disconnect(static_cast<int>(key));
				if (extOver->m_overType == OVERTYPE::SEND) 
					delete extOver;
				continue;
			}
		}

		// ��Ŷ Ÿ�Կ� ���� ó�� �ʿ�
		processPacketIO(extOver, len, static_cast<int>(key));
	}
}

void Iocp::timerWorker()
{
	while (true) {
		TIMER timer;
		if (!m_timer.empty()) {
			m_timer.try_pop(timer);
			if (timer.actTime <= system_clock::now()) {
				processTimer(timer);
			}
			else {
				m_timer.push(timer);
				this_thread::sleep_for(10ms);
			}
		}
		else {
			this_thread::sleep_for(10ms);
		}
	}
}

void Iocp::processTimer(TIMER timer)
{
	auto timerExtendedOver = new ExtendedOverlapped;
	timerExtendedOver->m_activeID = timer.activeID;
	switch (timer.eventType)
	{
	case EVENTTYPE::ACTIVE:
	{
		timerExtendedOver->m_overType = OVERTYPE::MONSTERACTIVE;
	}
	break;
	case EVENTTYPE::RESPAWN:
	{
		timerExtendedOver->m_overType = OVERTYPE::MONSTERRESPAWN;
	}
	break;
	case EVENTTYPE::ATTACK:
	{
		timerExtendedOver->m_overType = OVERTYPE::MONSTERATTACK;
	}
	break;
	}
	PostQueuedCompletionStatus(m_iocpHandle, 1, timer.activeID, &timerExtendedOver->m_wsaOver);
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
			//cout << "[���Ӽ���] ����Ű �� : " << assignmentID << " ��� ���� ����!\n";
			m_objectManager.m_player->insert(make_pair(assignmentID, Player(assignmentID, 100)));
			(*m_objectManager.m_player)[assignmentID].initialize(m_clientSock);			
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_clientSock), m_iocpHandle, assignmentID, 0);
			(*m_objectManager.m_player)[assignmentID].asynRecv();
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
			disconnect(key);
			break;
		}
		int remainPacketData = len + (*m_objectManager.m_player)[key].m_reaminPacketData;
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
		(*m_objectManager.m_player)[key].m_reaminPacketData = remainPacketData;
		if (remainPacketData > 0) {
			memcpy(extOver->m_sendBuf, p, remainPacketData);
		}
		(*m_objectManager.m_player)[key].asynRecv();
	}
	break;
	case OVERTYPE::SEND:
	{
		if (len == 0) {
			disconnect(key);
			break;
		}
	}
	break;
	case OVERTYPE::MONSTERACTIVE: 
	{
		// ��� ��ũ��Ʈ ����Ͽ� ���� �̵� ���� �ʿ�
		lua_State* L = (*m_objectManager.m_monster)[key].m_luaState;
		switch ((*m_objectManager.m_monster)[key].m_monsterState) {
		case MONSTERSTATE::IDLE:
		{
			// ��Ȳ�̵� ���� �ʿ�
			lua_getglobal(L, "randomMove");
			lua_pushinteger(L, (*m_objectManager.m_monster)[key].m_x.load());
			lua_pushinteger(L, (*m_objectManager.m_monster)[key].m_y.load());
			if (lua_pcall(L, 2, 2, 0) != 0) {
				std::cerr << "[��� �Լ� ����] " << lua_tostring(L, -1) << "\n";
			}
			else {
				int nextX = lua_tointeger(L, -2);
				int nextY = lua_tointeger(L, -1);
				lua_pop(L, 2);
				(*m_objectManager.m_monster)[key].setPosition(nextX, nextY);
				(*m_objectManager.m_monster)[key].setZone();
				m_objectManager.checkMonsterZone((*m_objectManager.m_monster)[key].m_zone, key);
			}
		}
		break;
		case MONSTERSTATE::CHASE:
		{
			int targetID = (*m_objectManager.m_monster)[key].m_targetID;
			lua_getglobal(L, "findPath");
			lua_pushinteger(L, (*m_objectManager.m_monster)[key].m_x.load());
			lua_pushinteger(L, (*m_objectManager.m_monster)[key].m_y.load());
			lua_pushinteger(L, (*m_objectManager.m_player)[targetID].m_x.load());
			lua_pushinteger(L, (*m_objectManager.m_player)[targetID].m_y.load());
			if (lua_pcall(L, 4, 2, 0) != 0) {
				std::cerr << "[��� �Լ� ����] " << lua_tostring(L, -1) << "\n";
			}
			else {
				int nextX = lua_tointeger(L, -2);
				int nextY = lua_tointeger(L, -1);
				lua_pop(L, 2);
				(*m_objectManager.m_monster)[key].setPosition(nextX, nextY);
				(*m_objectManager.m_monster)[key].setZone();
				m_objectManager.checkMonsterZone((*m_objectManager.m_monster)[key].m_zone, key);
			}
			double distance = m_objectManager.calcInRange((*m_objectManager.m_monster)[key], (*m_objectManager.m_player)[key]);
			// �������� ����� ��� �̵�
			if (distance > CHASERANGE * CHASERANGE) {
				(*m_objectManager.m_monster)[key].m_monsterState = MONSTERSTATE::IDLE;
				(*m_objectManager.m_monster)[key].m_targetID = -1;
			}
			// ���ݹ��� �ȿ� ������ ����
			/*
			else if (distance < ATTACKRANGE * ATTACKRANGE) {
				TIMER timer;
				timer.activeID = key;
				timer.eventType = EVENTTYPE::ATTACK;
				timer.actTime = system_clock::now() + 1000ms;
				m_timer.push(timer);
				break;
			}
			*/
		}
		break;
		}

		// �̵�ó�� �� �ٽ� �̵� Ÿ�̸� ����
		TIMER timer;
		timer.activeID = key;
		timer.eventType = EVENTTYPE::ACTIVE;
		timer.actTime = system_clock::now() + 1000ms;
		m_timer.push(timer);
	}
	break;
	case OVERTYPE::MONSTERRESPAWN: 
	{
		int zoneNumber = (*m_objectManager.m_monster)[key].m_zone;
		(*m_objectManager.m_monster)[key].m_monsterState = MONSTERSTATE::IDLE;
		(*m_objectManager.m_monster)[key].m_targetID = -1;
		// ���� ������ ���� ���� �߰�
		m_objectManager.m_zone[zoneNumber].insert(key);
		// �߰��� ���Ͱ� ���̴� �������� ���� ���� ��Ŷ ����
		m_objectManager.checkMonsterZone(zoneNumber, key);

		// ���� Ÿ�Կ� ���� ���� �̵� ���� �ʿ�
		// EASY - ����, �񼱰� / NORMAL - ��Ȳ, �񼱰� / HARD - ��Ȳ, ����
		MONSTERTYPE monsterType = (*m_objectManager.m_monster)[key].m_monsterType;
		if (monsterType == MONSTERTYPE::HARD) {
			if ((*m_objectManager.m_monster)[key].m_targetID != -1) {
				(*m_objectManager.m_monster)[key].m_monsterState = MONSTERSTATE::CHASE;
			}
		}
		TIMER timer;
		timer.activeID = key;
		timer.eventType = EVENTTYPE::ACTIVE;
		timer.actTime = system_clock::now() + 1000ms;
		m_timer.push(timer);
	}
	break;
	case OVERTYPE::MONSTERATTACK:
	{
		// ���� ���� �߰� �ʿ�
	}
	break;
	default: cout << "[Unknowed Packet Error] check the over Type of packet. \n"; break;
	}
	delete extOver;
}

void Iocp::processPacket(char* packet, int key)
{
	switch (packet[1])
	{
	case CS_LOGIN_REQUEST:
	{
		//cout << "[�α��μ���] ����Ű �� : " << key << " ��� ���� �α��μ���!\n";
		CS_LOGIN_REQUEST_PACKET* p = reinterpret_cast<CS_LOGIN_REQUEST_PACKET*>(packet);
		(*m_objectManager.m_player)[key].setPosition(rand() % 2000, rand() % 2000);
		(*m_objectManager.m_player)[key].setZone();
		int zoneNumber = (*m_objectManager.m_player)[key].m_zone;		
		m_objectManager.m_zone[zoneNumber].insert(key);
		(*m_objectManager.m_player)[key].sendLoginAllowPacket();

		// ������ ������ ����, ������ ������ �þ�ó��
		// �ڽ��� ���� zone�� �� ������ zone�� ó��
		m_objectManager.checkPlayerZone(zoneNumber, key);

		// ������ ������ ���� �ش� ������ ó�� �湮�ϴ� ��� ���� ����
		checkFirstVisitZone(zoneNumber);
	}
	break;
	case CS_MOVE_REQUEST:
	{
		//cout << "[�̵�] ����Ű �� : " << key << " ��� ���� �̵�!\n";
		CS_MOVE_REQUEST_PACKET* p = reinterpret_cast<CS_MOVE_REQUEST_PACKET*>(packet);
		(*m_objectManager.m_player)[key].setPosition(static_cast<MOVETYPE>(p->moveType));		
		(*m_objectManager.m_player)[key].sendMoveAllowPacket((*m_objectManager.m_player)[key], p->clientTime);

		// ������ �̵����� ���� �þߺ�ȭó��
		// 1. �̵��� ������ zone ��ȭ Ȯ��
		int newZone = (*m_objectManager.m_player)[key].m_x.load() / ZONESIZE + ((*m_objectManager.m_player)[key].m_y.load() / ZONESIZE) * (MAPWIDTH / ZONESIZE);
		m_objectManager.changeZone(newZone, key);

		// 2. ������ viewlist�� �ִ� ������Ʈ�� �þ� ��Ȯ��
		m_objectManager.checkViewlist(key, p->clientTime);

		// 3. ���ӽÿ� ���������� ���� zone�� �����Ͽ� ���� ���̴� ���� �� ���� Ȯ��
		m_objectManager.checkPlayerZone(newZone, key);
		
		// ������ �̵��� ���� �ش� ������ ó�� �湮�ϴ� ��� ���� ����
		checkFirstVisitZone(newZone);
	}
	break;
	default: break;
	}
}

void Iocp::checkFirstVisitZone(int zoneNumber)
{
	bool expected = false;
	if (m_bZone[zoneNumber].compare_exchange_strong(expected, true)) {
		for (int i = MAXUSER; i < MAXUSER + MAXMONSTER; ++i) {
			if ((*m_objectManager.m_monster)[i].m_zone != zoneNumber) continue;
			TIMER timer;
			timer.activeID = i;
			timer.eventType = EVENTTYPE::RESPAWN;
			timer.actTime = system_clock::now() + 1000ms;
			m_timer.push(timer);
		}
	}
}
