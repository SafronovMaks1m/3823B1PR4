#include <iostream>
#include <algorithm>
#include "string"
#include <cmath>
#include "exception"
#pragma once

class CMonom {
public:
    float _coef;
    int* _powers;
    size_t _size;
    CMonom();
    CMonom(size_t size);
    CMonom(std::string& str, char* names, size_t size = 3);
    CMonom(float coef, int* mas, size_t size = 3);
    CMonom(float coef, size_t size = 3);
    CMonom(const CMonom& monom);
    ~CMonom();

    CMonom& operator=(const CMonom& obj);

    friend std::istream& operator >> (std::istream& in, CMonom& monom) {
        size_t size; float coef;
        std::cout << "Enter the number of variables of the monom: "; in >> size; monom._size = size;
        std::cout << "Enter the coef of the monom: "; in >> coef; monom._coef = coef;
        monom._powers = new int[monom._size];
        for (size_t i = 0; i < monom._size; i++) {
            std::cout << "degree of the " << i+1 << " variable is" << " = "; in >> monom._powers[i];
        }
        std::cout << std::endl;
        return in;
    }

    friend std::ostream& operator << (std::ostream& os, const CMonom& monom) {
        os << "coef: " << monom._coef << std::endl;
        if (monom._coef == 0)
            return os;
        os << "Degrees: ";
        for (size_t i = 0; i < monom._size; i++) {
            os << monom._powers[i];
            if (i < monom._size - 1)
                os << ", ";
        }
        std::cout << std::endl;
        return os;
    }

    bool is_number(const char& symbol) const noexcept;

    bool is_null() const noexcept;

    CMonom operator+(const CMonom& obj) const;
    CMonom& operator+=(const CMonom& obj);

    CMonom operator-(const CMonom& obj) const;
    CMonom& operator-=(const CMonom& obj);

    CMonom operator*(const CMonom& obj) const noexcept;
    CMonom& operator*=(const CMonom& obj) noexcept;

    CMonom operator/(const CMonom& obj) const;
    CMonom& operator/=(const CMonom& obj);

    CMonom operator*(const float& value) const noexcept;
    CMonom& operator*=(const float& value) noexcept;

    CMonom operator/(const float& value) const;
    CMonom& operator/=(const float& value);

    CMonom operator-() const noexcept;
    CMonom& operator-() noexcept;

    bool operator==(const CMonom& obj) const noexcept;
    bool operator!=(const CMonom& obj) const noexcept;

    bool operator>(const CMonom& obj) const noexcept;
    bool operator<(const CMonom& obj) const noexcept;

    int convertInt(const std::string& str, size_t index) const noexcept;

    float valuePoint(const float* point) const noexcept;
};

CMonom::CMonom() {
    _coef = 0;
    _size = 3;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = 1;
    }
}

CMonom::CMonom(size_t size) {
    _size = size;
    _coef = 0;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = 0;
    }
}

CMonom::CMonom(std::string& str, char* names, size_t size) {
    _size = size;
    _powers = new int[_size];
    int curr_pos = 0;
    float result = 0;
    int sign = 1;
    if (str[0] == '-') {
        sign = -1;
        curr_pos = 1;
    }
    if (is_number(str[curr_pos])) {
        while (is_number(str[curr_pos])) {
            result = result * 10 + (str[curr_pos] - '0');
            curr_pos++;
        }
        if (str[curr_pos] == '.') {
            curr_pos++;
            float float_part = 0.0;
            int accuracy = 0;
            while (is_number(str[curr_pos])) {
                float_part = float_part * 10 + (str[curr_pos] - '0');
                curr_pos++;
                accuracy++;
            }
            result += float_part * pow(10, -accuracy);
        }
    }
    else {
        result = 1;
    }
    result *= sign;
    _coef = result;
    size_t index;
    for (size_t i = 0; i < _size; i++) {
        index = str.find(names[i]);
        if (index != std::string::npos) {
            if (index+2< str.size() && is_number(str[index + 2])) {
                index += 2;
                _powers[i] = convertInt(str, index);
            }
            else if (index + 2 < str.size() - 1 && str[index + 2] == '-') {
                index += 3;
                _powers[i] = -convertInt(str, index);
            }
            else
                _powers[i] = 1;
        }
        else {
            _powers[i] = 0;
        }
    }
}

int CMonom::convertInt(const std::string& str, size_t index) const noexcept {
    int result = 0;
    while ((index != str.size()) && is_number(str[index])) {
        result = result * 10 + (str[index] - '0');
        index++;
    }
    return result;
}

bool CMonom::is_number(const char& symbol) const noexcept {
    return symbol >= '0' && symbol <= '9';
}

bool CMonom::is_null() const noexcept {
    return _coef == 0;
}

CMonom::CMonom(const CMonom& monom) {
    _size = monom._size;
    _coef = monom._coef;
    _powers = new int[_size];
    std::copy(monom._powers, monom._powers + _size, _powers);
}

CMonom::CMonom(float coef, int* mas, size_t size) {
    _coef = coef;
    _size = size;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = mas[i];
    }
}

CMonom::CMonom(float coef, size_t size) {
    _coef = coef;
    _size = size;
    _powers = new int[_size];
}

CMonom& CMonom::operator=(const CMonom& obj) {
    _coef = obj._coef;
    _size = obj._size;
    if (_powers != nullptr)
        delete[] _powers;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = obj._powers[i];
    }
    return *this;
}

