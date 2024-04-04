#pragma once
#include "object.h"

class Player : public Object
{
public:
	Player() = default;
	Player(Texture& texture, int left, int top, int width, int height)
		: Object(texture, left, top, width, height) {}
	Player(const Player& other) : Object(other) {}
	virtual ~Player() override = default;

	void draw(RenderWindow& window) override;
};

