#include "exception"
#include "iostream"
#include "..//lib_bin_tree/TBinNode.h"

template <class T>
class BSearchTree {
	BTreeNode<T>* _head;
	public:
		BSearchTree();
		BTreeNode<T>* insert(T val);
		BTreeNode<T>* search(T val) const noexcept;
		BTreeNode<T>* search_prev(T& val) const noexcept;
		BTreeNode<T>* min(BTreeNode<T>* node);
		void erase(T val) noexcept;
		~BSearchTree();
		void clear(BTreeNode<T>* node) noexcept;
		BTreeNode<T>* head();
};

template<class T>
BSearchTree<T>::BSearchTree() {
	_head = nullptr;
}

template<class T>
BTreeNode<T>* BSearchTree<T>::insert(T val) {
	BTreeNode<T>* node = new BTreeNode<T>(val);
	if (_head == nullptr)
		_head = node;
	else {
		BTreeNode<T>* cur = _head;
		while (true) {
			if (val > cur->value()) {
				if (cur->right() == nullptr) {
					cur->right(node);
					break;
				}
				else
					cur = cur->right();
			}
			else if (val < cur->value()) {
				if (cur->left() == nullptr) {
					cur->left(node);
					break;
				}
				else 
					cur = cur->left();
			}
			else {
				throw std::logic_error("A node with this value is already in the tree.");
			}
		}
	}
	return node;
}

template <class T>
BTreeNode<T>* BSearchTree<T>::search(T val) const noexcept {
	BTreeNode<T>* cur = _head;
	while (cur != nullptr) {
		if (val > cur->value())
			cur = cur->right();
		else if (val < cur->value())
			cur = cur->left();
		else
			return cur;
	}
	return nullptr;
}

template <class T>
BTreeNode<T>* BSearchTree<T>::search_prev(T& val) const noexcept {
	BTreeNode<T>* cur = _head;
	BTreeNode<T>* next = _head;
	while (next->value()!=val) {
		cur = next;
		if (val > next->value())
			next = next->right();
		else
			next = next->left();
	}
	return cur;
}

template <class T>
BTreeNode<T>* BSearchTree<T>::min(BTreeNode<T>* node) {
	BTreeNode<T>* cur = node->right();
	BTreeNode<T>* next = node->right();
	while (next->left() != nullptr) {
		cur = next;
		next = next->left();
	}
	cur->left(next->right());
	return next;
}

template <class T>
void BSearchTree<T>::erase(T val) noexcept {
	BTreeNode<T>* del = this->search(val);
	BTreeNode<T>* prev = this->search_prev(val);
	if (del->left() == nullptr && del->right() == nullptr) {
		if (prev->left() == del)
			prev->left(nullptr);
		else
			prev->right(nullptr);
		delete del;
	}
	else if (del->left() != nullptr && del->right() != nullptr) {
		BTreeNode<T>* rep = this->min(del);
		if (rep != del->right())
			rep->right(del->right());
		rep->left(del->left());
		if (prev->left() == del)
			prev->left(rep);
		else
			prev->right(rep);
		delete del;
	}
	else {
		BTreeNode<T>* child = del->left() != nullptr ? del->left() : del->right();
		if (prev->left() == del)
			prev->left(child);
		else
			prev->right(child);
		delete del;
	}
}

template <class T>
BSearchTree<T>::~BSearchTree() {
	clear(_head);
}

template <class T>
void BSearchTree<T>::clear(BTreeNode<T>* node) noexcept {
	if (node != nullptr) {
		clear(node->left());
		clear(node->right());

		delete node;
	}
}

template <class T>
BTreeNode<T>* BSearchTree<T>::head() {
	return _head;
}