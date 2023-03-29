#include "stdafx.h"
#include "sfml.h"

void Sfml::Initialize()
{
	client.GetNetwork().Initialize();
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
				case sf::Keyboard::Left:
					client.move(0);
					break;
				case sf::Keyboard::Right:
					client.move(1);
					break;
				case sf::Keyboard::Up:
					client.move(2);
					break;
				case sf::Keyboard::Down:
					client.move(3);
					break;
				case sf::Keyboard::Escape:
					window.close();
					break;
				}
			}
		}

		window.clear(Color::Blue);
		client.draw(window);
		window.display();
	}	
}
