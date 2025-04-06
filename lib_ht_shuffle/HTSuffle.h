#include <string>
#include "exception"
#include "math.h"
#include "../lib_pair/TPair.h"
#include "../lib_dmassive/TDmassive.h"
#include "../lib_itable/itable.h"
#pragma once

template <class TKey, class TVal>
class HTSuffle : public ITable<TKey, TVal> {
	TDMassive<TPair<TKey, TVal>> _data;
	size_t _capacity;
	size_t _size;
public:
	HTSuffle(size_t capacity) : _capacity(capacity), _data(capacity, true), _size(0) {};
	bool is_full() const noexcept;
	bool is_empty() const noexcept;
	size_t hash(int key) const noexcept;
	size_t hash(std::string key) const noexcept;
	void insert(TKey key, TVal value);
	size_t search_index(TKey key);
	void repeated_mixing(size_t& index, TKey key);
	int mutually_prime_number() const noexcept;
	TVal& find(TKey key);
	const TVal& find(TKey key) const;
	int search(TKey key) const noexcept;
	void erase(TKey key);
	const TVal& operator[](const TKey key) const;
	TVal& operator[](const TKey key);
	inline size_t capacity() { return  _capacity; }
	inline size_t size() { return  _size; }
	TDMassive<TPair<TKey, TVal>>& data() { return _data; }
};

template <class TKey, class TVal>
bool HTSuffle<TKey, TVal>::is_full() const noexcept {
	return _size == _capacity;
}

template <class TKey, class TVal>
bool HTSuffle<TKey, TVal>::is_empty() const noexcept {
	return _size == 0;
}

template <class TKey, class TVal>
size_t HTSuffle<TKey, TVal>::hash(int key) const noexcept {
	const double A = (sqrt(5) - 1) / 2;
	double  a = key * A;
	double  b = a - int(a);
	return floor(_capacity * b);
}

template <class TKey, class TVal>
size_t HTSuffle<TKey, TVal>::hash(std::string key) const noexcept {
	int number = 0;
	for (size_t i = 0; i < key.size(); i++)
		number += int(key[i]);
	const double A = (sqrt(5) - 1) / 2;
	double  a = number * A;
	double  b = a - int(a);
	return floor(_capacity * b);
}

template <class TKey, class TVal>
void HTSuffle<TKey, TVal>::insert(TKey key, TVal value) {
	if (is_full())
		throw std::logic_error("The table is full");
	size_t index = search_index(key);
	_data.replace(index, TPair<TKey, TVal>(key, value));
	_size++;
}

template <class TKey, class TVal>
size_t HTSuffle<TKey, TVal>::search_index(TKey key) {
	size_t index = hash(key);
	if (_data.states()[index] == State::busy) {
		if (_data[index].first() == key)
			throw std::logic_error("There is already such a key.");
		repeated_mixing(index, key);
		return index;
	}
	return index;
}

template <class TKey, class TVal>
void HTSuffle<TKey, TVal>::repeated_mixing(size_t& index, TKey key) {
	int h = mutually_prime_number();
	size_t result;
	for (size_t i = 1; i < _capacity; i++) {
		result = (index + i*h) % _capacity;
		if (_data.states()[result] == State::busy && _data[result].first() == key)
			throw std::logic_error("There is already such a key.");
		if (_data.states()[result] == State::deleted || _data.states()[result] == State::empty) {
			index = result;
			break;
		}
	}
}

template <class TKey, class TVal>
int HTSuffle<TKey, TVal>::mutually_prime_number() const noexcept {
	bool flag = false;
	for (size_t i = 2; i < _capacity; i++) {
		flag = false;
		for (size_t j = 2; j <= i; j++) {
			if (_capacity % j == 0 && i % j == 0) {
				flag = true;
				break;
			}
		}
		if (!flag) return i;
	}
	return 1;
}

template <class TKey, class TVal>
TVal& HTSuffle<TKey, TVal>::find(TKey key) {
	size_t index = hash(key);
	if (_data.states()[index] == State::busy && _data[index].first() == key)
		return _data[index].second();
	if (_data.states()[index] == State::empty)
		throw std::logic_error("key not found");
	int h = mutually_prime_number();
	size_t result;
	for (size_t i = 1; i < _capacity; i++) {
		result = (index + i * h) % _capacity;
		if (_data.states()[result] == State::busy && _data[result].first() == key)
			return _data[result].second();
		if (_data.states()[result] == State::empty)
			throw std::logic_error("key not found");
	}
	throw std::logic_error("key not found");
}

template <class TKey, class TVal>
const TVal& HTSuffle<TKey, TVal>::find(TKey key) const{
	size_t index = hash(key);
	if (_data.states()[index] == State::busy && _data[index].first() == key)
		return _data[index].second();
	if (_data.states()[index] == State::empty)
		throw std::logic_error("key not found");
	int h = mutually_prime_number();
	size_t result;
	for (size_t i = 1; i < _capacity; i++) {
		result = (index + i * h) % _capacity;
		if (_data.states()[result] == State::busy && _data[result].first() == key)
			return _data[result].second();
		if (_data.states()[result] == State::empty)
			throw std::logic_error("key not found");
	}
	throw std::logic_error("key not found");
}


template <class TKey, class TVal>
int HTSuffle<TKey, TVal>::search(TKey key) const noexcept {
	size_t index = hash(key);
	if (_data.states()[index] == State::busy && _data[index].first() == key)
		return index;
	if (_data.states()[index] == State::empty)
		return -1;
	int h = mutually_prime_number();
	size_t result;
	for (size_t i = 1; i < _capacity; i++) {
		result = (index + i * h) % _capacity;
		if (_data.states()[result] == State::busy && _data[result].first() == key)
			return result;
		if (_data.states()[result] == State::empty)
			return -1;
	}
	return -1;
}

template <class TKey, class TVal>
void HTSuffle<TKey, TVal>::erase(TKey key) {
	if (is_empty())
		throw std::logic_error("table is empty");
	int index = search(key);
	if (index == -1)
		throw std::logic_error("key not found");
	_data.remove_by_index(index);
	_size--;
}

template<class TKey, class TVal>
const TVal& HTSuffle<TKey, TVal>::operator[](const TKey key) const {
	return this->find(key);
}

template<class TKey, class TVal>
TVal& HTSuffle<TKey, TVal>::operator[](const TKey key) {
	return this->find(key);
}