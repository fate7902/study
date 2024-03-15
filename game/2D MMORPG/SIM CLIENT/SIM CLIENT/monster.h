#pragma once
#include "object.h"

class Monster : public Object
{
protected:
	int				m_id;

public:
	Monster() = default;
	Monster(Texture& texture, int left, int top, int width, int height)
		: Object(texture, left, top, width, height) {}
	~Monster() = default;

	void draw(RenderWindow& window) override;
};

