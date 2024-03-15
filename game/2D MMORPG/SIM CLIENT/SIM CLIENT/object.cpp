#include "stdafx.h"
#include "object.h"

Object::Object(Texture& texture, int left, int top, int width, int height)
{
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(IntRect(left, top, width, height));
}

void Object::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Object::setSpritePosition()
{
	m_sprite.setPosition(m_x, m_y);
}

void Object::setScale(float x, float y)
{
	m_sprite.setScale(x, y);
}
