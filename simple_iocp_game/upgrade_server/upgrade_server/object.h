#pragma once
#include "stdafx.h"

class OBJECT {
public:
	atomic<pair<int, int>> m_position;
	int m_UID{};

public:
	OBJECT() = default;
	OBJECT(const OBJECT& other)
		: m_position(other.m_position.load()),
		m_UID(other.m_UID)
	{
	}
	OBJECT(OBJECT&& other) noexcept
		: m_position(other.m_position.load()),
		m_UID(other.m_UID)
	{
	}
	~OBJECT() = default;

	void Move(int dir, pair<int, int>& pii) {
		switch (dir) {
		case 0: pii.first++; break; // ���� �̵�
		case 1: pii.first--; break; // ���� �̵�
		case 2: pii.second--; break; // �� �̵�
		case 3: pii.second++; break; // �Ʒ� �̵�
		}
	}
	void SetPosition(int dir) {
		pair<int, int> oldPos = m_position.load(memory_order_release);
		pair<int, int> newPos(oldPos);
		Move(dir, newPos);
		while (!m_position.compare_exchange_weak(oldPos, newPos, memory_order_acquire)) {
			newPos = oldPos;
			Move(dir, newPos);
		}
	}
};
