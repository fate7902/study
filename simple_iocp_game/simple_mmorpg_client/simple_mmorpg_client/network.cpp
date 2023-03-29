#include "stdafx.h"
#include "network.h"

void Network::Initialize()
{
	status = socket.connect(SERVER_IP, PORT_NUM);
	socket.setBlocking(false);
	if (status != Socket::Done) {
		cout << "서버와 연결할 수 없습니다.\n";
		while (true);
	}
}

const Socket::Status& Network::GetSocketStatus()
{
	return status;
}
