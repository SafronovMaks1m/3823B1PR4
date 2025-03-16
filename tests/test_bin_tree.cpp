#include <gtest.h>
#include "..//lib_bin_tree/TBinNode.h"
#include "..//lib_bin_tree/TBinTree.h"
#include "..//lib_pair/TPair.h"
#include "..//lib_dict/TDict.h"

TEST(TestTBinTree, check_func_insert) {
	BSearchTree<int> tree;
	tree.insert(5);
	ASSERT_EQ(tree.head()->value(), 5);
	tree.insert(3);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	tree.insert(6);
	ASSERT_EQ(tree.head()->right()->value(), 6);
	tree.insert(7);
	ASSERT_EQ(tree.head()->right()->right()->value(), 7);
	tree.insert(4);
	ASSERT_EQ(tree.head()->left()->right()->value(), 4);
	tree.insert(2);
	ASSERT_EQ(tree.head()->left()->left()->value(), 2);
}

TEST(TestTBinTree, check_func_insert_throw) {
	BSearchTree<int> tree;
	tree.insert(5);
	ASSERT_EQ(tree.head()->value(), 5);
	tree.insert(3);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	tree.insert(6);
	ASSERT_EQ(tree.head()->right()->value(), 6);
	tree.insert(7);
	ASSERT_EQ(tree.head()->right()->right()->value(), 7);
	tree.insert(4);
	ASSERT_EQ(tree.head()->left()->right()->value(), 4);
	tree.insert(2);
	ASSERT_EQ(tree.head()->left()->left()->value(), 2);
	ASSERT_ANY_THROW(tree.insert(2));
	ASSERT_ANY_THROW(tree.insert(7));
}

TEST(TestTBinTree, check_func_search) {
	BSearchTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(6);
	tree.insert(7);
	tree.insert(4);
	tree.insert(2);
	BTreeNode<int>* node = tree.search(3);
	ASSERT_EQ(node->value(), 3);
	ASSERT_EQ(node->left()->value(), 2);
	ASSERT_EQ(node->right()->value(), 4);
	node = tree.search(6);
	ASSERT_EQ(node->value(), 6);
	ASSERT_EQ(node->left(), nullptr);
	ASSERT_EQ(node->right()->value(), 7);
	node = tree.search(9);
	ASSERT_EQ(node, nullptr);
}

TEST(TestTBinTree, check_func_erase1) {
	BSearchTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(6);
	tree.insert(7);
	tree.insert(4);
	tree.insert(2);
	tree.erase(7);
	ASSERT_EQ(tree.search(7), nullptr);
	ASSERT_EQ(tree.head()->right()->right(), nullptr);
	tree.erase(4);
	ASSERT_EQ(tree.search(4), nullptr);
	ASSERT_EQ(tree.head()->left()->right(), nullptr);
}

TEST(TestTBinTree, check_func_erase2) {
	BSearchTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(6);
	tree.insert(7);
	tree.insert(4);
	tree.insert(2);
	tree.erase(6);
	ASSERT_EQ(tree.search(6), nullptr);
	ASSERT_EQ(tree.head()->right()->value(), 7);
}

TEST(TestTBinTree, check_func_erase3) {
	BSearchTree<int> tree;
	tree.insert(8);
	tree.insert(3);
	tree.insert(10);
	tree.insert(1);
	tree.insert(6);
	tree.insert(4);
	tree.insert(7);
	tree.erase(3);
	ASSERT_EQ(tree.search(3), nullptr);
	ASSERT_EQ(tree.head()->left()->value(), 4);
	ASSERT_EQ(tree.head()->left()->left()->value(), 1);
	ASSERT_EQ(tree.head()->left()->right()->value(), 6);
}

TEST(TestTBinTree, check_func_erase4) {
	BSearchTree<int> tree;
	tree.insert(8);
	tree.insert(3);
	tree.insert(10);
	tree.insert(1);
	tree.insert(6);
	tree.insert(4);
	tree.insert(7);
	tree.erase(6);
	ASSERT_EQ(tree.search(6), nullptr);
	ASSERT_EQ(tree.head()->left()->right()->value(), 7);
	ASSERT_EQ(tree.head()->left()->right()->right(), nullptr);
	ASSERT_EQ(tree.head()->left()->right()->left()->value(), 4);
}

TEST(TestTBinTree, check_func_erase5) {
	BSearchTree<int> tree;
	tree.insert(8);
	tree.insert(3);
	tree.insert(10);
	tree.insert(1);
	tree.insert(6);
	tree.insert(4);
	tree.insert(7);
	tree.insert(5); //!!!
	tree.erase(3);
	ASSERT_EQ(tree.search(3), nullptr);
	ASSERT_EQ(tree.head()->left()->value(), 4);
	ASSERT_EQ(tree.head()->left()->left()->value(), 1);
	ASSERT_EQ(tree.head()->left()->right()->value(), 6);
	ASSERT_EQ(tree.head()->left()->right()->left()->value(), 5);
	ASSERT_EQ(tree.head()->left()->right()->right()->value(), 7);
}