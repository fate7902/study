#pragma once
#include "sfmlBase.h"
#include "client.h"

class Sfml : public SfmlBase
{
protected:
	Client			m_client;

public:
	Sfml() = default;
	virtual ~Sfml() = default;

	void run() override;
};

