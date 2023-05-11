#pragma once
#include "object.h"
#include "network.h"

class Client
{
private:
	Texture* map;
	Texture* character;
	Object tileA, tileB;
	Object player;
	Network network;

public:
	Object* players;

public:
	Client();
	~Client();

	void initialize();

	void draw(RenderWindow& window);
	void move(const MOVE_TYPE& action_type);

	Network& GetNetwork();
	Object& GetPlayer();
};