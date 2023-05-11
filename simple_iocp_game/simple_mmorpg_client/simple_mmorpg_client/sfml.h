#pragma once
#include "client.h"

class Sfml
{
private:
	RenderWindow window;
	Client client;

public:
	Sfml() = default;
	~Sfml() = default;

	void Loop(Object* pl);

private:
	void Initialize(Object* pl);
};

