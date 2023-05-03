#pragma once
constexpr int NAME_SIZE = 10;

enum class MOVE_TYPE { UP, DOWN, RIGHT, LEFT };

// server -> client
#define SC_LOGIN 0

// client -> server
#define CS_LOGIN 100
#define CS_MOVE 101

#pragma pack(push, 1)
// server -> client
struct SC_LOGIN_PROTOCOL {
    uint8_t size;
    char type;
    int x, y;
};

// client -> server
struct CS_LOGIN_PROTOCOL {
    uint8_t size;
    char type;
    char name[NAME_SIZE];
};

struct CS_MOVE_PROTOCOL {
    uint8_t size;
    char type;
    MOVE_TYPE move_type;
};
#pragma pack(pop)