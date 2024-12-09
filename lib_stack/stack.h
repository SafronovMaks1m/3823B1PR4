#include <iostream>
#include <stdexcept>
#include "../lib_dmassive/TDmassive.h"
#pragma once

template <class T>
class TStack {
public:
    TDMassive<T> _data;
    size_t _size;
    size_t _top;
public:
    TStack(size_t size = 20);

    inline bool isEmpty() const noexcept;//тоже самое для vector _data.size() == 0  

    inline bool isFull() const noexcept;

    void push(T val); //исклюсение на то есть ли там элемент  

    //void push только для vector  

    void pop();

    int top();
};

template <class T>
TStack<T>::TStack(size_t size) {
    _data = TDMassive<T>(size);
    _size = size;
    _top = -1;
}

template <class T>
inline bool TStack<T>::isEmpty() const noexcept {
    return _top == -1;
}

template <class T>
inline bool TStack<T>::isFull() const noexcept {
    return _top == _size - 1;
}

template<class T>
void TStack<T>::push(T val) {
    if (isFull()) {
        throw std::overflow_error("TStack is full");
    }
    _top++;
    _data[_top] = val;
}

template <class T>
void TStack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("TStack is empty");
    }
    _top--;
}

template <class T>
int TStack<T>::top() {
    return _data[_top];
}