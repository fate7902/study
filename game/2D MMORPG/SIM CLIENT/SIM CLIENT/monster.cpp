#include "stdafx.h"
#include "monster.h"

extern int g_x, g_y;

void Monster::draw(RenderWindow& window)
{	
	float rx = (m_x - g_x) * 53.f + 8;
	float ry = (m_y - g_y) * 45.f + 8;
	m_sprite.setPosition(rx, ry);
	window.draw(m_sprite);	
}
