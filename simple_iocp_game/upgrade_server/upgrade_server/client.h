#pragma once
#include "ext_over.h"
#include "object.h"

class CLIENT : public OBJECT
{
public:
	int m_prevRemainDataSize;
	SOCKET m_socket;
	EXT_OVER m_recvOver;

public:
	CLIENT() = default;
	CLIENT(int prevRemainDataSize, SOCKET socket, int UID)
		: m_prevRemainDataSize(prevRemainDataSize), m_socket(socket) 
	{
		m_UID = UID;
	}
    CLIENT(const CLIENT& other)
        : OBJECT(other),
        m_prevRemainDataSize(other.m_prevRemainDataSize),
        m_socket(other.m_socket),
        m_recvOver(other.m_recvOver)
    {
    }
    CLIENT(CLIENT&& other) noexcept
        : OBJECT(move(other)),
        m_prevRemainDataSize(other.m_prevRemainDataSize),
        m_socket(other.m_socket),
        m_recvOver(move(other.m_recvOver))
    {
    }
	CLIENT& operator=(const CLIENT& other)
	{
		if (this == &other) {
			return *this;
		}

		// Call the copy assignment operator of the base class
		OBJECT::operator=(other);

		// Copy the member variables
		m_prevRemainDataSize = other.m_prevRemainDataSize;
		m_socket = other.m_socket;
		m_recvOver = other.m_recvOver;

		return *this;
	}
	~CLIENT() = default;

	void recv();
};
