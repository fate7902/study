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
	// val : 변화값, op : 1 - 값 설정 / 2 - 회복 / 3 - 감소
	void setHP(int val, int op);

	// setPosition(int, int) : 값으로 위치 조정
	void setPosition(int x, int y);
	// setPosition(MOVETYPE) : 타입에 따른 값 조정
	void setPosition(MOVETYPE movetype);
};

