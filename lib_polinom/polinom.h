#include "iostream"
#include "algorithm"
#include "string"
#include "monom.h"
#include "exception"
#include "../lib_list/list.h"
#include "../lib_list/node.h"
#include "../lib_dmassive/TDmassive.h"

class CPolinom {
public:
    size_t _size;
    char* _names;
    Tlist<CMonom> _monoms;

    CPolinom(std::string str, size_t size = 3);

    CPolinom(const char* mas, size_t size = 3);

    CPolinom(size_t size);

    CPolinom();

    CPolinom& operator=(const CPolinom& obj);

    CPolinom(const CPolinom& obj);

    void fillVar();

    ~CPolinom();

    void parse(std::string str);

    void appendPolinom(const CMonom& obj);

    void calculate();

    void valuePoint();

    CPolinom operator+(const CMonom& obj) const;

    CPolinom& operator+=(const CMonom& obj);

    CPolinom operator-(const CMonom& obj) const;

    CPolinom& operator-=(const CMonom& obj);

    CPolinom operator*(const CMonom& obj) const;

    CPolinom& operator*=(const CMonom& obj);

    CPolinom operator/(const CMonom& obj) const;

    CPolinom& operator/=(const CMonom& obj);

    CPolinom operator+(const CPolinom& obj) const;

    CPolinom& operator+=(const CPolinom& obj);

    CPolinom operator-(const CPolinom& obj) const;

    CPolinom& operator-=(const CPolinom& obj);

    CPolinom operator*(const CPolinom& obj) const;

    CPolinom operator/(const CPolinom& obj) const;

    bool operator==(const CPolinom& obj) const;

    bool operator!=(const CPolinom& obj) const;

    bool isVariable(const CMonom& obj) const;

