#include "../lib_DMassive/TDmassive.h"
#include "iostream"
#include <math.h>
#include "exception"

template<class T>
class TVector{
    private:
        TDMassive<T> _array;
    public:
        TVector(const size_t size = 5);
        TVector(const T* mas, const size_t size);
        TVector(const TVector& vector);
        TVector<T>& operator = (const TVector <T>& vector);
        void check_lenght(const size_t len) const;
        const T& operator[](int index) const noexcept;
        T& operator[](int index) noexcept;
        size_t size() const noexcept;
        TVector<T> operator+(const TVector<T>& obj) const noexcept;
        TVector<T> operator-(const TVector<T>& obj) const noexcept;
        TVector<T>& operator += (const TVector<T>& obj) noexcept;
        TVector<T>& operator -= (const TVector<T>& obj) noexcept;
        int operator *(const TVector<T>& obj) const noexcept;
        TVector<T>& operator *=(const T& value) noexcept;
        TVector<T> operator *(const T& value) const noexcept;
        double search_length() const noexcept;
        bool operator == (const TVector<T>& obj) const noexcept;
        bool operator != (const TVector<T>& obj) const noexcept;
        void print() const noexcept;
        template <class T>
        friend std::istream& operator >> (std::istream& in, TVector<T>& vector) {
            T value = 0;
            std::cout << "¬ведите " << vector.size() << " чисел: ";
            for (int i = 0; i < vector.size(); i++) {
                in >> value;
                vector[i] = value;
            }
            std::cout << std::endl;
            return in;
        }
};

template <class T>
TVector<T>::TVector(const size_t size){
    _array = TDMassive<T>(size);
}

template <class T>
TVector<T>::TVector(const T* mas, const size_t size){
    _array = TDMassive<T>(mas, size);
}

template <class T>
TVector<T>::TVector(const TVector& vector){
    _array = vector._array; 
}

template <class T>
TVector<T>& TVector<T>::operator =(const TVector <T>& vector){
    _array = vector._array;
    return *this;
}

template <class T>
void TVector<T>::check_lenght(const size_t len) const{
    if (size()!=len)
        throw std::logic_error("the length of the vectors does not match");
}

template <class T>
const T& TVector<T>::operator[](int index) const noexcept{
    return _array[index];
}

template <class T>
T& TVector<T>::operator[](int index) noexcept{
    return _array[index];
}

template <class T>
size_t TVector<T>::size() const noexcept{
    return _array.size();
}

template <class T>
TVector<T> TVector<T>::operator+(const TVector<T>& obj) const noexcept{
    check_lenght(obj.size());
    TVector<T> new_vector = TVector(size());
    for (size_t i = 0; i<size(); i++){
        new_vector[i] = _array[i]+obj[i];
    }
    return new_vector;
}

template <class T>
TVector<T> TVector<T>::operator-(const TVector<T>& obj) const noexcept{
    check_lenght(obj.size());
    TVector<T> new_vector = TVector(size());
    for (size_t i = 0; i<size(); i++){
        new_vector[i] = _array[i]-obj[i];
    }
    return new_vector;
}

template <class T>
TVector<T>& TVector<T>::operator+=(const TVector<T>& obj) noexcept{
    check_lenght(obj.size());
    for (size_t i = 0; i<size(); i++){
        _array[i]+= obj[i];
    }
    return *this;
}

template <class T>
TVector<T>& TVector<T>::operator-=(const TVector<T>& obj) noexcept{
    check_lenght(obj.size());
    for (size_t i = 0; i<size(); i++){
        _array[i]-= obj[i];
    }
    return *this;
}

template <class T>
int TVector<T>::operator *(const TVector<T>& obj) const noexcept{
    check_lenght(obj.size());
    T s = 0;
    for (size_t i = 0; i<size(); i++){
        s+=_array[i]*obj[i];
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
double TVector<T>::search_length() const noexcept{
    return sqrt(double(operator*(*this)));
}

template <class T>
bool TVector<T>::operator==(const TVector<T>& obj) const noexcept{
    check_lenght(obj.size());
    for (size_t i = 0; i<size(); i++){
        if (_array[i]!=obj[i]){
            return false;
        }
    }
    return true;
}

template <class T>
bool TVector<T>::operator!=(const TVector<T>& obj) const noexcept{
    check_lenght(obj.size());
    return !(this->operator==(obj));
}

template <class T>
void TVector<T>::print() const noexcept{
    _array.print();
}




