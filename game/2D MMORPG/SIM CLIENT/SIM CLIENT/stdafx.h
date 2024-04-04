#pragma once
#define SFML_STATIC 1
#include "include/SFML/Graphics.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

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

using namespace sf;

#include <iostream>
#include <concurrent_unordered_map.h>
#include "..\..\SIM SERVER\Project1\packetInfo.h"
using namespace std;
using namespace concurrency;

constexpr auto SCREENWIDTH = 9;
constexpr auto SCREENHEIGHT = 9;
constexpr auto TILEWIDTH = 50;
constexpr auto TILEHEIGHT = 50;
constexpr auto WINDOWWIDTH = TILEWIDTH * SCREENWIDTH + 10;
constexpr auto WINDOWHEIGHT = TILEHEIGHT * SCREENHEIGHT + 10;
constexpr auto MAXUSER = 5000;

enum class MOVETYPE { UP, DOWN, LEFT, RIGHT };
enum class MONSTERTYPE { EASY, NORMAL, HARD };