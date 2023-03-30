#include "stdafx.h"
#include "sfml.h"

void Sfml::Initialize()
{
	client.GetNetwork().Initialize(client.GetPlayer());
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D Client");	
}

void Sfml::Loop()
{
	Initialize();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {				
				switch (event.key.code) {
				case Keyboard::Left: client.move(MOVE_TYPE::LEFT); break;
				case Keyboard::Right: client.move(MOVE_TYPE::RIGHT); break;
				case Keyboard::Up: client.move(MOVE_TYPE::UP); break;
				case Keyboard::Down: client.move(MOVE_TYPE::DOWN); break;
				case Keyboard::Escape: window.close(); break;
				}
			}
		}

		window.clear(Color::Blue);
		client.draw(window);
		window.display();
	}	
}
