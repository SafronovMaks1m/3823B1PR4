#pragma once

template <class T>
class AVLTreeNode {
	T _value;
	size_t _hight;
	AVLTreeNode<T>* _left;
	AVLTreeNode<T>* _right;
	AVLTreeNode<T>* _parent;
public:
	AVLTreeNode(T value, size_t hight = 0, AVLTreeNode<T>* left = nullptr, AVLTreeNode<T>* right = nullptr, AVLTreeNode<T>* parent = nullptr);
	AVLTreeNode(const AVLTreeNode<T>& node);
	AVLTreeNode<T>& operator = (const AVLTreeNode <T>& node);
	const T& value() const noexcept;
	const size_t& hight() const noexcept;
	AVLTreeNode<T>* left();
	AVLTreeNode<T>* right();
	AVLTreeNode<T>* parent();
	void hight(size_t new_hight);
	void left(AVLTreeNode<T>* node);
	void right(AVLTreeNode<T>* node);
	void parent(AVLTreeNode<T>* node);
};

template<class T>
AVLTreeNode<T>::AVLTreeNode(T value, size_t hight = 0, AVLTreeNode<T>* left = nullptr, AVLTreeNode<T>* right = nullptr, AVLTreeNode<T>* parent = nullptr) {
	_value = value; _left = left; _right = right; _hight = hight; _parent = parent;
}

template<class T>
AVLTreeNode<T>::AVLTreeNode(const AVLTreeNode<T>& node) {
	_value = node._value;
	_right = node._right;
	_left = node._left;
	_hight = node._hight;
	_parent = node._parent;
}

template<class T>
AVLTreeNode<T>& AVLTreeNode<T>::operator = (const AVLTreeNode <T>& node) {
	if (&node != this) {
		_value = node._value;
		_right = node._right;
		_left = node._left;
		_hight = node._hight;
	}
	return *this;
}

template<class T>
const T& AVLTreeNode<T>::value() const noexcept {
	return _value;
}

template<class T>
AVLTreeNode<T>* AVLTreeNode<T>::left() {
	return _left;
}

template<class T>
AVLTreeNode<T>* AVLTreeNode<T>::right() {
	return _right;
}

template<class T>
AVLTreeNode<T>* AVLTreeNode<T>::parent() {
	return _parent;
}

template<class T>
const size_t& AVLTreeNode<T>::hight() const noexcept {
	return _hight;
}

template<class T>
void AVLTreeNode<T>::hight(size_t new_hight){
	_hight = new_hight;
}

template<class T>
void AVLTreeNode<T>::left(AVLTreeNode<T>* node) {
	_left = node;
}

template<class T>
void AVLTreeNode<T>::right(AVLTreeNode<T>* node) {
	_right = node;
}

template<class T>
void AVLTreeNode<T>::parent(AVLTreeNode<T>* node) {
	_parent = node;
}
