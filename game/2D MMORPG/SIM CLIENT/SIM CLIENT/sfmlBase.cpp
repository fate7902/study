#include "stdafx.h"
#include "sfmlBase.h"

void SfmlBase::initialize()
{
	m_window.create(VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "2D Client");
}
