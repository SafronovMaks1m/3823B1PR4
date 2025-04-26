#include "exception"
#include "iostream"
#include "string"
#include "..//lib_bin_tree/TBinNode.h"
#include "..//lib_bin_tree/TBinNode.cpp"
#pragma once

template <class T>
class BSearchTree {
	BTreeNode<T>* _head;
	size_t _size;
	public:
		BSearchTree();
		BTreeNode<T>* copy(BTreeNode<T>* node) noexcept;
		BSearchTree(const BSearchTree<T>& tree);
		BSearchTree<T>& operator=(const BSearchTree<T>& tree);
		BTreeNode<T>* insert(T val);
		BTreeNode<T>* search(T val) const noexcept;
		BTreeNode<T>* search_prev(T& val) const noexcept;
		BTreeNode<T>* min(BTreeNode<T>* node);
		void erase(T val) noexcept;
		~BSearchTree();
		void clear(BTreeNode<T>* node) noexcept;
		BTreeNode<T>* head();
		size_t size() const noexcept;
		void tree_out(BTreeNode<T>* node, bool flag = false) noexcept;
		void cursor_move(int y, int x);
		void print_branch(BTreeNode<T>* node);
		void calculating_coordinates(BTreeNode<T>* node, bool flag);
		void coordinates_after_branch_formed(BTreeNode<T>* node, bool flag);
};

template<class T>
BSearchTree<T>::BSearchTree() {
	_head = nullptr;
	_size = 0;
}

template<class T>
BTreeNode<T>* BSearchTree<T>::copy(BTreeNode<T>* node) noexcept {
	if (node == nullptr)
		return nullptr;
	BTreeNode<T>* new_node = new BTreeNode<T>(node->value());
	new_node->left(copy(node->left()));
	new_node->right(copy(node->right()));
	return new_node;
}

template<class T>
BSearchTree<T>::BSearchTree(const BSearchTree<T>& tree) {
	_head = copy(tree._head);
	_size = tree._size;
}

template<class T>
BSearchTree<T>& BSearchTree<T>::operator=(const BSearchTree<T>& tree) {
	if (&tree != this) {
		_head = copy(tree._head);
		_size = tree._size;
	}
	return *this;
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
	_size++;
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
		if (del == _head) {
			_head = nullptr;
		}
	}
	else if (del->left() != nullptr && del->right() != nullptr) {
		BTreeNode<T>* rep = this->min(del);
		if (rep != del->right())
			rep->right(del->right());
		rep->left(del->left());
		if (del != _head) {
			if (prev->left() == del)
				prev->left(rep);
			else
				prev->right(rep);
		}
		delete del;
		if (del == _head) {
			_head = rep;
		}
	}
	else {
		BTreeNode<T>* child = del->left() != nullptr ? del->left() : del->right();
		if (del != _head) {
			if (prev->left() == del)
				prev->left(child);
			else
				prev->right(child);
		}
		delete del;
		if (del == _head) {
			_head = child;
		}
	}
	_size--;
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

template <class T>
size_t BSearchTree<T>::size() const noexcept {
	return _size;
}

template <class T>
void BSearchTree<T>::cursor_move(int y, int x) {
	std::cout << "\033[" << y << ";" << x << "H";
}

template<class T>
void BSearchTree<T>::calculating_coordinates(BTreeNode<T>* node, bool flag) {
	if (node->value() != _head->value() && width == 100) {
		depth += 3;
		if (flag == false)
			width -= width_sub;
		else
			width += (total + 1 + total / 2);
		total /= 2;
	}
	else if (node->value() != _head->value()) {
		depth += 3;
		if (flag == false) {
			total -= total_sub;
			width_sub -= total_sub; width -= width_sub;
		}
		else {
			total -= total_sub;
			width += width_sub + total_sub; width_sub -= total_sub;
		}
	}
	else {
		Depth(node);
		total_sub = max_dept;
		total = max_dept * (max_dept - 2) * 2;
		width_sub = (total / 2) + 1;
	}
}

static int max_dept = 0;
static int count = 0;
template<class T>
void Depth(BTreeNode<T>* node) {
	if (node == nullptr) return;
	count += 1;
	Depth(node->left());
	Depth(node->right());
	max_dept = count > max_dept ? count : max_dept;
	count -= 1;
}

template <class T>
void BSearchTree<T>::print_branch(BTreeNode<T>* node) {
	cursor_move(depth, width + total + 1); std::cout << node->value();
	if (node->left() != nullptr || node->right() != nullptr) {
		if (node->left() != nullptr) {
			cursor_move(depth, width);
			std::cout << "." << std::string(total, '-');
			cursor_move(depth + 1, width); std::cout << "|"; cursor_move(depth + 2, width); std::cout << "|";
		}
		if (node->right() != nullptr) {
			int size_value = std::to_string(node->value()).size();
			cursor_move(depth, width + total + 1 + size_value);
			std::cout << std::string(total, '-') << ".";
			cursor_move(depth + 1, width + total * 2 + 1 + size_value);  std::cout << "|"; cursor_move(depth + 2, width + total * 2 + 1 + size_value); std::cout << "|";
		}
	}
}

template <class T>
void BSearchTree<T>::coordinates_after_branch_formed(BTreeNode<T>* node, bool flag) {
	depth -= 3;
	if (flag == false) {
		if (_head->left()->value() == node->value()) {
			total *= 2; width += width_sub;
		}
		else {
			width += width_sub; total += total_sub; width_sub += total_sub;
		}
	}
	else {
		total += total_sub; width_sub += total_sub; width -= width_sub + total_sub;
	}
}

static int width = 100;
static int depth = 1;
static int total;
static int width_sub;
static int total_sub;
template<class T>
void BSearchTree<T>::tree_out(BTreeNode<T>* node, bool flag) noexcept {
	if (node == nullptr) return;
	calculating_coordinates(node, flag);
	print_branch(node);
	tree_out(node->left(), false);
	tree_out(node->right(), true);
	coordinates_after_branch_formed(node, flag);
}