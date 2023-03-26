#include "stdafx.h"
#include "sfml.h"

void Sfml::Initialize()
{
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
					break;
				case sf::Keyboard::Right:					
					break;
				case sf::Keyboard::Up:
					break;
				case sf::Keyboard::Down:
					break;
				case sf::Keyboard::Escape:
					window.close();
					break;
				}
			}
		}

		window.clear(Color::Yellow);
		window.display();
	}	
}
