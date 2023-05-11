#pragma once

class Object
{
private:
	bool showing;
	Sprite sprite;

public:
	int x, y;
	int id;

public:
	Object();
	Object(Texture& t, int left, int top, int width, int height);
	~Object() = default;

	void setScale(float x, float y);
	void show();
	void hide();
	void move(int pos_x, int pos_y);
	void draw(RenderWindow& window);
	void map_draw(RenderWindow& window);
};