    friend std::istream& operator >> (std::istream& in, CPolinom& polinom) {
        size_t size;
        std::string str;
        std::cout << "Enter the number of variables of the polynomial: "; std::cin >> size;
        std::cout << "Polinom: " << "F(";
        for (size_t i = 0; i < size; i++) {
            std::cout << static_cast<char>(i + 97);
            if (i != size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ") = "; std::cin >> str;
        polinom = CPolinom(str, size);
        return in;
    }

    void calculator(const CPolinom& polinom) const;

    void calculator(const CMonom& monom) const;

    friend std::ostream& operator<<(std::ostream& out, const CPolinom& polinom) {
        auto next = polinom._monoms.begin(); 
        if (polinom._monoms.get_size() == 0) {
            std::cout << 0 << std::endl;
            return out;
        }
        next++;
        for (auto it = polinom._monoms.begin(); it != polinom._monoms.end(); it++) {
            if ((*it)._coef == -1) {
                out << "-";
                if (polinom.isVariable((*it)) == false)
                    out << "1";
            }
            else if ((*it)._coef == 1) {
                if (it != polinom._monoms.begin())
                    out << "+";
                if (polinom.isVariable((*it)) == false)
                    out << "1";
            }
            else {
                if ((it != polinom._monoms.begin()) && (*it)._coef > 0)
                    out << "+";
                out << (*it)._coef;
            }
            for (size_t i = 0; i < polinom._size; i++) {
                if ((*it)._powers[i] != 0) {
                    if ((*it)._powers[i] == 1)
                        out << polinom._names[i];
                    else
                        out << polinom._names[i] << "^" << (*it)._powers[i];
                }
            }
            if (next != polinom._monoms.end()) {
                next++;
            }
        }
        out << std::endl;
        return out;
    }
};

CPolinom::CPolinom(std::string str, size_t size) {
    _size = size;
    _names = new char[_size];
    fillVar();
    parse(str);
}

CPolinom::CPolinom(const char* mas, size_t size) {
    _size = size;
    _names = new char[_size];
    fillVar();
    parse(std::string(mas));
}

CPolinom::CPolinom(size_t size) {
    _size = size;
    _names = new char[_size];
    fillVar();
}

CPolinom::CPolinom() {
    _size = 3;
    _names = new char[_size];
    fillVar();
}

CPolinom& CPolinom::operator=(const CPolinom& obj) {
    if (this != &obj) {
        delete[] _names;
        _size = obj._size;
        _names = new char[_size];
        std::copy(obj._names, obj._names + _size, _names);
        _monoms = obj._monoms;
    }
    return *this;
}

CPolinom::CPolinom(const CPolinom& obj) {
    _size = obj._size;
    _names = new char[_size];
    std::copy(obj._names, obj._names + _size, _names);
    _monoms = obj._monoms;
}

void CPolinom::fillVar() {
    for (size_t i = 97; i < 97 + _size; i++) {
        _names[i - 97] = static_cast<char>(i);
    }
}

CPolinom::~CPolinom() {
    delete[] _names;
}

void CPolinom::parse(std::string str) {
    TDMassive<std::string> list;
    std::string monom;
    for (auto it = str.begin(); it != str.end(); it++) {
        if ((*it) == '+' || (*it) == '-') {
            if (!monom.empty())
                list.push_back(monom);
            if ((*it) == '-')
                monom = (*it);
            else
                monom.clear();
        }
        else if ((*it) == '*' || (*it) == '/') {
            if (!monom.empty())
                list.push_back(monom);
            std::string s(1, (*it));
            list.push_back(s);
            monom.clear();
        }
        else {
            if ((*it) != '(' && (*it) != ')')
                monom += (*it);
        }
    }
    if (!monom.empty())
        list.push_back(monom);
    for (int i = 0; i < list.size(); i++) {
        if (list[i + 1] == "*" || list[i + 1] == "/") {
            if (list[i + 1] == "*")
                appendPolinom(CMonom(list[i], _names, _size) * CMonom(list[i + 2], _names, _size));
            else
                appendPolinom(CMonom(list[i], _names, _size) / CMonom(list[i + 2], _names, _size));
            i += 2;
        }
        else {
            CMonom c = CMonom(list[i], _names, _size);
            appendPolinom(c);
        }
    }
    this->calculate();
}

void CPolinom::appendPolinom(const CMonom& obj) {
    if (_monoms.isEmpty()) {
        _monoms.push_back(obj);
    }
    else {
        size_t index = 0;
        bool flag = false;
        for (auto it = _monoms.begin(); it != _monoms.end(); it++, index++) {
            if (obj > (*it) || obj == (*it)) {
                _monoms.insert(index, obj);
                flag = true;
                break;
            }
        }
        if (flag == false)
            _monoms.push_back(obj);
    }
}

void CPolinom::calculate() {
    auto cur = _monoms.begin();
    auto next = _monoms.begin(); next++;
    CPolinom pol(_size);
    CMonom mon = (*cur);
    while (cur != _monoms.end()) {
        if (next != _monoms.end() && (*cur) == (*next)) {
            mon = (*cur);
            mon += (*next);
        }
        else {
            if (!mon.is_null())
                pol.appendPolinom(mon);
            if (next != _monoms.end()) {
                cur = next;
                mon = (*cur);
            }
            else
                break;
        }
        next++;
    }
    (*this) = pol;
}

void CPolinom::valuePoint() {
    float* mas = new float[_size];
    for (size_t i = 0; i < _size; i++) {
        std::cout << "Enter the value " << _names[i] << ": ";
        std::cin >> mas[i];
    }
    float result = 0;
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        result += (*it).valuePoint(mas);
    }
    std::cout << "Result = " << result << std::endl;
    delete[] mas;
}

CPolinom CPolinom::operator+(const CMonom& obj) const {
    if (obj._size != _size)
        throw std::logic_error("incorrect addition of polynomials");
    CPolinom polinom(*this);
    polinom.appendPolinom(obj);
    polinom.calculate();
    return polinom;
}

CPolinom& CPolinom::operator+=(const CMonom& obj) {
    if (obj._size != _size)
        throw std::logic_error("incorrect addition of polynomials");
    this->appendPolinom(obj);
    this->calculate();
    return *this;
}

CPolinom CPolinom::operator-(const CMonom& obj) const {
    if (obj._size != _size)
        throw std::logic_error("incorrect addition of polynomials");
    CPolinom polinom(*this);
    polinom.appendPolinom(obj * (-1));
    polinom.calculate();
    return polinom;
}

CPolinom& CPolinom::operator-=(const CMonom& obj) {
    if (obj._size != _size)
        throw std::logic_error("incorrect addition of polynomials");
    this->appendPolinom(obj * (-1));
    this->calculate();
    return *this;
}

CPolinom CPolinom::operator*(const CMonom& obj) const {
    CPolinom polinom(std::max(_size, obj._size));
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        polinom.appendPolinom((*it) * obj);
    }
    polinom.calculate();
    return polinom;
}

