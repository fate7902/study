/*
* IOCP ���� ������ ���� ���
* IocpBase�� ��ӹ޾� ����
*/

#pragma once
#include "iocpbase.h"
#include "extendedOverlapped.h"
#include "objectManager.h"

constexpr int MAXTHREAD = 12;

struct TIMER {
	int							activeID;
	EVENTTYPE					eventType;
	system_clock::time_point	actTime;

	bool operator<(const TIMER& other) const {
		return actTime > other.actTime;
	}
};

class Iocp : public IocpBase
{
private:
	ExtendedOverlapped					m_extOver;
	concurrent_queue<int>*				m_availableID;
	ObjectManager						m_objectManager;
	concurrent_priority_queue<TIMER>	m_timer;
	atomic<bool>*						m_bZone;

public:
	Iocp() = default;
	Iocp(int port) : IocpBase(port) {}
	~Iocp() = default;

	void initialize();

private:	
	int getIDAssignment();
	void disconnect(int key);
	void worker();
	void timerWorker();
	void processTimer(TIMER timer);
	void processPacketIO(ExtendedOverlapped*& extOver, DWORD len, int key);
	void processPacket(char* packet, int key);
	void checkFirstVisitZone(int zoneNumber);
};
