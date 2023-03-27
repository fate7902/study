#include "stdafx.h"
#include "client.h"

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
	player.move(5, 5);
	player.show();
}

Client::~Client()
{
	delete map;
	delete character;
}

void Client::draw(RenderWindow& window)
{	
	for (int i = 0; i < SCREEN_WIDTH; ++i) {
		for (int j = 0; j < SCREEN_HEIGHT; ++j) {
			int tile_x = i;
			int tile_y = j;
			if ((tile_x < 0) || (tile_y < 0)) continue;
			if (((tile_x + tile_y) % 6) < 3) {
				tileA.move(TILE_WIDTH * i + 5, TILE_HEIGHT * j + 5);
				tileA.draw(window);
			}
			else
			{
				tileB.move(TILE_WIDTH * i + 5, TILE_HEIGHT * j + 5);
				tileB.draw(window);
			}
		}
	}
	player.draw(window);
}

void Client::move(int dir)
{
	switch (dir)
	{
	case 0: // left
		player.move(player.x - TILE_WIDTH, player.y);
		break;
	case 1: // right
		player.move(player.x + TILE_WIDTH, player.y);
		break;
	case 2: // up
		player.move(player.x, player.y - TILE_HEIGHT);
		break;
	case 3: // down
		player.move(player.x, player.y + TILE_HEIGHT);
		break;
	}
}