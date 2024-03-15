#pragma once
#include "terrain.h"
#include "monster.h"
#include "player.h"

class Client
{
protected:
	Texture*			m_terrainTexture;
	Texture*			m_monsterTexture;
	Texture*			m_characterTexture;

	Terrain				m_terrainSand, m_terrainStone;
	Monster				m_monster;
	Player				m_player;

public:
	Client();
	~Client();

public:
	void rendering(RenderWindow& window);
};

