#include <string>
#include "exception"
#include "math.h"
#include "../lib_dict/TDict.h"
#include "../lib_list/list.h"
#include "../lib_list/node.h"
#include "../lib_dmassive/TDmassive.h"
#include "../lib_itable/itable.h"
#pragma once

template <class TKey, class TVal>
class HTList : public ITable<TKey, TVal> {
	TDMassive<Tlist<TDict<TKey, TVal>>> _data;
	size_t _capacity;
	size_t _size;
public:
	HTList(size_t capacity) : _capacity(capacity), _data(capacity, true), _size(0) {};
	size_t hash(int key) const noexcept;
	size_t hash(std::string key) const noexcept;
	void insert(TKey key, TVal value);
	TVal& find(TKey key);
	const TVal& find(TKey key) const;
	void erase(TKey key);
	const TVal& operator[](const TKey key) const;
	TVal& operator[](const TKey key);
	inline size_t capacity() { return  _capacity; }
	inline size_t size() { return  _size; }
	inline TDMassive<Tlist<TDict<TKey, TVal>>>& data() { return _data; }
};

template <class TKey, class TVal>
size_t HTList<TKey, TVal>::hash(int key) const noexcept {
	const double A = (sqrt(5) - 1) / 2;
	double  a = key * A;
	double  b = a - int(a);
	return floor(_capacity * b);
}

template <class TKey, class TVal>
size_t HTList<TKey, TVal>::hash(std::string key) const noexcept {
	int number = 0;
	for (size_t i = 0; i < key.size(); i++)
		number += int(key[i]);
	const double A = (sqrt(5) - 1) / 2;
	double  a = number * A;
	double  b = a - int(a);
	return floor(_capacity * b);
}

template <class TKey, class TVal>
void HTList<TKey, TVal>::insert(TKey key, TVal value) {
	size_t index = hash(key);
	if (_data[index].find(TDict<TKey, TVal>(key, value)) != nullptr)
		throw std::logic_error("There is already such a key.");
	if (_data[index].isEmpty())
		_size++;
	_data[index].push_back(TDict<TKey, TVal>(key, value));
}

template <class TKey, class TVal>
TVal& HTList<TKey, TVal>::find(TKey key) {
	size_t index = hash(key);
	TNode<TDict<TKey, TVal>>* node = _data[index].find(TDict<TKey, TVal>(key, TVal()));
	if (node == nullptr)
		throw std::logic_error("key not found");
	return node->value().value();
}

template <class TKey, class TVal>
const TVal& HTList<TKey, TVal>::find(TKey key) const{
	size_t index = hash(key);
	TNode<TDict<TKey, TVal>>* node = _data[index].find(TDict<TKey, TVal>(key, TVal()));
	if (node == nullptr)
		throw std::logic_error("key not found");
	return node->value().value();
}

template <class TKey, class TVal>
void HTList<TKey, TVal>::erase(TKey key) {
	int index = hash(key);
	TNode<TDict<TKey, TVal>>* node = _data[index].find(TDict<TKey, TVal>(key, TVal()));
	if (node == nullptr)
		throw std::logic_error("key not found");
	_data[index].erase(node);
	if (_data[index].isEmpty())
		_size--;
}

template<class TKey, class TVal>
const TVal& HTList<TKey, TVal>::operator[](const TKey key) const {
	return this->find(key);
}

template<class TKey, class TVal>
TVal& HTList<TKey, TVal>::operator[](const TKey key) {
	return this->find(key);
}