/*
* 네트워크 관련 패킷 구조체 및 각종 열거형 
*/
#pragma once

constexpr int MAXIDLEN = 20;
constexpr int MAXPWLEN = 100;

// I/O 타입 열거형
enum class OVERTYPE { ACCEPT, SEND, RECV, PLAYERLOGOUT, MONSTERACTIVE, MONSTERRESPAWN, MONSTERATTACK };
// 로그인 결과
enum class LOGINRESULT { SUCCESS, FAILED };

// server -> client packetType
constexpr int SC_LOGIN_ALLOW = 1;
constexpr int SC_MOVE_ALLOW = 2;
constexpr int SC_ADDOBJECT_ALLOW = 3;
constexpr int SC_DELETEOBJECT_ALLOW = 4;

// client -> server packetType
constexpr int CS_TESTLOGIN_REQUEST = 100;
constexpr int CS_LOGIN_REQUEST = 101;
constexpr int CS_MOVE_REQUEST = 102;


#pragma pack(push, 1)
// server -> client packet
struct SC_LOGIN_ALLOW_PACKET {
	unsigned char size;
	char type;
	int loginResult;
	int x, y;
	int lv;
	int exp;
	int hp;
	int key;
};

struct SC_MOVE_ALLOW_PACKET {
	unsigned char size;
	char type;
	int x, y;
	int key;
	unsigned clientTime;
};

struct SC_ADDOBJECT_ALLOW_PACKET {
	unsigned char size;
	char type;
	int monsterType;
	int x, y;
	int key;
};

struct SC_DELETEOBJECT_ALLOW_PACKET {
	unsigned char size;
	char type;
	int key;
};

// client -> server packet
struct CS_LOGIN_REQUEST_PACKET {
	unsigned char size;
	char type;
	char ID[MAXIDLEN];
	char PW[MAXPWLEN];
	unsigned clientTime;
};

struct CS_TESTLOGIN_REQUEST_PACKET {
	unsigned char size;
	char type;
	unsigned clientTime;
};

struct CS_MOVE_REQUEST_PACKET {
	unsigned char size;
	char type;
	int moveType;
	unsigned clientTime;
};
#pragma pack(pop)