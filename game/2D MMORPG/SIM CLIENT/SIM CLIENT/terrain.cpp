#include "stdafx.h"
#include "terrain.h"

void Terrain::draw(RenderWindow& window)
{	
	m_sprite.setPosition(m_x, m_y);
	window.draw(m_sprite);
}
