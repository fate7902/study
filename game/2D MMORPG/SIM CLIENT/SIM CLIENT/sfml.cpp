#include "stdafx.h"
#include "sfml.h"

void Sfml::run()
{
	SfmlBase::initialize();
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
				}
			}
		}

		// ���� ������
		m_window.clear(Color::Blue);	
		m_client.rendering(m_window);
		m_window.display();
	}
}
