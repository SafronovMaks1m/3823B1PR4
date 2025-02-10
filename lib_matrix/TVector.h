#include "TDmassive.h"
#include "iostream"
#include <math.h>
#include "exception"
#include "algorithm"
#pragma once

template<class T>
class TVector {
protected:
    TDMassive<T> _array;
    size_t _start_index;
public:
    TVector(const size_t size = 5, int value = 0, size_t start_index = 0);
    TVector(const T* mas, const size_t size);
    TVector(const TVector& vector);
    TVector<T>& operator = (const TVector <T>& vector);
    void check_lenght(const size_t len) const;
    const T& operator[](int index) const noexcept;
    T& operator[](int index) noexcept;
    size_t size() const noexcept;
    size_t start_index() const noexcept;
    TVector<T> operator+(const TVector<T>& obj) const;
    TVector<T> operator-(const TVector<T>& obj) const;
    TVector<T>& operator += (const TVector<T>& obj);
    TVector<T>& operator -= (const TVector<T>& obj);
    int operator *(const TVector<T>& obj) const;
    TVector<T>& operator *=(const T& value) noexcept;
    TVector<T> operator *(const T& value) const noexcept;
    double search_length() const noexcept;
    bool operator == (const TVector<T>& obj) const;
    bool operator != (const TVector<T>& obj) const;
    void print() const;
};

template <class T>
TVector<T>::TVector(const size_t size, int value, size_t start_index) {
    _start_index = start_index;
    _array = TDMassive<T>(size, value);
}

template <class T>
TVector<T>::TVector(const T* mas, const size_t size) {
    _start_index = 0;
    _array = TDMassive<T>(mas, size);
    size_t i = 0;
    while (mas[i] == 0 && i < size) {
        _start_index++;
        i++;
    }
}

template <class T>
TVector<T>::TVector(const TVector& vector) {
    _array = vector._array;
    _start_index = vector._start_index;
}

template <class T>
TVector<T>& TVector<T>::operator =(const TVector <T>& vector) {
    _array = vector._array;
    _start_index = vector._start_index;
    return *this;
}

template <class T>
void TVector<T>::check_lenght(const size_t len) const {
    if (size() != len)
        throw std::logic_error("the length of the vectors does not match");
}

template <class T>
const T& TVector<T>::operator[](int index) const noexcept {
    if (index < _start_index) {
        static const T default_value = T{};
        return default_value;
    }
    return _array[index - _start_index];
}

template <class T>
T& TVector<T>::operator[](int index) noexcept {
    static T invalid_value{};
    if (index >= _start_index) {
        return _array[index - _start_index];
    }
    return invalid_value;
}

template <class T>
size_t TVector<T>::size() const noexcept {
    return _array.size();
}

template <class T>
size_t TVector<T>::start_index() const noexcept {
    return _start_index;
}

template <class T>
TVector<T> TVector<T>::operator+(const TVector<T>& obj) const {
    check_lenght(obj.size());
    TVector<T> new_vector = TVector(size());
    for (size_t i = 0; i < size(); i++) {
        new_vector[i] = _array[i] + obj._array[i];
    }
    return new_vector;
}

template <class T>
TVector<T> TVector<T>::operator-(const TVector<T>& obj) const {
    check_lenght(obj.size());
    TVector<T> new_vector = TVector(size());
    for (size_t i = 0; i < size(); i++) {
        new_vector[i] = _array[i] - obj._array[i];
    }
    return new_vector;
}

template <class T>
TVector<T>& TVector<T>::operator+=(const TVector<T>& obj) {
    check_lenght(obj.size());
    for (size_t i = 0; i < size(); i++) {
        _array[i] += obj._array[i];
    }
    return *this;
}

template <class T>
TVector<T>& TVector<T>::operator-=(const TVector<T>& obj) {
    check_lenght(obj.size());
    for (size_t i = 0; i < size(); i++) {
        _array[i] -= obj._array[i];
    }
    return *this;
}

template <class T>
int TVector<T>::operator *(const TVector<T>& obj) const {
    check_lenght(obj.size());
    T s = 0;
    for (size_t i = 0; i < size(); i++) {
        s += _array[i] * obj._array[i];
    }
    return s;
}

template<class T>
TVector<T>& TVector<T>::operator *=(const T& value) noexcept {
    for (size_t i = 0; i < size(); i++) {
        _array[i] *= value;
    }
    return *this;
}

template<class T>
TVector<T> TVector<T>::operator *(const T& value) const noexcept {
    TVector<T> obj = TVector<T>();
    for (size_t i = 0; i < size(); i++) {
        obj[i] = _array[i] * value;
    }
    return obj;
}

template <class T>
double TVector<T>::search_length() const noexcept {
    return sqrt(double(operator*(*this)));
}

template <class T>
bool TVector<T>::operator==(const TVector<T>& obj) const {
    check_lenght(obj.size());
    for (size_t i = 0; i < size(); i++) {
        if (_array[i] != obj._array[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool TVector<T>::operator!=(const TVector<T>& obj) const {
    check_lenght(obj.size());
    return !(this->operator==(obj));
}

template <class T>
void TVector<T>::print() const {
    _array.print();
}
template <class T>
std::istream& operator >> (std::istream& in, TVector<T>& vector) {
    T value = 0;
    std::cout << "������� " << vector.size() << " �����: ";
    for (int i = 0; i < vector.size(); i++) {
        in >> value;
        vector[i] = value;
    }
    std::cout << std::endl;
    return in;
}




