#include "stdafx.h"
#include "terrain.h"

void Terrain::draw(RenderWindow& window)
{	
	Object::setSpritePosition();
	window.draw(m_sprite);
}
