#include "stdafx.h"
#include "network.h"

void Network::Initialize(Object& pl)
{
	status = socket.connect(SERVER_IP, PORT_NUM);
	socket.setBlocking(false);
	if (status != Socket::Done) {
		cout << "서버와 연결할 수 없습니다.\n";
		while (true);
	}
	player = pl;
	SendLogin();
}

const Socket::Status& Network::GetSocketStatus()
{
	return status;
}

// 프로토콜 전송 관련
void Network::SendProtocol(void* protocol)
{
	unsigned char* p = reinterpret_cast<unsigned char*>(protocol);
	size_t sent = 0;
	socket.send(protocol, p[0], sent);
}

void Network::SendLogin()
{
	string str;
	cout << "사용할 닉네임을 적어주세요 : ";
	cin >> str;
	CS_LOGIN_PROTOCOL p;
	p.size = sizeof(CS_LOGIN_PROTOCOL);
	p.type = CS_LOGIN;
	strcpy_s(p.name, str.c_str());
	SendProtocol(&p);
}

void Network::SendMove(const MOVE_TYPE& move_type)
{
	CS_MOVE_PROTOCOL p;
	p.size = sizeof(CS_MOVE_PROTOCOL);
	p.type = CS_MOVE;
	p.move_type = move_type;
	SendProtocol(&p);
}

void Network::ProtocolProcessing(char* ptr)
{	
	switch (ptr[1]) {
	case SC_LOGIN:
	{
		SC_LOGIN_PROTOCOL* p = reinterpret_cast<SC_LOGIN_PROTOCOL*>(ptr);
		player.x = p->x;
		player.y = p->y;
		break;
	}
	}
}

void Network::DataProcessing(char* net_buf, size_t t)
{
	char* ptr = net_buf;
	static size_t in_packet_size = 0;
	static size_t saved_packet_size = 0;
	static char packet_buffer[BUF_SIZE];

	while (0 != t) {
		if (0 == in_packet_size) in_packet_size = ptr[0];
		if (t + saved_packet_size >= in_packet_size) {
			memcpy(packet_buffer + saved_packet_size, ptr, in_packet_size - saved_packet_size);
			ProtocolProcessing(packet_buffer);
			ptr += in_packet_size - saved_packet_size;
			t -= in_packet_size - saved_packet_size;
			in_packet_size = 0;
			saved_packet_size = 0;
		}
		else {
			memcpy(packet_buffer + saved_packet_size, ptr, t);
			saved_packet_size += t;
			t = 0;
		}
	}
}

void Network::Recv()
{
	char network_buf[BUF_SIZE];
	size_t	received;

	auto recv_result = socket.receive(network_buf, BUF_SIZE, received);
	if (recv_result == Socket::Error)
	{
		cout << "Recv 에러!";
		while (true);		
	}
	if (recv_result != Socket::NotReady)
		if (received > 0) DataProcessing(network_buf, received);
}
