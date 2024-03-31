#include "stdafx.h"
#include "sfml.h"



void Sfml::initialize()
{
	m_client.m_network.initialize();
	SfmlBase::initialize();	
}

void Sfml::run()
{	
	initialize();
	while (m_window.isOpen())
	{
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				m_window.close();
			if (event.type == Event::KeyPressed) {
				// Ű �Է� ����
				switch (event.key.code) {
				case Keyboard::Up: m_client.m_network.sendMove(MOVETYPE::UP); break;
				case Keyboard::Down: m_client.m_network.sendMove(MOVETYPE::DOWN); break;
				case Keyboard::Left: m_client.m_network.sendMove(MOVETYPE::LEFT); break;
				case Keyboard::Right: m_client.m_network.sendMove(MOVETYPE::RIGHT); break;
				default: break;
				}
			}
		}

		// ���� ������
		m_window.clear(Color::Blue);	
		m_client.rendering(m_window);
		m_window.display();
	}
}
