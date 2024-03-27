#pragma once
class Object
{
public:
	atomic<int>			m_x, m_y;
	atomic<int>			m_hp;
	int					m_id;

public:
	Object() = default;
	Object(int id, int hp);
	~Object() = default;

protected:
	// val : ��ȭ��, op : 1 - �� ���� / 2 - ȸ�� / 3 - ����
	void setHP(int val, int op);

	// setPosition(int, int) : ������ ��ġ ����
	void setPosition(int x, int y);
	// setPosition(MOVETYPE) : Ÿ�Կ� ���� �� ����
	void setPosition(MOVETYPE movetype);
};

