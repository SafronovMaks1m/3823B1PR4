#include "exception"
#include "../lib_dmassive/TDmassive.h"
#include "../lib_heap/heap.h"

template <class T>
class MinHeap : public Heap<T> {
public:
	MinHeap(size_t size = 0);
	MinHeap(size_t size, const T* data);
	MinHeap(const MinHeap<T>& heap);
	MinHeap<T>& operator=(const MinHeap<T>& heap);
	void emplace(size_t index, T value);
	inline T min() const;
	T remove_min();
private:
	void sift_down(size_t index) noexcept;
	void sift_up(size_t index) noexcept;
	void min_heapify() noexcept;
};

template <class T>
MinHeap<T>::MinHeap(size_t size) {
	_data = TDMassive<T>(size);
	_size = 0;
}

template <class T>
MinHeap<T>::MinHeap(size_t size, const T* data) {
	_size = size;
	_data = TDMassive<T>(data, size);
	min_heapify();
}

template <class T>
MinHeap<T>::MinHeap(const MinHeap& heap) {
	_data = heap._data;
	_size = heap._size;
}

template <class T>
MinHeap<T>& MinHeap<T>::operator=(const MinHeap<T>& heap) {
	if (&heap != this) {
		_data = heap._data;
		_size = heap._size;
	}
	return *this;
}

template <class T>
void MinHeap<T>::emplace(size_t index, T value) {
	if (index < 0 || index >= _size)
		throw std::logic_error("incorrect index");
	_data[index] = value;
	if (_data[index] < _data[this->parent(index)])
		this->sift_up(index);
	else if (index < _size / 2)
		this->sift_down(index);
}

template <class T>
T MinHeap<T>::min() const {
	if (this->is_empty())
		throw std::logic_error("incorrect operation");
	return _data[0];
}

template <class T>
T MinHeap<T>::remove_min() {
	if (this->is_empty())
		throw std::logic_error("incorrect operation");
	T min_value = _data[0];
	_data[0] = _data[_size - 1];
	_data.pop_back();
	_size--;
	if (_size!=0)
		this->sift_down(0);
	return min_value;
}

template <class T>
void MinHeap<T>::sift_down(size_t index) noexcept {
	while (this->left(index) < _size) {
		int min_child;
		if (this->right(index) < _size && _data[this->right(index)] < _data[this->left(index)])
			min_child = this->right(index);
		else
			min_child = this->left(index);
		if (_data[index] <= _data[min_child])
			break;
		T copy = _data[index];
		_data[index] = _data[min_child];
		_data[min_child] = copy;
		index = min_child;
	}
}

template <class T>
void MinHeap<T>::sift_up(size_t index) noexcept {
	while (index > 0) {
		if (_data[index] >= _data[this->parent(index)])
			break;
		T copy = _data[index];
		_data[index] = _data[this->parent(index)];
		_data[this->parent(index)] = copy;
		index = this->parent(index);
	}
}

template <class T>
void MinHeap<T>::min_heapify() noexcept {
	for (int i = _size / 2 - 1; i >= 0; i--) {
		this->sift_down(i);
	}
}

template <class T>
void sorted(T*& massive, size_t size){
	MinHeap<T> heap(size, massive);
	delete[] massive;
	massive = new T[size];
	for (size_t i = 0; i < size; i++) {
		massive[i] = heap.remove_min();
	}
}