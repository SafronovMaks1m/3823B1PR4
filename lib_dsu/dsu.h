#include "iostream"
#include "stdexcept"
#include "../lib_dmassive/TDmassive.h"

class DSU {
	int _size;
	TDMassive<int> _parent;
	TDMassive<int> _rank;
public:
	DSU(int size = 0);
	~DSU();
	void make_set(int elem);
	int find(int elem);
	void uni(int first, int second);
	void clear();
};

DSU::DSU(int size = 0) {
	_size = size;
	_parent = TDMassive<int>(_size);
	for (size_t i = 0; i < _size; i++) {
		_parent[i] = i+1;
	}
	_rank = TDMassive<int>(_size, 0);
}

DSU::~DSU() {}

void DSU::make_set(int elem) {
	if (elem > _size + 1) {
		throw std::logic_error("incorrect addition of a set");
	}
	_size++;
	_parent[elem - 1] = elem;
}

int DSU::find(int elem) {
	if (elem <= 0 || elem > _size) {
		throw std::logic_error("Input Error: ...\n");
	}
	if (_parent[elem-1] == elem) {
		return elem;
	}
	return find(_parent[elem-1]);
}

void DSU::uni(int first, int second) {
	int top1 = find(first);
	int top2 = find(second);
	_parent[top2 - 1] = top1;
	if (_rank[top1 - 1] == 0) {
		_rank[top1 - 1] = _rank[top2 - 1] + 1;
	}
	else {
		if (_rank[top1 - 1] <= _rank[top2 - 1]) {
			_rank[top1 - 1] = _rank[top2 - 1] + 1;
		}
	}
}

void DSU::clear() {
	_size = 0;
	_parent.clear();
	_rank.clear();
}