#pragma once
class Object
{
public:
	atomic<int>			m_x, m_y;
	atomic<int>			m_hp;
	int					m_id;
	int					m_zone;

public:
	Object() = default;
	Object(int id, int hp);
	Object(const Object& other)
		: m_x(other.m_x.load()),
		m_y(other.m_y.load()),
		m_hp(other.m_hp.load()),
		m_id(other.m_id),
		m_zone(other.m_zone){}
	virtual ~Object() {};

public:
	// val : 변화값, op : 1 - 값 설정 / 2 - 회복 / 3 - 감소
	void setHP(int val, int op);
	void setZone();
	// setPosition(int, int) : 값으로 위치 조정
	void setPosition(int x, int y);
	// setPosition(MOVETYPE) : 타입에 따른 값 조정
	void setPosition(MOVETYPE movetype);
};

