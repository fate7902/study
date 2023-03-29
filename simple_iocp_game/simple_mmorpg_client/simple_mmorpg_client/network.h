#pragma once

class Network
{
private:
	TcpSocket socket;
	Socket::Status status;

public:
	Network() = default;
	~Network() = default;

	void Initialize();

	const Socket::Status& GetSocketStatus();
};