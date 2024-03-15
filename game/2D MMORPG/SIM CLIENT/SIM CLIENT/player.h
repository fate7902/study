#pragma once
#include "object.h"

class Player : public Object
{
protected:
	int				m_id;

public:
	Player() = default;
	Player(Texture& texture, int left, int top, int width, int height)
		: Object(texture, left, top, width, height) {}
	~Player() = default;

	void draw(RenderWindow& window) override;
};

