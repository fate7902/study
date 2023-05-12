#pragma once
constexpr int NAME_SIZE = 10;

enum class MOVE_TYPE { UP, DOWN, RIGHT, LEFT };

// server -> client
constexpr int SC_LOGIN = 0;
constexpr int SC_TRANS = 1;
constexpr int SC_ADD_OBJECT = 2;
constexpr int SC_REMOVE_OBJECT = 3;

// client -> server
constexpr int CS_LOGIN = 100;
constexpr int CS_MOVE = 101;

#pragma pack(push, 1)
// server -> client
struct SC_LOGIN_PROTOCOL {
	unsigned char size;
	char type;
	int id;
	int x, y;
};

struct SC_MOVE_PROTOCOL {
	unsigned char size;
	char type;
	int id;
	int x, y;
	unsigned int client_time;
};

struct SC_ADD_OBJECT_PROTOCOL {
	unsigned char size;
	char type;
	int id;
	int x, y;
};

struct SC_REMOVE_OBJECT_PROTOCOL {
	unsigned char size;
	char type;
	int id;
};

// client -> server
struct CS_LOGIN_PROTOCOL{
	unsigned char size;
	char type;
	char name[NAME_SIZE];
};

struct CS_MOVE_PROTOCOL {
	unsigned char size;
	char type;
	MOVE_TYPE move_type;
	unsigned int client_time;
};
#pragma pack(pop)