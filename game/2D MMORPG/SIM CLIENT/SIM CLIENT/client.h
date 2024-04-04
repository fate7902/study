#pragma once
#include "terrain.h"
#include "monster.h"
#include "player.h"
#include "network.h"

class Client
{
public:
	Texture*			m_terrainTexture;
	Texture*			m_characterTexture;

	Terrain				m_terrainSand, m_terrainStone;

	Network				m_network;

public:
	Client();
	~Client();

public:
	void rendering(RenderWindow& window);
};

