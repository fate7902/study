#include "stdafx.h"
#include "network.h"

void Network::Initialize()
{
	status = socket.connect(SERVER_IP, PORT_NUM);
	socket.setBlocking(false);
	if (status != Socket::Done) {
		cout << "������ ������ �� �����ϴ�.\n";
		while (true);
	}
}

const Socket::Status& Network::GetSocketStatus()
{
	return status;
}
