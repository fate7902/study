#include "stdafx.h"
#include "iocp.h"

void Iocp::initialize()
{	
	cout << "[Loading] Iocp::initialize()\n";
	for (int i = 0; i < MAXUSER; i++) m_availableID.push(i);

	IocpBase::initialize();

	m_clientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_extOver.m_overType = OVERTYPE::ACCEPT;
	AcceptEx(m_serverSock, m_clientSock, m_extOver.m_sendBuf, 0, m_addrSize + 16, m_addrSize + 16, 0, &m_extOver.m_wsaOver);

	vector<thread> workerThreads;
	thread timerThread{ &Iocp::timerWorker, this };
	thread dbThread{ &Iocp::dbWorker, this };
	for (int i = 0; i < MAXTHREAD; ++i)
		workerThreads.emplace_back(&Iocp::worker, this);
	for (auto& th : workerThreads)
		th.join();
	timerThread.join();
	dbThread.join();
	cout << "[Finished] server logout.\n";
}

int Iocp::getIDAssignment()
{
	int id;
	if (m_availableID.try_pop(id)) return id;
	else return -1;
}

void Iocp::disconnect(int key)
{
	int currentZone = m_objectManager.m_player[key]->m_zone;
	int currentZoneGroup = currentZone / ZONEGROUP;
	m_objectManager.m_player[key]->m_zone = -1;
	m_objectManager.m_zoneMutex[currentZoneGroup].lock();
	m_objectManager.m_zone[currentZone].unsafe_erase(key);
	m_objectManager.m_zoneMutex[currentZoneGroup].unlock();

	shared_ptr<concurrent_unordered_set<int>> oldlistPtr = m_objectManager.m_player[key]->m_viewlist;
	for (const auto& id : *oldlistPtr) {
		if (id >= MAXUSER) continue;
		m_objectManager.m_player[id]->m_viewlistMutex.lock();
		m_objectManager.m_player[id]->m_viewlist->unsafe_erase(key);
		m_objectManager.m_player[id]->m_viewlistMutex.unlock();
		m_objectManager.m_player[id]->sendDeleteObjectPacket(key);
	}
	cout << "Logout on client[" << key << "]\n";

	shared_ptr<Player> playerDataPtr = m_objectManager.m_player[key];
	CHARACTERINFO characterInfo{
		playerDataPtr->m_ID,
		playerDataPtr->m_PW,
		playerDataPtr->m_x.load(),
		playerDataPtr->m_y.load(),
		playerDataPtr->m_lv,
		playerDataPtr->m_exp.load(),
		playerDataPtr->m_hp.load()};
	DBREQUEST dbRequest{ key, DBREQUESTTYPE::SAVE, system_clock::now(), true, characterInfo };
	if (characterInfo.ID != "test") m_requestDB.push(dbRequest);

	TIMER timer;
	timer.activeID = key;
	timer.eventType = EVENTTYPE::LOGOUT;
	timer.actTime = system_clock::now() + seconds(5);
	m_objectManager.m_timer.push(timer);	
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
	case EVENTTYPE::LOGOUT:
	{
		timerExtendedOver->m_overType = OVERTYPE::PLAYERLOGOUT;
	}
	break;
	}
	PostQueuedCompletionStatus(m_iocpHandle, 1, timer.activeID, &timerExtendedOver->m_wsaOver);
}

void Iocp::dbWorker()
{
	while (true) {
		DBREQUEST dbRequest;
		if (!m_requestDB.empty()) {
			m_requestDB.try_pop(dbRequest);
			if (dbRequest.actTime <= system_clock::now()) {
				processDB(dbRequest);
			}
			else {
				m_requestDB.push(dbRequest);
				this_thread::sleep_for(10ms);
			}			
		}
		else {
			this_thread::sleep_for(10ms);
		}
	}
}

