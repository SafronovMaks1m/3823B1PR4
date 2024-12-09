#include <iostream>
#include <stdexcept>
#include "../lib_list/list.h"
#define MAX 5

template <class T>
class TLStack {
public:
    int _size;
    Tlist<T> _data;
public:
    TLStack(int n = MAX) {
        _size = n;
    }

    inline bool isEmpty() const noexcept; 

    inline bool isFull() const noexcept;

    void push(const T& val);

    void pop();

    TNode<T>* top() const noexcept;
};

template <class T>
inline bool TLStack<T>::isEmpty() const noexcept {
    return _data.get_size() == 0;
}

template <class T>
inline bool TLStack<T>::isFull() const noexcept {
    return _data.get_size() == _size;
}

template<class T>
void TLStack<T>::push(const T& val) {
    if (isFull()) {
        throw std::overflow_error("TStack is full");
    }
    _data.push_front(val);
}

template <class T>
void TLStack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("TStack is empty");
    }
    _data.pop_front();
}

template <class T>
TNode<T>* TLStack<T>::top() const noexcept {
    return _data._head;
}