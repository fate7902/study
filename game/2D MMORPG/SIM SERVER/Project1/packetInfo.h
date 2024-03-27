/*
* 네트워크 관련 패킷 구조체 및 각종 열거형 
*/
#pragma once

// I/O 타입 열거형
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