CMonom::~CMonom() {
    delete[] _powers;
}

CMonom CMonom::operator+(const CMonom& obj) const {
    if (_size != obj._size || (*this) != obj)
        throw std::logic_error("addition of monomials with different sizes");
    CMonom monom = CMonom(_coef + obj._coef, _powers, _size);
    return monom;
}

CMonom& CMonom::operator+=(const CMonom& obj) {
    if (_size != obj._size || (*this) != obj)
        throw std::logic_error("addition of monomials with different sizes");
    _coef += obj._coef;
    return *this;
}

CMonom CMonom::operator-(const CMonom& obj) const {
    if (_size != obj._size || (*this) != obj)
        throw std::logic_error("addition of monomials with different sizes");
    CMonom monom = CMonom(_coef - obj._coef, _powers, _size);
    return monom;
}

CMonom& CMonom::operator-=(const CMonom& obj) {
    if (_size != obj._size || (*this) != obj)
        throw std::logic_error("addition of monomials with different sizes");
    _coef -= obj._coef;
    return *this;
}

CMonom CMonom::operator*(const CMonom& obj) const noexcept {
    size_t max = std::max(_size, obj._size);
    CMonom monom = CMonom(_coef * obj._coef, max);
    for (size_t i = 0; i < max; i++) {
        if (_size <= i)
            monom._powers[i] = obj._powers[i];
        else if (obj._size <= i)
            monom._powers[i] = _powers[i];
        else
            monom._powers[i] = _powers[i] + obj._powers[i];
    }
    return monom;
}

CMonom& CMonom::operator*=(const CMonom& obj) noexcept {
    _coef *= obj._coef;
    size_t max = std::max(_size, obj._size);
    int* mas = new int[max];
    for (size_t i = 0; i < _size; i++) {
        mas[i] = _powers[i];
    }
    for (size_t i = 0; i < obj._size; i++) {
        mas[i] += obj._powers[i];
    }
    delete[] _powers;
    _powers = mas;
    _size = max;
    return *this;
}

CMonom CMonom::operator/(const CMonom& obj) const {
    if (obj._coef == 0)
        throw std::logic_error("you can't divide by zero");
    size_t max = std::max(_size, obj._size);
    CMonom monom = CMonom(_coef / obj._coef, max);
    for (size_t i = 0; i < max; i++) {
        if (_size <= i)
            monom._powers[i] = obj._powers[i];
        else if (obj._size <= i)
            monom._powers[i] = _powers[i];
        else
            monom._powers[i] = _powers[i] - obj._powers[i];
    }
    return monom;
}

CMonom& CMonom::operator/=(const CMonom& obj) {
    _coef /= obj._coef;
    size_t max = std::max(_size, obj._size);
    int* mas = new int[max];
    for (size_t i = 0; i < _size; i++) {
        mas[i] = _powers[i];
    }
    for (size_t i = 0; i < obj._size; i++) {
        mas[i] -= obj._powers[i];
    }
    delete[] _powers;
    _powers = mas;
    _size = max;
    return *this;
}

CMonom CMonom::operator*(const float& value) const noexcept {
    return CMonom(value * _coef, _powers, _size);
}

CMonom& CMonom::operator*=(const float& value) noexcept {
    this->_coef *= value;
    return *this;
}

CMonom CMonom::operator/(const float& value) const {
    if (value == 0)
        throw std::logic_error("you can't divide by zero");
    return CMonom(value / _coef, _powers, _size);
}

CMonom& CMonom::operator/=(const float& value) {
    if (value == 0)
        throw std::logic_error("you can't divide by zero");
    this->_coef /= value;
    return *this;
}

CMonom CMonom::operator-() const noexcept {
    return CMonom(-_coef, _powers, _size);
}

CMonom& CMonom::operator-() noexcept {
    this->_coef *= -1;
    return *this;
}

bool CMonom::operator==(const CMonom& obj) const noexcept {
    if (_size == obj._size) {
        for (size_t i = 0; i < _size; i++) {
            if (_powers[i] != obj._powers[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool CMonom::operator!=(const CMonom& obj) const noexcept {
    return !((*this) == obj);
}

bool CMonom::operator>(const CMonom& obj) const noexcept {
    size_t m = std::min(_size, obj._size);
    for (size_t i = 0; i < m; i++) {
        if (_powers[i] > obj._powers[i]) {
            return true;
        }
        else if (_powers[i] < obj._powers[i]) {
            return false;
        }
    }
    if (_size == m && obj._size == m)
        return _coef > obj._coef;
    else if (_size != m) {
        for (size_t i = m; i < _size; i++) {
            if (_powers[i] > 0)
                return true;
            else if (_powers[i] == 0)
                continue;
            else
                return false;
        }
        return _coef > obj._coef;
    }
    for (size_t i = m; i < obj._size; i++) {
        if (obj._powers[i] > 0)
            return false;
        else if (obj._powers[i] == 0)
            continue;
        else
            return true;
    }
    return _coef > obj._coef;
}

bool CMonom::operator<(const CMonom& obj) const noexcept {
    return !((*this) > obj);
}

float CMonom::valuePoint(const float* point) const noexcept {
    float result = _coef;
    for (size_t i = 0; i < _size; i++) {
        result *= std::pow(point[i], _powers[i]);
    }
    return result;
}