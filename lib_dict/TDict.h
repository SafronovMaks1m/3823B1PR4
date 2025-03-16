#include <iostream>
#include <string>
#include <stdexcept>
#pragma once

template <class T1, class T2>
class TDict {
	T1 _key;
	T2 _value;
	public:
		TDict() = default;
		TDict(const T1& key, const T2& value) : _key(key), _value(value) { }
		TDict(const TDict& dict) : _key(dict._key), _value(dict._value) { }
		~TDict() { }

		TDict<T1, T2>& operator = (const TDict<T1, T2>& dict) noexcept;

		bool operator> (const TDict<T1, T2>& dict) const noexcept;
		bool operator< (const TDict<T1, T2>& dict) const noexcept;

		bool operator> (const T1& key) const noexcept;
		bool operator< (const T1& key) const noexcept;

		bool operator>= (const TDict<T1, T2>& dict) const noexcept;
		bool operator<= (const TDict<T1, T2>& dict) const noexcept;

		bool operator>= (const T1& key) const noexcept;
		bool operator<= (const T1& key) const noexcept;

		bool operator== (const TDict<T1, T2>& dict) const noexcept;
		bool operator!= (const TDict<T1, T2>& dict) const noexcept;

		bool operator== (const T1& key) const noexcept;
		bool operator!= (const T1& key) const noexcept;

		inline T1 key() const noexcept;
		inline T2& value() noexcept;
		inline const T2& value() const noexcept;

		inline void set_key(const T1& key) noexcept;
		inline void set_value(const T2& value) noexcept;
};

template <class T1, class T2>
TDict<T1, T2>& TDict<T1, T2>::operator=(const TDict<T1, T2>& dict) noexcept {
	if ((*this) != dict) {
		_key = dict._key;
		_value = dict._value;
	}
	return *this;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator> (const TDict<T1, T2>& dict) const noexcept{
	if (_key > dict._key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator< (const TDict<T1, T2>& dict) const noexcept {
	if (_key < dict._key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator> (const T1& key) const noexcept {
	if (this->_key > key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator< (const T1& key) const noexcept {
	if (this->_key < key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator>= (const TDict<T1, T2>& dict) const noexcept {
	if (_key >= dict._key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator<= (const TDict<T1, T2>& dict) const noexcept {
	if (_key <= dict._key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator>= (const T1& key) const noexcept {
	if (this->_key >= key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator<= (const T1& key) const noexcept {
	if (this->_key <= key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator== (const TDict<T1, T2>& dict) const noexcept {
	if (_key == dict._key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator!= (const TDict<T1, T2>& dict) const noexcept {
	if (_key != dict._key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator== (const T1& key) const noexcept {
	if (this->_key == key)
		return true;
	return false;
}

template <class T1, class T2>
bool TDict<T1, T2>::operator!= (const T1& key) const noexcept {
	if (this->_key != key)
		return true;
	return false;
}

template <class T1, class T2>
T1 TDict<T1, T2>::key() const noexcept {
	return _key;
}

template <class T1, class T2>
T2& TDict<T1, T2>::value() noexcept {
	return _value;
}

template <class T1, class T2>
const T2& TDict<T1, T2>::value() const noexcept {
	return _value;
}

template <class T1, class T2>
void TDict<T1, T2>::set_key(const T1& key) noexcept {
	return _key = key;
}

template <class T1, class T2>
void TDict<T1, T2>::set_value(const T2& value) noexcept {
	return _value = value;
}