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
	auto new_vec = new vector<int>();
	new_vec->reserve(vec.load()->size() + 1);
	new_vec->insert(new_vec->end(), vec.load()->begin(), vec.load()->end());
	new_vec->push_back(val);
	vector<int>* old_vec = vec.load();
	do {
		delete new_vec;
		new_vec = new vector<int>(*old_vec);
		new_vec->push_back(val);
	} while (!vec.compare_exchange_weak(old_vec, new_vec));
	delete old_vec;
	/*
	bool old_use = false;
	while (!use.compare_exchange_strong(old_use, true)) {
		old_use = false;
	}

	vector<int>* old_vec = vec.load();
	vector<int>* new_vec = new vector<int>(*old_vec);
	new_vec->emplace_back(val);
	vec.store(new_vec);	
	use.store(false);
	*/
}

void LFVEC::insert(int val)
{
	auto new_vec = new vector<int>();
	new_vec->reserve(vec.load()->size() + 1);
	new_vec->insert(new_vec->end(), vec.load()->begin(), vec.load()->end());
	new_vec->push_back(val);
	vector<int>* old_vec = vec.load();
	do {
		delete new_vec;
		new_vec = new vector<int>(*old_vec);
		new_vec->push_back(val);
	} while (!vec.compare_exchange_weak(old_vec, new_vec));
	delete old_vec;
	/*
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
	*/
}

void LFVEC::erase(int val)
{
	vector<int>* old_vec;
	vector<int>* new_vec;
	do {
		old_vec = vec.load();
		new_vec = new vector<int>(*old_vec);
		auto iter = find(new_vec->begin(), new_vec->end(), val);
		if (iter == new_vec->end()) {
			delete new_vec;
			return;
		}
		new_vec->erase(iter);
	} while (!vec.compare_exchange_weak(old_vec, new_vec));
	delete old_vec;
	/*
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
	*/
}

void LFVEC::clear()
{
	delete vec.load();
	vec = new vector<int>();
	use = false;
}

int LFVEC::empty()
{
	vector<int>* old_vec;
	vector<int>* new_vec;
	int value = -1; // 초기값 설정
	do {
		old_vec = vec.load();
		if (old_vec->size() == 0) {
			return -1;
		}
		new_vec = new vector<int>(*old_vec);
		value = *new_vec->begin();
		new_vec->erase(new_vec->begin());
	} while (!vec.compare_exchange_weak(old_vec, new_vec));
	vec.store(new_vec);
	delete old_vec;
	return value;
	/*
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
	*/
}

bool LFVEC::exist(int val)
{
	vector<int>* old_vec;
	vector<int>* new_vec;
	do {
		old_vec = vec.load();
		new_vec = new vector<int>(*old_vec);
		auto iter = find(new_vec->begin(), new_vec->end(), val);
		if (iter == new_vec->end()) {
			delete new_vec;
			return false;
		}
		new_vec->erase(iter);
	} while (!vec.compare_exchange_weak(old_vec, new_vec));
	delete old_vec;
	return true;
	/*
	bool old_use = false;
	while (!use.compare_exchange_strong(old_use, true)) {
		old_use = false;
	}

	vector<int>* old_vec = vec.load();
	auto iter = find(old_vec->begin(), old_vec->end(), val);
	use.store(false);
	if (iter == old_vec->end()) return false;
	else return true;
	*/
}
