#pragma once

template <class T>
class BTreeNode {
	T _value;
	BTreeNode<T>* _left;
	BTreeNode<T>* _right;
	public:
		BTreeNode(T value, BTreeNode<T>* left = nullptr, BTreeNode<T>* right = nullptr);
		const T& value() const noexcept;
		BTreeNode<T>* left();
		BTreeNode<T>* right();
		void left(BTreeNode<T>* node);
		void right(BTreeNode<T>* node);
};

template<class T>
BTreeNode<T>::BTreeNode(T value, BTreeNode<T>* left, BTreeNode<T>* right) {
	_value = value; _left = left; _right = right;
}

template<class T>
const T& BTreeNode<T>::value() const noexcept{
	return _value;
}

template<class T>
BTreeNode<T>* BTreeNode<T>::left() {
	return _left;
}

template<class T>
BTreeNode<T>* BTreeNode<T>::right() {
	return _right;
}

template<class T>
void BTreeNode<T>::left(BTreeNode<T>* node) {
	_left = node;
}

template<class T>
void BTreeNode<T>::right(BTreeNode<T>* node) {
	_right = node;
}