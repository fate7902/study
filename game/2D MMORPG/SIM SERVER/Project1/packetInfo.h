/*
* ��Ʈ��ũ ���� ��Ŷ ����ü �� ���� ������ 
*/
#pragma once

// I/O Ÿ�� ������
enum class OVERTYPE { ACCEPT, SEND, RECV };

// server -> client packetType
constexpr int SC_LOGIN_ALLOW = 1;

// client -> server packetType
constexpr int CS_LOGIN_REQUEST = 100;

#pragma pack(push, 1)
// server -> client packet
struct SC_LOGIN_ALLOW_PACKET {
	unsigned char size;
	char type;	
	int x, y;
};

// client -> server packet
struct CS_LOGIN_REQUEST_PACKET {
	unsigned char size;
	char type;
};
#pragma pack(pop)