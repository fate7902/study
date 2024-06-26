/*
* IOCP 서버 구현의 메인 헤더
* IocpBase를 상속받아 구현
*/

#pragma once
#include "iocpbase.h"
#include "extendedOverlapped.h"
#include "objectManager.h"
#include "database.h"

constexpr int MAXTHREAD = 12;

class Iocp : public IocpBase
{
private:
	ExtendedOverlapped							m_extOver;
	concurrent_queue<int>						m_availableID;
	ObjectManager								m_objectManager;
	concurrent_queue<DBREQUEST>					m_requestDB;
	Database									m_DB;

public:
	Iocp() = default;
	Iocp(int port) : IocpBase(port) {}
	~Iocp() = default;

	void initialize();

private:	
	int getIDAssignment();
	void disconnect(int key);
	void timerWorker();
	void processTimer(TIMER timer);
	void dbWorker();
	void processDB(DBREQUEST dbRequest);
	void worker();
	void processPacketIO(ExtendedOverlapped*& extOver, DWORD len, int key);
	void processPacket(char* packet, int key);
};
