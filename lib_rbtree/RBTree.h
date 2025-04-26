#include "exception"
#include "iostream"
#include "string"
#include <Windows.h>
#include "../lib_rbtree/RBtreeNode.h"
#pragma once

template <class T>
class RBTree {
	RBtreeNode<T>* _head;
	public:
		RBTree();
		RBtreeNode<T>* copy(RBtreeNode<T>* node) noexcept;
		RBTree(const RBTree<T>& tree);
		RBTree<T>& operator=(const RBTree<T>& tree);
		void balance(RBtreeNode<T>* node) noexcept;
		RBtreeNode<T>* insert(T val);
		RBtreeNode<T>* search(T val) const noexcept;
		void erase();
		void rotation(RBtreeNode<T>* node);
		void RR(RBtreeNode<T>* node);
		void LL(RBtreeNode<T>* node);
		void RL(RBtreeNode<T>* node);
		void LR(RBtreeNode<T>* node);
		void clear(RBtreeNode<T>* node) noexcept;
		~RBTree();
		RBtreeNode<T>* head();
		void tree_out(RBtreeNode<T>* node, bool flag = false) noexcept;
		void cursor_move(int y, int x);
		void print_branch(RBtreeNode<T>* node);
		void calculating_coordinates(RBtreeNode<T>* node, bool flag);
		void coordinates_after_branch_formed(RBtreeNode<T>* node, bool flag);
};

template <class T>
RBTree<T>::RBTree() {
	_head = nullptr;
}

template <class T>
void RBTree<T>::clear(RBtreeNode<T>* node) noexcept {
	if (node != nullptr) {
		clear(node->left());
		clear(node->right());
		delete node;
	}
}

template<class T>
RBTree<T>::~RBTree() {
	clear(_head);
}

template<class T>
RBtreeNode<T>* RBTree<T>::head() {
	return _head;
}

template<class T>
RBtreeNode<T>* RBTree<T>::copy(RBtreeNode<T>* node) noexcept {
	if (node == nullptr)
		return nullptr;
	RBtreeNode<T>* new_node = new RBtreeNode<T>(node->value());
	new_node->color(node->color());
	new_node->left(copy(node->left()));
	if (new_node->left()) new_node->left()->parent(new_node);
	new_node->right(copy(node->right()));
	if (new_node->right()) new_node->right()->parent(new_node);
	return new_node;
}

template<class T>
RBTree<T>::RBTree(const RBTree<T>& tree) {
	_head = copy(tree._head);
}

template<class T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& tree) {
	if (&tree != this) {
		delete _head;
		_head = copy(tree._head);
	}
	return *this;
}

template<class T>
RBtreeNode<T>* RBTree<T>::insert(T val) {
	RBtreeNode<T>* node = new RBtreeNode<T>(val);
	if (_head == nullptr)
		_head = node;
	else {
		RBtreeNode<T>* cur = _head;
		while (true) {
			if (val > cur->value()) {
				if (cur->right() == nullptr) {
					cur->right(node);
					node->parent(cur);
					break;
				}
				else
					cur = cur->right();
			}
			else if (val < cur->value()) {
				if (cur->left() == nullptr) {
					cur->left(node);
					node->parent(cur);
					break;
				}
				else
					cur = cur->left();
			}
			else {
				throw std::logic_error("A node with this value is already in the tree.");
			}
		}
		balance(node);
	}
	return node;
}

template<class T>
void RBTree<T>::balance(RBtreeNode<T>* node) noexcept {
	_head->color(true);
	if (node!=_head && node->parent()->color() == false) {
		RBtreeNode<T>* gp = node->parent()->parent();
		RBtreeNode<T>* uncle = (node->parent() == gp->left()) ? gp->right() : gp->left();
		if (uncle && uncle->color() == false) {
			node->parent()->color(true);
			uncle->color(true);
			if (node->parent()->parent() != _head) {
				node->parent()->parent()->color(false);
				balance(node->parent()->parent());
			}
		}
		else
			rotation(node);
	}
}

template <class T>
void RBTree<T>::RR(RBtreeNode<T>* node) {
	RBtreeNode<T>* r = node->right();
	if (node == _head) {
		_head = node->right();
		r->parent(nullptr);
	}
	else {
		bool root = node->parent()->right() == node ? true : false;
		if (root)
			node->parent()->right(r);
		else
			node->parent()->left(r);
		node->right()->parent(node->parent());
	}
	node->right(r->left());
	if (node->right()) node->right()->parent(node);
	r->left(node);
	node->parent(r);
	node->color(false);
	r->color(true);
}

template <class T>
void RBTree<T>::LL(RBtreeNode<T>* node) {
	RBtreeNode<T>* l = node->left();
	if (node == _head) {
		_head = node->left();
		l->parent(nullptr);
	}
	else {
		bool root = node->parent()->left() == node ? true : false;
		if (root)
			node->parent()->left(l);
		else
			node->parent()->right(l);
		node->left()->parent(node->parent());
	}
	node->left(l->right());
	if (node->left()) node->left()->parent(node);
	l->right(node);
	node->parent(l);
	node->color(false);
	l->color(true);
}

template <class T>
void RBTree<T>::RL(RBtreeNode<T>* node) {
	LL(node->right());
	RR(node);
}

template <class T>
void RBTree<T>::LR(RBtreeNode<T>* node) {
	RR(node->left());
	LL(node);
}

template<class T>
void RBTree<T>::rotation(RBtreeNode<T>* node) {
	RBtreeNode<T>* Gf = node->parent()->parent();
	if (node->parent()->value() > Gf->value()) {
		if (node->value() > node->parent()->value())
			RR(Gf);
		else
			RL(Gf);
	}
	else {
		if (node->value() > node->parent()->value())
			LR(Gf);
		else
			LL(Gf);
	}
}

template <class T>
RBtreeNode<T>* RBTree<T>::search(T val) const noexcept {
	RBtreeNode<T>* cur = _head;
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
void RBTree<T>::cursor_move(int y, int x) {
	std::cout << "\033[" << y << ";" << x << "H";
}

template<class T>
void RBTree<T>::calculating_coordinates(RBtreeNode<T>* node, bool flag) {
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

template<class T>
void Depth(RBtreeNode<T>* node) {
	if (node == nullptr) return;
	count += 1;
	Depth(node->left());
	Depth(node->right());
	max_dept = count > max_dept ? count : max_dept;
	count -= 1;
}

template <class T>
void RBTree<T>::print_branch(RBtreeNode<T>* node) {
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor_move(depth, width + total + 1); 
	if (node->color())
		SetConsoleTextAttribute(console_color, 3);
	else
		SetConsoleTextAttribute(console_color, 4);
	std::cout << node->value();
	SetConsoleTextAttribute(console_color, 7);
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
void RBTree<T>::coordinates_after_branch_formed(RBtreeNode<T>* node, bool flag) {
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

template<class T>
void RBTree<T>::tree_out(RBtreeNode<T>* node, bool flag) noexcept {
	if (node == nullptr) return;
	calculating_coordinates(node, flag);
	print_branch(node);
	tree_out(node->left(), false);
	tree_out(node->right(), true);
	coordinates_after_branch_formed(node, flag);
}