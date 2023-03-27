#pragma once
#include "object.h"

class Client
{
private:
	Texture* map;
	Texture* character;
	Object tileA, tileB;
	Object player;

public:
	Client();
	~Client();

	void draw(RenderWindow& window);
	void move(int dir);
};