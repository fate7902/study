#pragma once
class LFVEC
{
private:
	atomic<vector<int>*> vec;
	atomic<bool> use;

public:
	LFVEC();
	~LFVEC();

	void emplace_back(int val);
	void insert(int val);
	void erase(int val);
	void clear();
	int empty();
	bool exist(int val);
};