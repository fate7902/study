#pragma once
#include "sfmlBase.h"
#include "client.h"

class Sfml : public SfmlBase
{
public:
	Client			m_client;

public:
	Sfml() = default;
	virtual ~Sfml() override = default;

	void initialize();
	void run() override;
};

