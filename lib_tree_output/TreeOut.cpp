//#include "iostream"
//#include "..//lib_bin_tree/TBinTree.h"
//#include "..//lib_bin_tree/TBinNode.h"
//#pragma once
//
//static int depth = 0;
//static int width = 50;
//
//template<class T>
//BTreeNode<T>* tree_out(BTreeNode<T>* node, bool flag) noexcept {
//	if (node == nullptr) {
//		depth -= 1; width += 5;
//		if (flag == true)
//			width -= 10;
//		return;
//	}
//	std::cout << " "*width << "|﹉﹉﹉﹉﹉" <<  node->value().key() << "﹉﹉﹉﹉﹉|" << std::endl;
//	depth += 1;
//	width -= 5;
//	tree_out(node->left()), false);
//	depth += 1;
//	width += 5;
//	tree_out(node->right()), true);
//	depth -= 1;
//	if (flag == false)
//		width += 5;
//	else
//		width -= 5;
//}