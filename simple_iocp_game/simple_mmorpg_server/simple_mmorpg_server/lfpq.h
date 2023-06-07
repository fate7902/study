#pragma once
struct TIMER_EVENT {
	int monster_id;
	EVENT_TYPE ev;
	system_clock::time_point act_time;
	int target_id;
};

class LFPQ
{
private:
	struct Node {
		TIMER_EVENT value;
		atomic<Node*> next;

		//Node(const TIMER_EVENT& val) : value(val), next(nullptr) {}
	};

	atomic<Node*> head;

public:
	LFPQ();
	~LFPQ();

	void emplace(const TIMER_EVENT& value);
	bool pop(TIMER_EVENT& value);
	bool top(TIMER_EVENT& value);
};

