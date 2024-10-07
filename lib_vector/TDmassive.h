#include "iostream"
#include "algorithm"
#define STEP_CAPACITY 15
#pragma once
#include "exception"

enum State { empty, busy, deleted };

template<typename T>
class TDMassive {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;
public:
    TDMassive();
    TDMassive(const TDMassive& archive);
    TDMassive(const T* arr, const size_t n);
    TDMassive(size_t n, T value = 0);
    TDMassive(const TDMassive& archive, size_t pos, size_t n);
    TDMassive<T>& operator = (const TDMassive <T>& mas);

    const T& operator[](int index) const noexcept;
    T& operator[](int index) noexcept;

    ~TDMassive();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    T* data() const noexcept;

    void overexposure(size_t n = 1) noexcept;

    void overexposure_del() noexcept;

    void push_back(T value) noexcept;

    void pop_back();

    void push_front(T value) noexcept;

    void pop_front();

    TDMassive& insert(T value, size_t pos);

    TDMassive& replace(size_t pos, T new_value);

    TDMassive& remove_all(T value) noexcept;

    TDMassive& remove_first(T value) noexcept;

    TDMassive& remove_last(T value) noexcept;

    TDMassive& remove_by_index(size_t pos);

    size_t find_all(T value) const noexcept;

    size_t find_first(T value) const noexcept;

    size_t find_last(T value) const noexcept;

    void swap(TDMassive& archive) noexcept;

    TDMassive& assign(const TDMassive& archive) noexcept;

    void clear() noexcept;

    void resize(size_t n, T value);

    TDMassive& insert(const T* arr, size_t n, size_t pos);

    TDMassive& erase(size_t pos, size_t n);

    //private:
    //    size_t count_value(T value); ????????
};

template <typename T>
TDMassive<T>::TDMassive() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < STEP_CAPACITY; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
TDMassive<T>::TDMassive(const TDMassive& archive) {
    _data = archive._data;
    _states = archive._states;
    _size = archive._size;
    _capacity = archive._capacity;
    _deleted = archive._deleted;
}

template <typename T>
TDMassive<T>::TDMassive(const T* arr, const size_t n) {
    _size = n;
    _capacity = (n / 15 + 1) * 15;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        if (i < n) {
            _data[i] = arr[i];
            _states[i] = State::busy;
        }
        else {
            _states[i] = State::empty;
        }
    }
}

template <typename T>
TDMassive<T>::TDMassive(size_t n, T value) {
    _size = n;
    _capacity = (n / 15 + 1) * 15;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        if (i < n) {
            _data[i] = value;
            _states[i] = State::busy;
        }
        else {
            _states[i] = State::empty;
        }
    }
}

template <typename T>
TDMassive<T>::TDMassive(const TDMassive& archive, size_t pos, size_t n) {
    _size = n;
    _capacity = (n / 15 + 1) * 15;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        if (i < n) {
            _data[i] = archive._data[i + pos];
            _states[i] = State::busy;
        }
        else {
            _states[i] = State::empty;
        }
    }
}

template<class T>
TDMassive<T>& TDMassive<T>::operator = (const TDMassive <T>& mas) {
    if (&mas != this) {
        _size = mas._size;
        _deleted = mas._deleted;
        _capacity = mas._capacity;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (int i = 0; i < _capacity; i++) {
            if (i < _size) {
                _data[i] = mas._data[i];
                _states[i] = mas._states[i];
            }
            else {
                _states[i] = State::empty;
            }
        }
    }
    return *this;
}

