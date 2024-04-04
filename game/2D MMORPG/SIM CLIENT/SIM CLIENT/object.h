#pragma once

class Object
{
public:	
	Sprite			m_sprite;
	int				m_x, m_y;
	int				m_id;
	bool			m_showing;

public:
	Object() = default;
	Object(Texture& texture, int left, int top, int width, int height);
	virtual ~Object() = default;

	void setPosition(int x, int y);
	void setSpritePosition();
	void setScale(float x, float y);
	virtual void draw(RenderWindow& window) = 0;
};