void Iocp::processDB(DBREQUEST dbRequest)
{
	switch (dbRequest.requestType)
	{	
	case DBREQUESTTYPE::SAVE:
	{
		if(dbRequest.bCompulsory) m_DB.saveData(dbRequest.characterInfo);
		else {
			CHARACTERINFO characterInfo;
			if (m_objectManager.m_player.find(dbRequest.requestID) != m_objectManager.m_player.end()) {
				shared_ptr<Player> playerDataPtr = m_objectManager.m_player[dbRequest.requestID];
				characterInfo.ID = playerDataPtr->m_ID;
				characterInfo.PW = playerDataPtr->m_PW;
				characterInfo.x = playerDataPtr->m_x.load();
				characterInfo.y = playerDataPtr->m_y.load();
				characterInfo.lv = playerDataPtr->m_lv;
				characterInfo.exp = playerDataPtr->m_exp.load();
				characterInfo.hp = playerDataPtr->m_hp.load();
			}
			if (characterInfo.lv != 0) {
				m_DB.saveData(characterInfo);
				dbRequest.actTime = system_clock::now() + minutes(5);
				m_requestDB.push(dbRequest);
			}
		}
	}
	break;
	}
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
			if (extOver->m_overType == OVERTYPE::ACCEPT) {
			}
			else {
				if (extOver->m_overType == OVERTYPE::SEND)
					delete extOver;
				disconnect(static_cast<int>(key));
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
		int assignmentID = getIDAssignment();
		if (assignmentID != -1) {	
			m_objectManager.m_player.insert(make_pair(assignmentID, make_shared<Player>(assignmentID, 100)));
			m_objectManager.m_player[assignmentID]->setSocket(m_clientSock);
			CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_clientSock), m_iocpHandle, assignmentID, 0);
			m_objectManager.m_player[assignmentID]->asynRecv();
		}
		else {
			cout << "[�˸�] �ִ� �����ο� ������������ ���� �Ұ�.\n";
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
		int remainPacketData = len + m_objectManager.m_player[key]->m_reaminPacketData;
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
		m_objectManager.m_player[key]->m_reaminPacketData = remainPacketData;
		if (remainPacketData > 0) {
			memcpy(extOver->m_sendBuf, p, remainPacketData);
		}
		m_objectManager.m_player[key]->asynRecv();
	}
	break;
	case OVERTYPE::SEND:
	{
		delete extOver;
		if (len == 0) {
			disconnect(key);			
			break;
		}		
		//cout << "���ۿϷ�\n";
	}
	break;
	case OVERTYPE::PLAYERLOGOUT:
	{
		m_objectManager.m_playerMutex.lock();
		shared_ptr<Player> playerDataPtr = m_objectManager.m_player[key];
		CHARACTERINFO characterInfo{
			playerDataPtr->m_ID,
			playerDataPtr->m_PW,
			playerDataPtr->m_x.load(),
			playerDataPtr->m_y.load(),
			playerDataPtr->m_lv,
			playerDataPtr->m_exp.load(),
			playerDataPtr->m_hp.load()};
		DBREQUEST dbRequest{ key, DBREQUESTTYPE::SAVE, system_clock::now(), true, characterInfo };
		m_requestDB.push(dbRequest);
		m_objectManager.m_player.unsafe_erase(key);
		m_objectManager.m_playerMutex.unlock();
		m_availableID.push(key);
		delete extOver;
	}
	break;
	case OVERTYPE::MONSTERACTIVE: 
	{		
		// ��� ��ũ��Ʈ ����Ͽ� ���� �̵� ����
		int monsterSpecies = static_cast<int>(m_objectManager.m_monster[key]->m_monsterType);
		lua_State* L = m_objectManager.m_luaState[monsterSpecies];
		int targetID;
		m_objectManager.m_luaMutex[monsterSpecies].lock();
		switch (m_objectManager.m_monster[key]->m_monsterState) {
		case MONSTERSTATE::IDLE:
		{
			// ��Ȳ�̵�
			lua_getglobal(L, "randomMove");
			lua_pushinteger(L, m_objectManager.m_monster[key]->m_x.load());
			lua_pushinteger(L, m_objectManager.m_monster[key]->m_y.load());
			if (lua_pcall(L, 2, 2, 0) != 0) {
				std::cerr << "[LUA�˸�] " << lua_tostring(L, -1) << "\n";
			}
			else {
				int nextX = lua_tointeger(L, -2);
				int nextY = lua_tointeger(L, -1);
				lua_pop(L, 2);
				m_objectManager.m_monster[key]->setPosition(nextX, nextY);
				m_objectManager.m_monster[key]->setZone();
			}
		}
		break;
		case MONSTERSTATE::CHASE:
		{
			targetID = m_objectManager.m_monster[key]->m_targetID;
			if (m_objectManager.m_player[targetID]->m_zone != -1) {
				int startX = m_objectManager.m_monster[key]->m_x.load();
				int startY = m_objectManager.m_monster[key]->m_y.load();
				int endX = m_objectManager.m_player[targetID]->m_x.load();
				int endY = m_objectManager.m_player[targetID]->m_y.load();
				lua_getglobal(L, "findPath");
				lua_pushinteger(L, startX);
				lua_pushinteger(L, startY);
				lua_pushinteger(L, endX);
				lua_pushinteger(L, endY);
				if (lua_pcall(L, 4, 2, 0) != 0) {
					cerr << "[LUA�˸�] " << lua_tostring(L, -1) << "\n";
				}
				else {
					int nextX = lua_tointeger(L, -2);
					int nextY = lua_tointeger(L, -1);
					lua_pop(L, 2);
					m_objectManager.m_monster[key]->setPosition(nextX, nextY);
					m_objectManager.m_monster[key]->setZone();
				}
			}
			else {
				m_objectManager.m_monster[key]->m_targetID = -1;
				m_objectManager.m_monster[key]->m_monsterState = MONSTERSTATE::IDLE;
			}		
		}
		break;
		}
		m_objectManager.m_luaMutex[monsterSpecies].unlock();
		m_objectManager.checkViewAtMonster(m_objectManager.m_monster[key]->m_zone, key);

		// �̵�ó�� �� �ٽ� �̵� Ÿ�̸� ����
		// �������� ���Ͱ� ���������� �Ÿ��� ���ݹ��� ���̸� ���� Ÿ�̸� ���� �ʿ�
		TIMER timer;
		timer.activeID = key;
		timer.eventType = EVENTTYPE::ACTIVE;
		timer.actTime = system_clock::now() + 1000ms;
		m_objectManager.m_timer.push(timer);
		delete extOver;
	}
	break;
	case OVERTYPE::MONSTERRESPAWN: 
	{
		int currentZone = m_objectManager.m_monster[key]->m_zone;		
		m_objectManager.m_monster[key]->m_monsterState = MONSTERSTATE::IDLE;
		m_objectManager.m_monster[key]->m_targetID = -1;

		// 1. ���� ������ ���� ���� �߰�
		m_objectManager.m_zone[currentZone].insert(key);
		// 2. ������ ��ġ�� �������� �þ߰�� �� ������� �ľ�
		m_objectManager.checkViewAtMonster(currentZone, key);

		// ���� Ÿ�Կ� ���� ���� �̵�
		// EASY - ����, �񼱰� / NORMAL - ��Ȳ, �񼱰� / HARD - ��Ȳ, ����
		MONSTERTYPE monsterType = m_objectManager.m_monster[key]->m_monsterType;
		if (monsterType != MONSTERTYPE::EASY) {
			TIMER timer;
			timer.activeID = key;
			timer.eventType = EVENTTYPE::ACTIVE;
			timer.actTime = system_clock::now() + 1000ms;
			m_objectManager.m_timer.push(timer);
		}		
		delete extOver;
	}
	break;
	case OVERTYPE::MONSTERATTACK:
	{		
		// ���� ���� �߰� �ʿ�
		delete extOver;
	}
	break;
	default: cout << "[�˸�] �˼����� ��Ŷ.\n"; break;
	}	
}

