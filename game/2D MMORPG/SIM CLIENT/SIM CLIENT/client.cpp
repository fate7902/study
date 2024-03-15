#include "stdafx.h"
#include "client.h"

Client::Client()
{
	m_terrainTexture = new Texture;
	m_terrainTexture->loadFromFile("map.png");
	m_terrainSand = Terrain(*m_terrainTexture, 12, 13, TILEWIDTH, TILEHEIGHT);
	m_terrainStone = Terrain(*m_terrainTexture, 12, 218, TILEWIDTH, TILEHEIGHT);

	m_monsterTexture = new Texture;
	m_monsterTexture->loadFromFile("monster.png");
	// �̹��� ��ġ�� ���� ���� ���� �ʿ�
	m_monster = Monster(*m_monsterTexture, 12, 13, TILEWIDTH, TILEHEIGHT);

	m_characterTexture = new Texture;
	m_characterTexture->loadFromFile("character.png");
	// �̹��� ��ġ�� ���� ���� ���� �ʿ�
	m_player = Player(*m_characterTexture, 60, 290, 175, 195);
}

Client::~Client()
{
	delete m_terrainTexture;
	delete m_monsterTexture;
	delete m_characterTexture;
}

void Client::rendering(RenderWindow& window)
{
	// ���� �׸���
	// ĳ���� �̵��� ���� ���� �ʿ�
	for (int i = 0; i < SCREENWIDTH; ++i) {
		for (int j = 0; j < SCREENHEIGHT; ++j) {
			int tileX = i;
			int tileY = j;
			if ((tileX < 0) || (tileY < 0)) continue;
			if (((tileX + tileY) % 6) < 3) {
				m_terrainSand.setPosition(TILEWIDTH * i + 7, TILEHEIGHT * j + 7);
				m_terrainSand.draw(window);
			}
			else
			{
				m_terrainStone.setPosition(TILEWIDTH * i + 7, TILEHEIGHT * j + 7);
				m_terrainStone.draw(window);
			}
		}
	}

	// ���� �� ���� �׸���
}