template <typename T>
void TDMassive<T>::print() const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] != State::deleted) {
            std::cout << _data[i];
            if (i != _size - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

template <typename T>
const T& TDMassive<T>::operator[](int index) const noexcept {
    return _data[index];
}

template <typename T>
T& TDMassive<T>::operator[](int index) noexcept {
    return _data[index];
}

template <typename T>
inline bool TDMassive<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
inline bool TDMassive<T>::full() const noexcept {
    return _size == _capacity;
}

template <typename T>
size_t TDMassive<T>::size() const noexcept {
    return _size;
}

template <typename T>
size_t TDMassive<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
T* TDMassive<T>::data() const noexcept {
    return _data;
}

template <typename T>
void TDMassive<T>::overexposure(size_t n) noexcept {
    int* array = new T[_capacity];
    State* mas = new State[_capacity];
    _capacity += (n / 15 + 1) * 15;
    for (size_t i = 0; i < _capacity; i++) {
        if (i < _size) {
            array[i] = _data[i];
            mas[i] = _states[i];
        }
        else {
            mas[i] = State::empty;
        }
    }
    _states = mas;
    _data = array;

}
template <typename T>
void TDMassive<T>::overexposure_del() noexcept {
    int count = 0;
    for (int i = _size - 1; i >= 0; i--) {
        if (_states[i] == State::deleted)
            count++;
        else if (count != 0) {
            for (size_t j = i + count + 1; j < _size; j++) {
                _data[j - count] = _data[j];
                _states[j] = State::empty;
                _states[j - count] = State::busy;
            }
            _size -= count;
            _deleted -= count;
            count = 0;
        }
    }
}

template <typename T>
void TDMassive<T>::push_back(T value) noexcept {
    if (full()) {
        if (_deleted != 0)
            overexposure_del();
        else
            overexposure();
    }
    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;
}

template <typename T>
void TDMassive<T>::pop_back() {
    if (empty()) {
        throw std::logic_error("empty!");
    }
    _states[_size - 1] = State::empty;
    _size--;
}

template <typename T>
void TDMassive<T>::push_front(T value) noexcept {
    if (full()) {
        if (_deleted != 0)
            overexposure_del();
        else
            overexposure();
    }
    _size++;
    for (int i = _size; i > 0; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[0] = value;
    _states[0] = State::busy;
}

template <typename T>
void TDMassive<T>::pop_front() {
    if (empty()) {
        throw std::logic_error("empty!");
    }
    if (_states[0] != State::deleted) {
        if (_size == 1) {
            _states[0] = State::empty;
            _size--;
        }
        else {
            _states[0] = State::deleted;
            _deleted += 1;
        }
    }
    if (double(_deleted) * 100 / double(_size) >= 40) {
        overexposure_del();
    }
}

template <typename T>
TDMassive<T>& TDMassive<T>::insert(T value, size_t pos) {
    if (_size < pos) {
        throw std::logic_error("Error in function \
\"TArchive<T>& insert(T value, size_t pos)\": wrong position value.");
    }
    if (full()) {
        if (_deleted != 0)
            overexposure_del();
        else
            overexposure();
    }
    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i - 1];
    }
    _data[pos] = value;
    _states[pos] = State::busy;
    _size++;
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::replace(size_t pos, T new_value) {
    if (pos<0 || pos>_size - 1) {
        throw std::logic_error("wrong pos!");
    }
    _data[pos] = new_value;
    if (_states[pos] == State::deleted)
        _deleted--;
    _states[pos] = State::busy;
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::remove_all(T value) noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) {
            if (i == _size - 1) {
                _states[i] = State::empty;
                _size--;
            }
            else {
                _states[i] = State::deleted;
                _deleted += 1;
            }
        }
    }
    if (double(_deleted) * 100 / double(_size) >= 40) {
        overexposure_del();
    }
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::remove_first(T value) noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) {
            if (i == _size - 1) {
                _states[i] = State::empty;
                _size--;
            }
            else {
                _states[i] = State::deleted;
                _deleted += 1;
            }
            break;
        }
    }
    if (double(_deleted) * 100 / double(_size) >= 40) {
        overexposure_del();
    }
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::remove_last(T value) noexcept {
    for (size_t i = _size - 1; i >= 0; i--) {
        if (_data[i] == value) {
            if (i == _size - 1) {
                _states[i] = State::empty;
                _size--;
            }
            else {
                _states[i] = State::deleted;
                _deleted += 1;
            }
            break;
        }
    }
    if (double(_deleted) * 100 / double(_size) >= 40) {
        overexposure_del();
    }
    return *this;
}


template <typename T>
TDMassive<T>& TDMassive<T>::remove_by_index(size_t pos) {
    if (pos<0 || pos>_size - 1) {
        throw std::logic_error("wrong pos!");
    }
    if (_size == pos + 1) {
        _states[pos] = State::empty;
        _size--;
    }
    else {
        _states[pos] = State::deleted;
        _deleted += 1;
    }
    if (double(_deleted) * 100 / double(_size) >= 40) {
        overexposure_del();
    }
    return *this;
}

template <typename T>
size_t TDMassive<T>::find_all(T value) const noexcept {
    size_t total = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) total++;
    }
    return total;
}

template <typename T>
size_t TDMassive<T>::find_first(T value) const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) return i;
    }
}

template <typename T>
size_t TDMassive<T>::find_last(T value) const noexcept {
    for (size_t i = _size - 1; i >= 0; i--) {
        if (_data[i] == value) return i;
    }
}

template <typename T>
void TDMassive<T>::swap(TDMassive& archive) noexcept {
    T* temp_data = _data;
    _data = archive._data;
    archive._data = temp_data;

    State* temp_states = _states;
    _states = archive._states;
    archive._states = temp_states;

    size_t temp_size = _size;
    _size = archive._size;
    archive._size = temp_size;

    size_t temp_capacity = _capacity;
    _capacity = archive._capacity;
    archive._capacity = temp_capacity;
}

template <typename T>
TDMassive<T>& TDMassive<T>::assign(const TDMassive& archive) noexcept {
    _size = archive._size;
    _deleted = archive._deleted;
    _capacity = archive._capacity;
    delete[] _data; delete[] _states;
    _data = new T[_capacity]; _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        if (i < _size) {
            _data[i] = archive._data[i];
            _states[i] = archive._states[i];
        }
        else {
            _states[i] = State::empty;
        }
    }
    return *this;
}

template <typename T>
TDMassive<T>::~TDMassive() {
    delete[] _data;
    _data = nullptr;
}

template <typename T>
void TDMassive<T>::clear() noexcept {
    _deleted = 0;
    _size = 0;
    _capacity = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
}

template <typename T>
void TDMassive<T>::resize(size_t n, T value) {
    if (n <= 0)
        throw std::logic_error("wrong n!");
    else if (n >= _capacity) {
        overexposure(n);
    }
    _size = n;
    for (int i = 0; i < _capacity; i++) {
        if (i < _size) {
            _data[i] = value;
            if (_states[i] == State::deleted)
                _deleted--;
            _states[i] = State::busy;
        }
        else {
            _states[i] = State::empty;
        }
    }
}

template <typename T>
TDMassive<T>& TDMassive<T>::insert(const T* arr, size_t n, size_t pos) {
    if (_capacity < _size + n) {
        if (n <= _deleted) {
            overexposure_del();
        }
        else {
            overexposure(n);
        }
    }

    for (int i = _size - 1; i >= pos; i--) {
        _data[i + n] = _data[i];
        _states[i + n] = _states[i];
    }
    for (int i = pos; i < pos + n; i++) {
        _data[i] = arr[i - pos];
        _states[i] = State::busy;
    }
    _size += n;
}

template <typename T>
TDMassive<T>& TDMassive<T>::erase(size_t pos, size_t n) {
    if (pos >= _size)
        return *this;
    for (int i = pos; i <= n; i++) {
        if (i < _size) {
            _states[i] = State::deleted;
            _deleted++;
        }
        else
            break;
    }
}





