#pragma once
#include "object.h"

class Terrain : public Object
{
public:
	Terrain() = default;
	Terrain(Texture& texture, int left, int top, int width, int height)
		: Object(texture, left, top, width, height) {}
	virtual ~Terrain() override = default;

	void draw(RenderWindow& window) override;
};

