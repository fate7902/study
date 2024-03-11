/*
* IOCP ���� ������ ���� ���
* IocpBase�� ��ӹ޾� ����
*/

#pragma once
#include "iocpbase.h"
#include "extendedOverlapped.h"

constexpr int MAXTHREAD = 12;

class Iocp : public IocpBase
{
private:
	ExtendedOverlapped	m_extOver;

public:
	Iocp() = default;
	Iocp(int port) : IocpBase(port) {}
	~Iocp() = default;

	void initialize();

private:	
	void worker();
};
