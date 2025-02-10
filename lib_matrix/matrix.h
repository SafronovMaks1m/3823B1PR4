#include "iostream"
#include "../lib_matrix/TVector.h"
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
            _array[i] = TVector<T>(size - i, 0, i);
            for (size_t j = 0; j < size; j++) {
                _array[i][j] = arr[i][j];
            }
        }
    }

    TUpperTriangularMatrix(const TUpperTriangularMatrix& m) : TVector<TVector<T>>(m) {}
    TUpperTriangularMatrix(const TVector<TVector<T>>& m) : TVector<TVector<T>>(m) {}
    ~TUpperTriangularMatrix() {}

    size_t size() const { return _array.size(); }

    using TVector<TVector<T>>::operator=;

    TUpperTriangularMatrix& operator+=(const TUpperTriangularMatrix& other) {
        *this = this->TVector<TVector<T>>::operator+(other);
        return *this;
    }

    const TVector<T>& operator[](int index) const noexcept {
        return _array[index];
    }

    TVector<T>& operator[](int index) noexcept {
        return _array[index];
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
            for (size_t k = 0; k < size(); k++) {
                matrix[i][j] += _array[i][k] * other._array[k][j];
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
        det *= _array[i][i];
    }
    return det;
}

template<class T>
std::ostream& operator << (std::ostream& out, const TUpperTriangularMatrix<T>& m) {
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m.size(); j++) {
            out << m[i][j] << " ";
        }
        out << "\n";
    }
    std::cout << std::endl;
    return out;
}