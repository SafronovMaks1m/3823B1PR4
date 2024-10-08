#include <iostream>
#include <stdexcept>

template <class T>
class TStack {
public:
    T* _data;
    size_t _size;
    size_t _top;
public:
    TStack(size_t size = 20);

    ~TStack();

    inline bool isEmpty() const noexcept;//���� ����� ��� vector _data.size() == 0  

    inline bool isFull() const noexcept;

    void push(T val); //���������� �� �� ���� �� ��� �������  

    //void push ������ ��� vector  

    void pop();

    int top();
};

template <class T>
TStack<T>::TStack(size_t size) {
    _data = new T[size];
    _size = size;
    _top = -1;
}

template <class T>
TStack<T>::~TStack() {
    delete[] _data;
    _data = nullptr;
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
    _top += 1;
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