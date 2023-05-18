#include "stdafx.h"
#include "lfvec.h"

LFVEC::LFVEC()
{
	vec = new vector<int>();	
}

LFVEC::~LFVEC()
{
	delete vec.load();
}

atomic<vector<int>*> LFVEC::Getvec()
{
	return vec.load();
}

void LFVEC::emplace_back(int val)
{
	vector<int>* old_vec;
	vector<int>* new_vec;
	while(true) {
		old_vec = vec.load();
		new_vec = new vector<int>(*old_vec);
		auto iter = find(new_vec->begin(), new_vec->end(), val);
		if (iter != new_vec->end()) {
			delete new_vec;
			return;
		}
		new_vec->emplace_back(val);
		if (vec.compare_exchange_strong(old_vec, new_vec)) {
			delete old_vec;
			return;
		}
		else delete new_vec;
	}
}

void LFVEC::erase(int val)
{
	vector<int>* old_vec;
	vector<int>* new_vec;
	while(true) {
		old_vec = vec.load();
		new_vec = new vector<int>(*old_vec);
		auto iter = find(new_vec->begin(), new_vec->end(), val);
		if (iter == new_vec->end()) {
			delete new_vec;
			return;
		}
		new_vec->erase(iter);
		if (vec.compare_exchange_strong(old_vec, new_vec)) {
			delete old_vec;
			return;
		}
		else delete new_vec;
	}	
}

void LFVEC::clear()
{
	vector<int>* old_vec;
	vector<int>* new_vec;
	while(true) {
		old_vec = vec.load();
		new_vec = new vector<int>(*old_vec);
		new_vec->clear();
		if (vec.compare_exchange_weak(old_vec, new_vec)) {
			delete old_vec;
			break;
		}
		else delete new_vec;
	}	
}

int LFVEC::empty()
{
	vector<int>* old_vec;
	vector<int>* new_vec;
	int value = -1;
	while(true) {
		old_vec = vec.load();
		if (old_vec->size() == 0) return -1;
		new_vec = new vector<int>(*old_vec);
		value = *new_vec->begin();
		new_vec->erase(new_vec->begin());
		if (vec.compare_exchange_weak(old_vec, new_vec)) {
			delete old_vec;
			return value;
		}
		else delete new_vec;
	}	
}

bool LFVEC::exist(int val)
{
	vector<int>* old_vec;
	vector<int>* new_vec;	
	while (true) {
		old_vec = vec.load();
		new_vec = new vector<int>(*old_vec);
		auto iter = find(new_vec->begin(), new_vec->end(), val);
		if (iter == new_vec->end()) {
			delete new_vec;
			return false;
		}
		if (vec.compare_exchange_weak(old_vec, new_vec)) {
			delete old_vec;
			return true;
		}
		else delete new_vec;
	}	
}