CPolinom& CPolinom::operator*=(const CMonom& obj) {
    if (_size != obj._size) {
        _size = std::max(_size, obj._size);
        this->fillVar();
    }
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        this->appendPolinom((*it) * obj);
    }
    this->calculate();
    return *this;
}

CPolinom CPolinom::operator/(const CMonom& obj) const {
    CPolinom polinom(std::max(_size, obj._size));
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        polinom.appendPolinom((*it) / obj);
    }
    polinom.calculate();
    return polinom;
}

CPolinom& CPolinom::operator/=(const CMonom& obj) {
    if (_size != obj._size) {
        _size = std::max(_size, obj._size);
        this->fillVar();
    }
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        this->appendPolinom((*it) / obj);
    }
    this->calculate();
    return *this;
}

CPolinom CPolinom::operator+(const CPolinom& obj) const {
    if (_size != obj._size)
        throw std::logic_error("incorrect addition of polynomials");
    CPolinom polinom = (*this);
    for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
        polinom = polinom + (*it);
    }
    return polinom;
}

CPolinom& CPolinom::operator+=(const CPolinom& obj) {
    if (_size != obj._size)
        throw std::logic_error("incorrect addition of polynomials");
    for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
        (*this) += (*it);
    }
    return *this;
}

CPolinom CPolinom::operator-(const CPolinom& obj) const {
    if (_size != obj._size)
        throw std::logic_error("incorrect addition of polynomials");
    CPolinom polinom = (*this);
    for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
        polinom = polinom - (*it);
    }
    return polinom;
}

CPolinom& CPolinom::operator-=(const CPolinom& obj) {
    if (_size != obj._size)
        throw std::logic_error("incorrect addition of polynomials");
    for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
        (*this) -= (*it);
    }
    return *this;
}

CPolinom CPolinom::operator*(const CPolinom& obj) const {
    CPolinom polinom(std::max(_size, obj._size));
    for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
        polinom += (*this) * (*it);
    }
    return polinom;
}

CPolinom CPolinom::operator/(const CPolinom& obj) const {
    CPolinom polinom(std::max(_size, obj._size));
    CPolinom copy = (*this);
    CMonom obj_head = obj._monoms._head->value();
    while (!copy._monoms.isEmpty() && (copy._monoms._head->value() > obj_head || copy._monoms._head->value() == obj_head)) {
        CMonom copy_head = copy._monoms._head->value();
        CMonom del = copy_head / obj_head;
        copy -= obj * del;
        polinom.appendPolinom(del);
    }
    // polinom+=copy;
    return polinom;
}

bool CPolinom::operator==(const CPolinom& obj) const {
    if (_size != obj._size)
        return false;
    auto ot = obj._monoms.begin();
    for (auto it = _monoms.begin(); it != _monoms.end(); it++, ot++) {
        if ((*it) != (*ot) || (*it)._coef != (*ot)._coef)
            return false;
    }
    return true;
}

bool CPolinom::operator!=(const CPolinom& obj) const {
    return !((*this) == obj);
}

bool CPolinom::isVariable(const CMonom& obj) const {
    for (size_t i = 0; i < obj._size; i++) {
        if (obj._powers[i] != 0)
            return true;
    }
    return false;
}

void CPolinom::calculator(const CPolinom& polinom) const {
    char op;
    std::cout << "Enter the operation (+,-,*,/): ";
    std::cin >> op;
    if (op == '+')
        std::cout << (*this) + polinom;
    else if (op == '-')
        std::cout << (*this) - polinom;
    else if (op == '*')
        std::cout << (*this) * polinom;
    else
        std::cout << (*this) / polinom;
}

void CPolinom::calculator(const CMonom& monom) const {
    char op;
    std::cout << "Enter the operation (+,-,*,/): ";
    std::cin >> op;
    if (op == '+')
        std::cout << (*this) + monom;
    else if (op == '-')
        std::cout << (*this) - monom;
    else if (op == '*')
        std::cout << (*this) * monom;
    else
        std::cout << (*this) / monom;
}