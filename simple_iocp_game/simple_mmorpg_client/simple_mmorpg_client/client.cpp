#include "stdafx.h"
#include "client.h"

extern int g_x, g_y;

Client::Client()
{
	map = new Texture;
	character = new Texture;
	map->loadFromFile("map.png");
	character->loadFromFile("character.png");
	tileA = Object{ *map, 12, 13, TILE_WIDTH, TILE_HEIGHT };
	tileA.show();
	tileB = Object{ *map, 12, 218, TILE_WIDTH, TILE_HEIGHT };
	tileB.show();	
	player = Object{ *character, 60, 290, 175, 195 };
	player.setScale(0.3f, 0.23f);
	player.move(4, 4);
	player.show();
}

Client::~Client()
{
	delete map;
	delete character;
}

void Client::draw(RenderWindow& window)
{	
	network.Recv();
	for (int i = 0; i < SCREEN_WIDTH; ++i) {
		for (int j = 0; j < SCREEN_HEIGHT; ++j) {
			int tile_x = i + g_x;
			int tile_y = j + g_y;
			if ((tile_x < 0) || (tile_y < 0)) continue;
			if (((tile_x + tile_y) % 6) < 3) {
				tileA.move(TILE_WIDTH * i + 7, TILE_HEIGHT * j + 7);
				tileA.map_draw(window);
			}
			else
			{
				tileB.move(TILE_WIDTH * i + 7, TILE_HEIGHT * j + 7);
				tileB.map_draw(window);
			}
		}
	}
	player.draw(window);
}

void Client::move(const MOVE_TYPE& action_type)
{
	network.SendMove(action_type);
}

Network& Client::GetNetwork()
{
	return network;
}

Object& Client::GetPlayer()
{
	return player;
}
