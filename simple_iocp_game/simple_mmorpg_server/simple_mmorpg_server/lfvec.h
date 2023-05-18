#pragma once
class LFVEC
{
private:
	atomic<vector<int>*> vec;

public:
	LFVEC();
	~LFVEC();

	atomic<vector<int>*> Getvec();

	void emplace_back(int val);
	void erase(int val);
	void clear();
	int empty();
	bool exist(int val);
};