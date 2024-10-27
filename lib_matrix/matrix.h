#include "iostream"
#include "../lib_vector/TVector.h"
#define STEP_CAPACITY 15

template <class T>
class TUpperTriangularMatrix : TVector<TVector<T>> {
private:
    using TVector<TVector<T>>::_array;
    using TVector<TVector<T>>::_start_index;
public:
    TUpperTriangularMatrix(size_t size = STEP_CAPACITY, int value = 0) : TVector<TVector<T>>(size) {
        for (size_t i = 0; i < size; i++) {
            _array[i] = TVector<T>(size - i, value, i);
        }
    }

    TUpperTriangularMatrix(T const* const* arr, size_t size) : TVector<TVector<T>>(size) {
        for (size_t i = 0; i < size; i++) {
            _array[i] = TVector<T>(size - i, i);
            for (size_t j = 0; j < size - i; j++) {
                _array[i][j] = arr[i][j + i];
            }
        }
    }

    TUpperTriangularMatrix(const TUpperTriangularMatrix& m) : TVector<TVector<T>>(m) {}
    TUpperTriangularMatrix(const TVector<TVector<T>>& m) : TVector<TVector<T>>(m) {}
    ~TUpperTriangularMatrix() {}

    size_t size() const { return _array.size(); }

    using TVector<TVector<T>>::operator[];
    using TVector<TVector<T>>::operator=;

    TUpperTriangularMatrix& operator+=(const TUpperTriangularMatrix& other) {
        *this = this->TVector<TVector<T>>::operator+(other);
        return *this;
    }

    TUpperTriangularMatrix operator+(const TUpperTriangularMatrix& other) {
        return TVector<TVector<T>>::operator+(other);
    }

    TUpperTriangularMatrix& operator-=(const TUpperTriangularMatrix& other) {
        *this = this->TVector<TVector<T>>::operator-(other);
        return *this;
    }

    TUpperTriangularMatrix operator-(const TUpperTriangularMatrix& other) {
        return TVector<TVector<T>>::operator-(other);
    }

    TUpperTriangularMatrix operator*(const TUpperTriangularMatrix& other) const;

    TUpperTriangularMatrix operator*(const T& value) const;

    TUpperTriangularMatrix& operator*=(const T& value);

    T serch_det() const noexcept;

    bool operator==(const TUpperTriangularMatrix<T>& obj) const {
        return TVector<TVector<T>>::operator==(obj);
    }

    bool operator!=(const TUpperTriangularMatrix<T>& obj) const {
        return TVector<TVector<T>>::operator!=(obj);
    }
};

template <class T>
TUpperTriangularMatrix<T> TUpperTriangularMatrix<T>::operator*(const TUpperTriangularMatrix& other) const {
    TUpperTriangularMatrix matrix = TUpperTriangularMatrix(size());
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            for (size_t k = _array[i].start_index(); k < 1 + j; k++) {
                matrix[i][j - _array[i].start_index()] += _array[i][k - _array[i].start_index()] * other._array[k][j - other._array[k].start_index()];
            }
        }
    }
    return matrix;
}

template <class T>
TUpperTriangularMatrix<T> TUpperTriangularMatrix<T>::operator*(const T& value) const {
    TUpperTriangularMatrix matrix = TUpperTriangularMatrix(size());
    for (size_t i = 0; i < size(); i++) {
        matrix[i] = _array[i] * value;
    }
    return matrix;
}

template <class T>
TUpperTriangularMatrix<T>& TUpperTriangularMatrix<T>::operator*=(const T& value) {
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] *= value;
    }
    return *this;
}

template <class T>
T TUpperTriangularMatrix<T>::serch_det() const noexcept {
    T det = 1;
    for (size_t i = 0; i < size(); i++) {
        det *= _array[i][0];
    }
    return det;
}

template<class T>
std::ostream& operator << (std::ostream& out, const TUpperTriangularMatrix<T>& m) {
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m.size(); j++) {
            if (j < i) { out << 0 << " "; }
            else { out << m[i][j - i] << " "; }
        }
        out << "\n";
    }
    std::cout << std::endl;
    return out;
}