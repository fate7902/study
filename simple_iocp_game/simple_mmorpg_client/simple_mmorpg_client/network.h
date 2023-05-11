#pragma once
#include "object.h"

class Network
{
private:
	TcpSocket socket;
	Socket::Status status;

public:
	Object* player;
	Object* players;
	int my_id;

public:
	Network() = default;
	~Network() = default;

	void Initialize(Object* pl);
	const Socket::Status& GetSocketStatus();

	void SendProtocol(void* protocol);
	void SendLogin();
	void SendMove(const MOVE_TYPE& move_type);

	void ProtocolProcessing(char* ptr);
	void DataProcessing(char* net_buf, size_t t);
	void Recv();
};