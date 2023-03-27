#include "stdafx.h"
#include "object.h"

Object::Object() : showing{ false }, x{ 0 }, y{ 0 }
{
}

Object::Object(Texture& t, int left, int top, int width, int height) : showing{ false }, x{ 0 }, y{ 0 }
{
	sprite.setTexture(t);
	sprite.setTextureRect(IntRect(left, top, width, height));
}

void Object::setScale(float x, float y)
{
	sprite.setScale(x, y);
}

void Object::show()
{
	showing = true;
}

void Object::hide()
{
	showing = false;
}

void Object::move(int pos_x, int pos_y)
{
	x = pos_x;
	y = pos_y;
}

void Object::draw(RenderWindow& window)
{
	if (!showing) return;
	sprite.setPosition((float)x, (float)y);
	window.draw(sprite);
}