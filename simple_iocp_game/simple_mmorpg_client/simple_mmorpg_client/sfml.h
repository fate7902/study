#pragma once
#include "stdafx.h"

constexpr auto SCREEN_WIDTH = 9;
constexpr auto SCREEN_HEIGHT = 9;
constexpr auto TILE_WIDTH = 65;

constexpr auto WINDOW_WIDTH = TILE_WIDTH * SCREEN_WIDTH + 10;
constexpr auto WINDOW_HEIGHT = TILE_WIDTH * SCREEN_WIDTH + 10;

class Sfml
{
private:
	RenderWindow window;

public:
	Sfml() = default;
	~Sfml() = default;

	void Loop();

private:
	void Initialize();

};

