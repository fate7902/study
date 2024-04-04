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
	// val : ��ȭ��, op : 1 - �� ���� / 2 - ȸ�� / 3 - ����
	void setHP(int val, int op);
	void setZone();
	// setPosition(int, int) : ������ ��ġ ����
	void setPosition(int x, int y);
	// setPosition(MOVETYPE) : Ÿ�Կ� ���� �� ����
	void setPosition(MOVETYPE movetype);
};

