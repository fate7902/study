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
				// 키 입력 관리
				switch (event.key.code) {				
				}
			}
		}

		// 게임 렌더링
		m_window.clear(Color::Blue);	
		m_client.rendering(m_window);
		m_window.display();
	}
}
