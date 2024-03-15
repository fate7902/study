#pragma once
constexpr int PORT = 4000;
constexpr auto SERVERIP = "127.0.0.1";
constexpr int BUF = 256;

class Network
{
protected:
	TcpSocket			m_socket;
	Socket::Status		m_status;

protected:
	Network() = default;
	~Network() = default;

	void initialize();
	void recv();
	void recvPacketChecking(char* recvPacket, size_t received);
	void processPacket(char* processedPacket);
};

