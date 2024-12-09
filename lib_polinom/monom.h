#include <iostream>
#include <algorithm>
#include <cmath>
#include "exception"

class CMonom {
    double _coef;
    int* _powers;
    size_t _size;
    public:
        CMonom();
        CMonom(double coef, int* mas, size_t size); 
        CMonom(double coef, size_t size); 
        CMonom(const CMonom& monom);
        ~CMonom();

        friend std::istream& operator >> (std::istream& in, CMonom &monom){
            size_t size; double coef;
            std::cout << "size: "; in >> size; monom._size = size;
            std::cout << "coef: "; in >> coef; monom._coef = coef;
            monom._powers = new int[monom._size];
            for (size_t i = 0; i < monom._size; i++){
                std::cout << "[" << i << "]" << " = "; in >> monom._powers[i];
            }
            std::cout << std::endl;
            return in;
        }

        friend std::ostream& operator << (std::ostream &os, const CMonom &monom){
            os << "coef: " << monom._coef << std::endl;
            os << "Degrees: ";
            for (size_t i = 0; i<monom._size; i++){
                os << monom._powers[i];
                if (i<monom._size-1)
                    os << ", ";
            }
            std::cout << std::endl;
            return os;
        }

        CMonom operator+(const CMonom& obj) const noexcept;
        CMonom& operator+=(const CMonom& obj) noexcept;
        
        CMonom operator-(const CMonom& obj) const noexcept;
        CMonom& operator-=(const CMonom& obj) noexcept;

        CMonom operator*(const CMonom& obj) const noexcept;
        CMonom& operator*=(const CMonom& obj) noexcept;

        CMonom operator/(const CMonom& obj) const;
        CMonom& operator/=(const CMonom& obj);

        CMonom operator*(const double& value) const noexcept;
        CMonom& operator*=(const double& value) noexcept;

        CMonom operator/(const double& value) const;
        CMonom& operator/=(const double& value);

        CMonom operator-() const noexcept;
        CMonom& operator-() noexcept;
        double valuePoint(const double* point) const noexcept;
};

CMonom::CMonom() {
    _size = 3;
    _coef = 1;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = 1;
    }
}

CMonom::CMonom(const CMonom& monom) {
    _coef = monom._coef;
    _size = monom._size;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = monom._powers[i];
    }
}

CMonom::CMonom(double coef, int* mas, size_t size){
    _coef = coef;
    _size = size;
    _powers = new int[_size];
    for (size_t i = 0; i<_size; i++){
        _powers[i] = mas[i];
    }
}

CMonom::CMonom(double coef, size_t size){
    _coef = coef;
    _size = size;
    _powers = new int[_size];
}

CMonom::~CMonom() {
    delete[] _powers;
}

CMonom CMonom::operator+(const CMonom& obj) const noexcept{
    CMonom monom = CMonom(_coef+obj._coef, _powers, _size);
    return monom;
}

CMonom& CMonom::operator+=(const CMonom& obj) noexcept{
    _coef+=obj._coef;
    return *this;
}

CMonom CMonom::operator-(const CMonom& obj) const noexcept{
    CMonom monom = CMonom(_coef-obj._coef, _powers, _size);
    return monom;
}

CMonom& CMonom::operator-=(const CMonom& obj) noexcept{
    _coef-=obj._coef;
    return *this;
}

CMonom CMonom::operator*(const CMonom& obj) const noexcept{
    size_t max = std::max(_size, obj._size);
    CMonom monom = CMonom(_coef*obj._coef, max);
    for (size_t i = 0; i<max; i++){
        if (_size<=i)
            monom._powers[i] = obj._powers[i];
        else if (obj._size<=i)
            monom._powers[i] = _powers[i];
        else
            monom._powers[i] = _powers[i] + obj._powers[i];
    }
    return monom;
}

CMonom& CMonom::operator*=(const CMonom& obj) noexcept{
    _coef *= obj._coef;
    size_t max = std::max(_size, obj._size);
    int* mas = new int[max];
    for (size_t i = 0; i < _size; i++) {
        mas[i] = _powers[i];}
    for (size_t i = 0; i < obj._size; i++) {
        mas[i] += obj._powers[i];}
    delete[] _powers;
    _powers = mas;
    _size = max;
    return *this;
}

CMonom CMonom::operator/(const CMonom& obj) const{
    if (obj._coef == 0)
        throw std::logic_error("you can't divide by zero");
    size_t max = std::max(_size, obj._size);
    CMonom monom = CMonom(_coef/obj._coef, max);
    for (size_t i = 0; i<max; i++){
        if (_size<=i)
            monom._powers[i] = obj._powers[i];
        else if (obj._size<=i)
            monom._powers[i] = _powers[i];
        else
            monom._powers[i] = _powers[i] - obj._powers[i];
    }
    return monom;
}

CMonom& CMonom::operator/=(const CMonom& obj){
    _coef /= obj._coef;
    size_t max = std::max(_size, obj._size);
    int* mas = new int[max];
    for (size_t i = 0; i < _size; i++) {
        mas[i] = _powers[i];}
    for (size_t i = 0; i < obj._size; i++) {
        mas[i] -= obj._powers[i];}
    delete[] _powers;
    _powers = mas;
    _size = max;
    return *this;
}

CMonom CMonom::operator*(const double& value) const noexcept{
    return CMonom(value*_coef, _powers, _size);
}

CMonom& CMonom::operator*=(const double& value) noexcept{
    this->_coef*=value;
    return *this;
}

CMonom CMonom::operator/(const double& value) const{
    if (value == 0)
        throw std::logic_error("you can't divide by zero");
    return CMonom(value/_coef, _powers, _size);
}

CMonom& CMonom::operator/=(const double& value) {
    if (value == 0)
        throw std::logic_error("you can't divide by zero");
    this->_coef/=value;
    return *this;
}

CMonom CMonom::operator-() const noexcept{
    return CMonom(-_coef, _powers, _size);
}

CMonom& CMonom::operator-() noexcept{
    this->_coef*= -1;
    return *this;
}

double CMonom::valuePoint(const double* point) const noexcept{
    double result = _coef;
    for (size_t i = 0; i<_size; i++){
        result *= std::pow(point[i], _powers[i]);
    }
    return result;
}