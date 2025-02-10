#include "iostream"
#include "stdexcept"
#include "../lib_dmassive/TDmassive.h"

class DSU {
public:
	int _size;
	TDMassive<int> _parent;
	TDMassive<int> _rank;
	DSU(int size = 0);
	~DSU();
	void make_set(int elem);
	int find(int elem);
	void uni(int first, int second);
	void clear();
	TDMassive<int>& parent();
	TDMassive<int>& rank();
};

DSU::DSU(int size) {
	_size = size;
	_parent = TDMassive<int>(_size);
	for (size_t i = 0; i < _size; i++) {
		_parent[i] = i + 1;
	}
	_rank = TDMassive<int>(_size, 0);
}

DSU::~DSU() {}

void DSU::make_set(int elem) {
	if (elem <= 0 || elem > _size) {
		throw std::logic_error("incorrect addition of a top");
	}
	_size++;
	_parent[elem - 1] = elem;
	_rank[elem - 1] = 0;
}

int DSU::find(int elem) {
	if (elem <= 0 || elem > _size) {
		throw std::logic_error("Input Error: ...\n");
	}
	if (_parent[elem - 1] != elem) {
		_parent[elem - 1] = find(_parent[elem - 1]);
	}
	return _parent[elem - 1];
}

void DSU::uni(int first, int second) {
	int top1 = find(first);
	int top2 = find(second);
	if (_rank[top1 - 1] > _rank[top2 - 1]) {
		_parent[top2 - 1] = top1;
	}
	else if (_rank[top1 - 1] < _rank[top2 - 1]) {
		_parent[top1 - 1] = top2;
	}
	else {
		_parent[top2 - 1] = top1;
		_rank[top1 - 1] += 1;
	}
	for (size_t i = 0; i < _size; i++) {
		std::cout << _parent[i] << " ";
	}
	std::cout << std::endl;
}

void DSU::clear() {
	_size = 0;
	_parent.clear();
	_rank.clear();
}

TDMassive<int>& DSU::parent() {
	return _parent;
}

TDMassive<int>& DSU::rank() {
	return _rank;
}
//