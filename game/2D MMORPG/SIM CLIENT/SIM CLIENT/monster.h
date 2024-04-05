#pragma once
#include "object.h"

class Monster : public Object
{
public:
	MONSTERTYPE		m_type;

public:
	Monster() = default;
	Monster(Texture& texture, int left, int top, int width, int height)
		: Object(texture, left, top, width, height) {}
	Monster(const Monster& other) : Object(other)
		, m_type(other.m_type) {}
	virtual ~Monster() override = default;

	void draw(RenderWindow& window) override;
};

