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
	Object(const Object& other) : m_sprite(other.m_sprite),
		m_x(other.m_x), m_y(other.m_y),
		m_id(other.m_id), m_showing(other.m_showing) {}
	virtual ~Object() = default;

	void setPosition(int x, int y);
	void setSpritePosition();
	void setScale(float x, float y);
	virtual void draw(RenderWindow& window) = 0;
};

