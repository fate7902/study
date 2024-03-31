/*
* 네트워크 관련 패킷 구조체 및 각종 열거형 
*/
#pragma once

// I/O 타입 열거형
enum class OVERTYPE { ACCEPT, SEND, RECV };

// server -> client packetType
constexpr int SC_LOGIN_ALLOW = 1;
constexpr int SC_MOVE_ALLOW = 2;
constexpr int SC_ADDOBJECT_ALLOW = 3;
constexpr int SC_DELETEOBJECT_ALLOW = 4;

// client -> server packetType
constexpr int CS_LOGIN_REQUEST = 100;
constexpr int CS_MOVE_REQUEST = 101;


#pragma pack(push, 1)
// server -> client packet
struct SC_LOGIN_ALLOW_PACKET {
	unsigned char size;
	char type;
	int x, y;
};

struct SC_MOVE_ALLOW_PACKET {
	unsigned char size;
	char type;
	int x, y;
};

struct SC_ADDOBJECT_PACKET {
	unsigned char size;
	char type;
	int x, y;
	int id;
};

struct SC_DELETEOBJECT_PACKET {
	unsigned char size;
	char type;
	int id;
};

// client -> server packet
struct CS_LOGIN_REQUEST_PACKET {
	unsigned char size;
	char type;
};

struct CS_MOVE_REQUEST_PACKET {
	unsigned char size;
	char type;
	int moveType;
};
#pragma pack(pop)