#include "exception"
#include "../lib_dmassive/TDmassive.h"
#pragma once

template <class T>
class Heap {
protected:
	TDMassive<T> _data;
	size_t _size;
public:
	inline size_t left(size_t index) const;
	inline size_t right(size_t index) const;
	inline size_t parent(size_t index) const;
	inline bool is_empty() const noexcept;
	inline TDMassive<T> data() const noexcept;
	inline size_t size() const noexcept;
	void insert(T value) noexcept;
	virtual void emplace(size_t index, T value) = 0;
private:
	virtual void sift_down(size_t) noexcept = 0;
	virtual void sift_up(size_t) noexcept = 0;
};

template<class T>
size_t Heap<T>::left(size_t index) const {
	if (index < 0 || index >= _size)
		throw std::logic_error("incorrect index");
	return 2 * index + 1;
}

template<class T>
size_t Heap<T>::right(size_t index) const {
	if (index < 0 || index >= _size)
		throw std::logic_error("incorrect index");
	return 2 * index + 2;
}

template<class T>
size_t Heap<T>::parent(size_t index) const {
	if (index < 0 || index >= _size)
		throw std::logic_error("incorrect index");
	else if (index == 0)
		return 0;
	return (index - ((index%2) == 0 ? 2 : 1))/2;
}

template<class T>
bool Heap<T>::is_empty() const noexcept {
	return _data.empty();
}

template <class T>
TDMassive<T> Heap<T>::data() const noexcept {
	return _data;
}

template <class T>
size_t Heap<T>::size() const noexcept {
	return _size;
}

template<class T>
void Heap<T>::insert(T value) noexcept {
	_data.push_back(value);
	_size++;
	sift_up(_size-1);
}