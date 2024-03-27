#include "stdafx.h"
#include "player.h"

extern int g_x, g_y;

void Player::draw(RenderWindow& window)
{	
	float rx = (m_x - g_x) * TILEWIDTH + 7;
	float ry = (m_y - g_y) * TILEHEIGHT + 8;
	m_sprite.setPosition(rx, ry);
	window.draw(m_sprite);
}
