#pragma once
#define SFML_STATIC 1
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "..\..\simple_mmorpg_server\simple_mmorpg_server\protocol.h"
using namespace std;
using namespace sf;

#ifdef _DEBUG
#pragma comment (lib, "lib/sfml-graphics-s-d.lib")
#pragma comment (lib, "lib/sfml-window-s-d.lib")
#pragma comment (lib, "lib/sfml-system-s-d.lib")
#pragma comment (lib, "lib/sfml-network-s-d.lib")
#else
#pragma comment (lib, "lib/sfml-graphics-s.lib")
#pragma comment (lib, "lib/sfml-window-s.lib")
#pragma comment (lib, "lib/sfml-system-s.lib")
#pragma comment (lib, "lib/sfml-network-s.lib")
#endif
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "ws2_32.lib")

constexpr auto SCREEN_WIDTH = 9;
constexpr auto SCREEN_HEIGHT = 9;
constexpr auto TILE_WIDTH = 53;
constexpr auto TILE_HEIGHT = 45;

constexpr auto WINDOW_WIDTH = TILE_WIDTH * SCREEN_WIDTH + 10;
constexpr auto WINDOW_HEIGHT = TILE_HEIGHT * SCREEN_HEIGHT + 10;

constexpr int MAX_USER = 5000;

constexpr auto PORT_NUM = 4000;
constexpr auto SERVER_IP = "127.0.0.1";

constexpr auto BUF_SIZE = 256;