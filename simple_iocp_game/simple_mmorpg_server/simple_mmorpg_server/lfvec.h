#pragma once
class LFVEC
{
private:
	atomic<vector<int>*> vec;

public:
	LFVEC();
	~LFVEC();

	void emplace_back(int val);
	void erase(int val);
	void clear();
	int empty();
	bool exist(int val);
};