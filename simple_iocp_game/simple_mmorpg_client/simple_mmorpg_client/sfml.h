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

	void Loop();

private:
	void Initialize();
};

