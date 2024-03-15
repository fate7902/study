#pragma once
class SfmlBase
{
protected:
	RenderWindow			m_window;

protected:
	SfmlBase() = default;
	virtual ~SfmlBase() = default;

	void initialize();
	virtual void run() = 0;
};

