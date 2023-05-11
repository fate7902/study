#include "stdafx.h"
#include "lfvec.h"

LFVEC::LFVEC()
{
	vec = new vector<int>();
	use = false;
}

LFVEC::~LFVEC()
{
	delete vec.load();
}

void LFVEC::emplace_back(int val)
{
	bool old_use = false;
	while (!use.compare_exchange_strong(old_use, true)) {
		old_use = false;
	}

	vector<int>* old_vec = vec.load();
	vector<int>* new_vec = new vector<int>(*old_vec);
	new_vec->emplace_back(val);
	vec.store(new_vec);	
	use.store(false);
}

void LFVEC::insert(int val)
{
	bool old_use = false;
	while (!use.compare_exchange_strong(old_use, true)) {
		old_use = false;
	}

	vector<int>* old_vec = vec.load();
	auto iter = find(old_vec->begin(), old_vec->end(), val);
	if (iter != old_vec->end()) {
		use.store(false);
		return;
	}

	vector<int>* new_vec = new vector<int>(*old_vec);
	new_vec->emplace_back(val);
	vec.store(new_vec);
	use.store(false);
}

void LFVEC::erase(int val)
{
	bool old_use = false;
	while (!use.compare_exchange_strong(old_use, true)) {
		old_use = false;
	}

	vector<int>* old_vec = vec.load();
	vector<int>* new_vec = new vector<int>(*old_vec);
	auto iter = find(new_vec->begin(), new_vec->end(), val);
	new_vec->erase(iter);
	vec.store(new_vec);
	use.store(false);
}

int LFVEC::empty()
{
	bool old_use = false;
	while (!use.compare_exchange_strong(old_use, true)) {
		old_use = false;
	}

	vector<int>* old_vec = vec.load();
	if (old_vec->size() == 0) {
		use.store(false);
		return -1;
	}

	vector<int>* new_vec = new vector<int>(*old_vec);
	int value = *new_vec->begin();
	new_vec->erase(new_vec->begin());
	vec.store(new_vec);
	use.store(false);
	return value;
}

bool LFVEC::exist(int val)
{
	bool old_use = false;
	while (!use.compare_exchange_strong(old_use, true)) {
		old_use = false;
	}

	vector<int>* old_vec = vec.load();
	auto iter = find(old_vec->begin(), old_vec->end(), val);
	use.store(false);
	if (iter == old_vec->end()) return false;
	else return true;
}
