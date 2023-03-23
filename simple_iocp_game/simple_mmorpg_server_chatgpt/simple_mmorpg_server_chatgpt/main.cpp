#include "stdafx.h"
#include "iocp.h"

int main() {
	IOCP iocp;
	thread t(&IOCP::Initialize, &iocp);
	t.join();

	// 다른 작업 진행 가능
}