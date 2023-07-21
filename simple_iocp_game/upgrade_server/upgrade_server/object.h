#pragma once
#include "stdafx.h"

class OBJECT {
public:
	atomic<pair<int, int>> m_position;
	int m_UID{};

public:
	OBJECT() = default;
	OBJECT(const OBJECT& other)
		: m_position(other.m_position.load(memory_order_acquire)),
		m_UID(other.m_UID)
	{
	}
	OBJECT(OBJECT&& other) noexcept
		: m_position(other.m_position.load(memory_order_acquire)),
		m_UID(other.m_UID)
	{
	}
	OBJECT& operator=(const OBJECT& other)
	{
		if (this == &other) {
			return *this;
		}

		// Copy the member variables
		m_position.store(other.m_position.load(memory_order_acquire),memory_order_release);
		m_UID = other.m_UID;

		return *this;
	}
	~OBJECT() = default;

	void Move(int dir, pair<int, int>& pii) {
		switch (dir) {
		case 0: pii.first++; break; // 우측 이동
		case 1: pii.first--; break; // 좌측 이동
		case 2: pii.second--; break; // 위 이동
		case 3: pii.second++; break; // 아래 이동
		}
	}
	void SetPosition(int dir) {
		pair<int, int> oldPos = m_position.load(memory_order_acquire);
		pair<int, int> newPos(oldPos);
		Move(dir, newPos);
		while (!m_position.compare_exchange_weak(oldPos, newPos, memory_order_release)) {
			newPos = oldPos;
			Move(dir, newPos);
		}
	}
};