void Iocp::processPacket(char* packet, int key)
{
	switch (packet[1])
	{
	case CS_TESTLOGIN_REQUEST: // ��Ʈ���� �׽�Ʈ �� ���� ��Ŷ
	{
		CS_TESTLOGIN_REQUEST_PACKET* p = reinterpret_cast<CS_TESTLOGIN_REQUEST_PACKET*>(packet);
		CHARACTERINFO characterInfo{
			"test", "test", rand() % 2000, rand() % 2000, 1, 0, 100
		};
		m_objectManager.m_player[key]->initialize(characterInfo);
		int currentZone = m_objectManager.m_player[key]->m_zone;		
		m_objectManager.m_zone[currentZone].insert(key);
		m_objectManager.m_player[key]->sendLoginAllowPacket(LOGINRESULT::SUCCESS);
		// 1. ������ ������ ���� �ش� ������ ó�� �湮�ϴ� ��� ���� ����
		m_objectManager.checkFirstVisitZone(currentZone);
		// 2. ������ ��ġ�� �������� �þ߰��
		m_objectManager.checkViewAtPlayer(currentZone, key, p->clientTime);
	}
	break;
	case CS_LOGIN_REQUEST:
	{		
		CS_LOGIN_REQUEST_PACKET* p = reinterpret_cast<CS_LOGIN_REQUEST_PACKET*>(packet);
		CHARACTERINFO characterInfo{ p->ID, p->PW, };
		// �α��� ���н� �������� ó��
		if (!m_DB.login(characterInfo)) {
			m_objectManager.m_player[key]->sendLoginAllowPacket(LOGINRESULT::FAILED);
			m_objectManager.m_playerMutex.lock();
			m_objectManager.m_player.unsafe_erase(key);
			m_objectManager.m_playerMutex.unlock();
			break;
		}
		m_objectManager.m_player[key]->initialize(characterInfo);
		int currentZone = m_objectManager.m_player[key]->m_zone;
		m_objectManager.m_zone[currentZone].insert(key);
		m_objectManager.m_player[key]->sendLoginAllowPacket(LOGINRESULT::SUCCESS);

		// 1. ������ ������ ���� �ش� ������ ó�� �湮�ϴ� ��� ���� ����
		m_objectManager.checkFirstVisitZone(currentZone);
		// 2. ������ ��ġ�� �������� �þ߰��
		m_objectManager.checkViewAtPlayer(currentZone, key, p->clientTime);
		// 3. �ڵ����� 5�и��� ������ ����
		DBREQUEST dbRequest{ key, DBREQUESTTYPE::SAVE, system_clock::now() + minutes(5), false, };
		m_requestDB.push(dbRequest);
	}
	break;
	case CS_MOVE_REQUEST:
	{		
		CS_MOVE_REQUEST_PACKET* p = reinterpret_cast<CS_MOVE_REQUEST_PACKET*>(packet);
		m_objectManager.m_player[key]->setPosition(static_cast<MOVETYPE>(p->moveType));		
		m_objectManager.m_player[key]->sendMoveAllowPacket(m_objectManager.m_player[key], p->clientTime);

		int currentZone = m_objectManager.m_player[key]->m_x.load() / ZONESIZE + (m_objectManager.m_player[key]->m_y.load() / ZONESIZE) * (MAPWIDTH / ZONESIZE);
		// 1. �̵��� ������ zone ��ȭ Ȯ��
		m_objectManager.changeZone(currentZone, key);
		// 2. ������ �̵��� ���� �ش� ������ ó�� �湮�ϴ� ��� ���� ����
		m_objectManager.checkFirstVisitZone(currentZone);
		// 3. �̵��� ����� �������� �þ߰��
		m_objectManager.checkViewAtPlayer(currentZone, key, p->clientTime);
	}
	break;
	default: break;
	}
}
