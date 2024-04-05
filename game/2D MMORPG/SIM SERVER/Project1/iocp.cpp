#include "stdafx.h"
#include "iocp.h"

Iocp::~Iocp()
{
	delete m_availableID;
}

void Iocp::initialize()
{	
	cout << "[Loading] Iocp::initialize()\n";
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
	cout << "[Finished] Iocp::initialize()\n";
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
				cout << "[오류발생] 접속 오류\n";
			else {				
				cout << "[오류발생] GQCS 오류\n";
				disconnect(static_cast<int>(key));
				if (extOver->m_overType == OVERTYPE::SEND) 
					delete extOver;
				continue;
			}
		}

		// 패킷 타입에 따른 처리 필요
		processPacketIO(extOver, len, static_cast<int>(key));
	}
}

void Iocp::timerWorker()
{
	while (true) {
		TIMER timer;
		if (!m_objectManager.m_timer.empty()) {
			m_objectManager.m_timer.try_pop(timer);
			if (timer.actTime <= system_clock::now()) {
				processTimer(timer);
			}
			else {
				m_objectManager.m_timer.push(timer);
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
			//cout << "[접속성공] 고유키 값 : " << assignmentID << " 사용 유저 접속!\n";
			m_objectManager.m_player->insert(make_pair(assignmentID, Player(assignmentID, 100)));
			(*m_objectManager.m_player)[assignmentID].initialize(m_clientSock);			
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_clientSock), m_iocpHandle, assignmentID, 0);
			(*m_objectManager.m_player)[assignmentID].asynRecv();
		}
		else {
			cout << "접속 한계로인한 접속 불가.\n";
		}
		m_clientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
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
			delete extOver;
			break;
		}
	}
	break;
	case OVERTYPE::MONSTERACTIVE: 
	{
		// 루아 스크립트 사용하여 몬스터 이동 구현
		int monsterSpecies = static_cast<int>((*m_objectManager.m_monster)[key].m_monsterType);
		lua_State* L = m_objectManager.m_luaState[monsterSpecies];
		m_objectManager.m_luaMutex[monsterSpecies].lock();
		switch ((*m_objectManager.m_monster)[key].m_monsterState) {
		case MONSTERSTATE::IDLE:
		{
			// 방황이동
			lua_getglobal(L, "randomMove");
			lua_pushinteger(L, (*m_objectManager.m_monster)[key].m_x.load());
			lua_pushinteger(L, (*m_objectManager.m_monster)[key].m_y.load());
			if (lua_pcall(L, 2, 2, 0) != 0) {
				std::cerr << "[루아 함수 오류] " << lua_tostring(L, -1) << "\n";
			}
			else {
				int nextX = lua_tointeger(L, -2);
				int nextY = lua_tointeger(L, -1);
				lua_pop(L, 2);
				(*m_objectManager.m_monster)[key].setPosition(nextX, nextY);
				(*m_objectManager.m_monster)[key].setZone();
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
				std::cerr << "[루아 함수 오류] " << lua_tostring(L, -1) << "\n";
			}
			else {
				int nextX = lua_tointeger(L, -2);
				int nextY = lua_tointeger(L, -1);
				lua_pop(L, 2);
				(*m_objectManager.m_monster)[key].setPosition(nextX, nextY);
				(*m_objectManager.m_monster)[key].setZone();
			}
		}
		break;
		}
		m_objectManager.m_luaMutex[monsterSpecies].unlock();
		m_objectManager.checkViewAtMonster((*m_objectManager.m_monster)[key].m_zone, key);

		// 이동처리 후 다시 이동 타이머 셋팅
		// 추적중인 몬스터가 추적대상과의 거리가 공격범위 안이면 공격 타이머 셋팅 필요
		TIMER timer;
		timer.activeID = key;
		timer.eventType = EVENTTYPE::ACTIVE;
		timer.actTime = system_clock::now() + 1000ms;
		m_objectManager.m_timer.push(timer);
	}
	break;
	case OVERTYPE::MONSTERRESPAWN: 
	{
		int zoneNumber = (*m_objectManager.m_monster)[key].m_zone;
		(*m_objectManager.m_monster)[key].m_monsterState = MONSTERSTATE::IDLE;
		(*m_objectManager.m_monster)[key].m_targetID = -1;

		// 1. 존에 생성된 몬스터 정보 추가
		m_objectManager.m_zone[zoneNumber].insert(key);
		// 2. 생성된 위치를 기준으로 시야계산 및 추적대상 파악
		m_objectManager.checkViewAtMonster(zoneNumber, key);

		// 몬스터 타입에 따른 몬스터 이동
		// EASY - 정지, 비선공 / NORMAL - 방황, 비선공 / HARD - 방황, 선공
		MONSTERTYPE monsterType = (*m_objectManager.m_monster)[key].m_monsterType;
		if (monsterType != MONSTERTYPE::EASY) {
			TIMER timer;
			timer.activeID = key;
			timer.eventType = EVENTTYPE::ACTIVE;
			timer.actTime = system_clock::now() + 1000ms;
			m_objectManager.m_timer.push(timer);
		}		
	}
	break;
	case OVERTYPE::MONSTERATTACK:
	{
		// 몬스터 공격 추가 필요
	}
	break;
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
		(*m_objectManager.m_player)[key].setPosition(rand() % 2000, rand() % 2000);
		(*m_objectManager.m_player)[key].setZone();
		int zoneNumber = (*m_objectManager.m_player)[key].m_zone;		
		m_objectManager.m_zone[zoneNumber].insert(key);
		(*m_objectManager.m_player)[key].sendLoginAllowPacket();

		// 1. 유저가 생성된 존이 해당 유저가 처음 방문하는 경우 몬스터 생성
		m_objectManager.checkFirstVisitZone(zoneNumber);
		// 2. 생성된 위치를 기준으로 시야계산
		m_objectManager.checkViewAtPlayer(zoneNumber, key, p->clientTime);
	}
	break;
	case CS_MOVE_REQUEST:
	{
		//cout << "[이동] 고유키 값 : " << key << " 사용 유저 이동!\n";
		CS_MOVE_REQUEST_PACKET* p = reinterpret_cast<CS_MOVE_REQUEST_PACKET*>(packet);
		(*m_objectManager.m_player)[key].setPosition(static_cast<MOVETYPE>(p->moveType));		
		(*m_objectManager.m_player)[key].sendMoveAllowPacket((*m_objectManager.m_player)[key], p->clientTime);

		int newZone = (*m_objectManager.m_player)[key].m_x.load() / ZONESIZE + ((*m_objectManager.m_player)[key].m_y.load() / ZONESIZE) * (MAPWIDTH / ZONESIZE);
		// 1. 이동한 유저의 zone 변화 확인
		m_objectManager.changeZone(newZone, key);
		// 2. 유저가 이동한 존이 해당 유저가 처음 방문하는 경우 몬스터 생성
		m_objectManager.checkFirstVisitZone(newZone);
		// 3. 이동한 결과를 바탕으로 시야계산
		m_objectManager.checkViewAtPlayer(newZone, key, p->clientTime);	
	}
	break;
	default: break;
	}
}
/*
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
*/