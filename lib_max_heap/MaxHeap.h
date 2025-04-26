#include "exception"
#include "../lib_dmassive/TDmassive.h"
#include "../lib_heap/heap.h"

template <class T>
class MaxHeap : public Heap<T> {
public:
	MaxHeap(size_t size = 0);
	MaxHeap(size_t size, const T* data);
	MaxHeap(const MaxHeap<T>& heap);
	MaxHeap<T>& operator=(const MaxHeap<T>& heap);
	void emplace(size_t index, T value);
	inline T max() const;
	T remove_max();
private:
	void sift_down(size_t index) noexcept;
	void sift_up(size_t index) noexcept;
	void max_heapify() noexcept;
};

template <class T>
MaxHeap<T>::MaxHeap(size_t size) {
	_data = TDMassive<T>(size);
	_size = 0;
}

template <class T>
MaxHeap<T>::MaxHeap(size_t size, const T* data) {
	_size = size;
	_data = TDMassive<T>(data, size);
	max_heapify();
}

template <class T>
MaxHeap<T>::MaxHeap(const MaxHeap& heap) {
	_data = heap._data;
	_size = heap._size;
}

template <class T>
MaxHeap<T>& MaxHeap<T>::operator=(const MaxHeap<T>& heap) {
	if (&heap != this) {
		_data = heap._data;
		_size = heap._size;
	}
	return *this;
}

template <class T>
void MaxHeap<T>::emplace(size_t index, T value) {
	if (index < 0 || index >= _size)
		throw std::logic_error("incorrect index");
	_data[index] = value;
	if (_data[index] > _data[this->parent(index)]) 
		this->sift_up(index);
	else if (index < _size / 2)
		this->sift_down(index);
}

template <class T>
T MaxHeap<T>::max() const {
	if (this->is_empty())
		throw std::logic_error("incorrect operation");
	return _data[0];
}

template <class T>
T MaxHeap<T>::remove_max() {
	if (this->is_empty())
		throw std::logic_error("incorrect operation");
	T max_value = _data[0];
	_data[0] = _data[_size - 1];
	_data.pop_back();
	_size--;
	if (_size!=0)
		this->sift_down(0);
	return max_value;
}

template <class T>
void MaxHeap<T>::sift_down(size_t index) noexcept {
	while (this->left(index) < _size) {
		int max_child;
		if (this->right(index) < _size && _data[this->right(index)] > _data[this->left(index)])
			max_child = this->right(index);
		else
			max_child = this->left(index);
		if (_data[index] >= _data[max_child])
			break;
		T copy = _data[index];
		_data[index] = _data[max_child];
		_data[max_child] = copy;
		index = max_child;
	}
}

template <class T>
void MaxHeap<T>::sift_up(size_t index) noexcept {
	while (index > 0) {
		if (_data[index] <= _data[this->parent(index)])
			break;
		T copy = _data[index];
		_data[index] = _data[this->parent(index)];
		_data[this->parent(index)] = copy;
		index = this->parent(index);
	}
}

template <class T>
void MaxHeap<T>::max_heapify() noexcept {
	for (int i = _size / 2 - 1; i >= 0; i--) {
		this->sift_down(i);
	}
}

template <class T>
void reverse_sorted(T*& massive, size_t size) {
	MaxHeap<T> heap(size, massive);
	delete[] massive;
	massive = new T[size];
	for (size_t i = 0; i < size; i++) {
		massive[i] = heap.remove_max();
	}
}