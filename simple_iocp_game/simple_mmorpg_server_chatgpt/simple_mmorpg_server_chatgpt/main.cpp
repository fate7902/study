#include "stdafx.h"
#include "iocp.h"

int main() {
	IOCP iocp;
	thread t(&IOCP::Initialize, &iocp);
	t.join();

	// �ٸ� �۾� ���� ����
}