#include "exception"
#include "algorithm"
#include "../lib_avltree/AVLTreeNode.h"
#pragma once

template<class T>
class AVLTree {
	AVLTreeNode<T>* _head;
	public:
		AVLTree();
		AVLTreeNode<T>* copy(AVLTreeNode<T>* node) noexcept;
		AVLTree(const AVLTree<T>& tree);
		AVLTree<T>& operator=(const AVLTree<T>& tree);
		AVLTreeNode<T>* insert(T val);
		AVLTreeNode<T>* search(T val) const noexcept;
		AVLTreeNode<T>* min_successor(AVLTreeNode<T>* node);
		void erase(T val) noexcept;
		void calculation_hight(AVLTreeNode<T>* node, bool flag = true) noexcept;
		int max_hight(AVLTreeNode<T>* node) const noexcept;
		int check_balance(AVLTreeNode<T>* node) const noexcept;
		void balance(AVLTreeNode<T>* node);
		void RR(AVLTreeNode<T>* node);
		void LL(AVLTreeNode<T>* node);
		void RL(AVLTreeNode<T>* node);
		void LR(AVLTreeNode<T>* node);
		void clear(AVLTreeNode<T>* node) noexcept;
		~AVLTree();
		AVLTreeNode<T>* head();
};

template <class T>
AVLTree<T>::AVLTree() {
	_head = nullptr;
}

template <class T>
void AVLTree<T>::clear(AVLTreeNode<T>* node) noexcept {
	if (node != nullptr) {
		clear(node->left());
		clear(node->right());
		delete node;
	}
}

template<class T>
AVLTree<T>::~AVLTree() {
	clear(_head);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::head() {
	return _head;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::copy(AVLTreeNode<T>* node) noexcept {
	if (node == nullptr)
		return nullptr;
	AVLTreeNode<T>* new_node = new AVLTreeNode<T>(node->value());
	new_node->left(copy(node->left()));
	if (new_node->left()) new_node->left()->parent(new_node);
	new_node->right(copy(node->right()));
	if (new_node->right()) new_node->right()->parent(new_node);
	return new_node;
}

template<class T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree) {
	_head = copy(tree._head);
}

template<class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& tree) {
	if (&tree != this) {
		delete _head;
		_head = copy(tree._head);
	}
	return *this;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::search(T val) const noexcept {
	AVLTreeNode<T>* cur = _head;
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

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(T val) {
	AVLTreeNode <T>* node = new AVLTreeNode<T>(val);
	if (_head == nullptr)
		_head = node;
	else {
		AVLTreeNode<T>* cur = _head;
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
		calculation_hight(node);
	}
	return node;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::min_successor(AVLTreeNode<T>* node) {
	AVLTreeNode<T>* cur = node->right();
	AVLTreeNode<T>* next = node->right();
	while (next->left() != nullptr) {
		cur = next;
		next = next->left();
	}
	if (cur != next) {
		cur->left(next->right());
		if (next->right()) next->right()->parent(cur);
	}
	return next;
}

template <class T>
void AVLTree<T>::erase(T val) noexcept {
	AVLTreeNode<T>* del = this->search(val);
	AVLTreeNode<T>* prev = del->parent();
	if (del->left() == nullptr && del->right() == nullptr) {
		if (del != _head) {
			if (prev->left() == del)
				prev->left(nullptr);
			else
				prev->right(nullptr);
			delete del;
			calculation_hight(prev);
		}
		else {
			delete del;
			_head = nullptr;
		}
	}
	else if (del->left() != nullptr && del->right() != nullptr) {
		AVLTreeNode<T>* rep = this->min_successor(del);
		AVLTreeNode<T>* old_parent_rep = rep->parent()!=del ? rep->parent() : rep;
		if (rep != del->right()) {
			rep->right(del->right());
			del->right()->parent(rep);
		}
		rep->left(del->left());
		del->left()->parent(rep);
		if (del != _head) {
			if (prev->left() == del)
				prev->left(rep);
			else
				prev->right(rep);
			rep->parent(prev);
		}
		delete del;
		if (del == _head) {
			_head = rep;
			rep->parent(nullptr);
		}
		calculation_hight(old_parent_rep);
	}
	else {
		AVLTreeNode<T>* child = del->left() != nullptr ? del->left() : del->right();
		if (del != _head) {
			if (prev->left() == del)
				prev->left(child);
			else
				prev->right(child);
			child->parent(prev);
			calculation_hight(prev);
		}
		delete del;
		if (del == _head) {
			_head = child;
			child->parent(nullptr);
			calculation_hight(child);
		}
	}
}

template <class T>
void AVLTree<T>::balance(AVLTreeNode<T>* node){
	if (check_balance(node) < 0) {
		if (check_balance(node->right()) <= 0)
			RR(node);
		else
			RL(node);
	}
	else {
		if (check_balance(node->left()) >= 0)
			LL(node);
		else
			LR(node);
	}
	calculation_hight(node);
}

template <class T>
void AVLTree<T>::RR(AVLTreeNode<T>* node) {
	AVLTreeNode<T>* r = node->right();
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
}

template <class T>
void AVLTree<T>::LL(AVLTreeNode<T>* node) {
	AVLTreeNode<T>* l = node->left();
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
}

template <class T>
void AVLTree<T>::RL(AVLTreeNode<T>* node) {
	LL(node->right());
	calculation_hight(node->right()->right(), false);
	RR(node);
}

template <class T>
void AVLTree<T>::LR(AVLTreeNode<T>* node) {
	RR(node->left());
	calculation_hight(node->left()->left(), false);
	LL(node);
}

template <class T>
int AVLTree<T>::check_balance(AVLTreeNode<T>* node) const noexcept{
	int left_hight, right_hight;
	left_hight = node->left() == nullptr ? -1 : node->left()->hight();
	right_hight = node->right() == nullptr ? -1 : node->right()->hight();
	return left_hight - right_hight;
}

template <class T>
int AVLTree<T>::max_hight(AVLTreeNode<T>* node) const noexcept {
	int left_hight, right_hight;
	left_hight = node->left() == nullptr ? -1 : node->left()->hight();
	right_hight = node->right() == nullptr ? -1 : node->right()->hight();
	return std::max(left_hight, right_hight);
}

template<class T>
void AVLTree<T>::calculation_hight(AVLTreeNode<T>* node, bool flag) noexcept {
	if (node == nullptr) return;
	node->hight(max_hight(node) + 1);
	if (std::abs(check_balance(node)) > 1 && flag) {
		balance(node);
	}
	calculation_hight(node->parent(), flag);
}