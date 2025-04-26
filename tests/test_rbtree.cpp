#include <gtest.h>
#include <string>
#include "../lib_rbtree/RBTree.h"
#include "../lib_rbtree/RBtreeNode.h"

TEST(Test_RBTree, check_func_insert_easy) {
	RBTree<int> tree;
	tree.insert(3);
	tree.insert(6);
	ASSERT_EQ(tree.head()->value(), 3);
	ASSERT_EQ(tree.head()->color(), true);
	ASSERT_EQ(tree.head()->right()->color(), false);
}

TEST(Test_RBTree, check_func_insert_LL) {
	RBTree<int> tree;
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	ASSERT_EQ(tree.head()->value(), 4);
	ASSERT_EQ(tree.head()->color(), true);
	ASSERT_EQ(tree.head()->right()->value(), 5);
	ASSERT_EQ(tree.head()->right()->color(), false);
	ASSERT_EQ(tree.head()->left()->value(), 3);
}

TEST(Test_RBTree, check_func_insert_RR) {
	RBTree<int> tree;
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	ASSERT_EQ(tree.head()->value(), 6);
	ASSERT_EQ(tree.head()->color(), true);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->right()->color(), false);
	ASSERT_EQ(tree.head()->left()->value(), 5);
	ASSERT_EQ(tree.head()->left()->color(), false);
}

TEST(Test_RBTree, check_func_insert_RL) {
	RBTree<int> tree;
	tree.insert(5);
	tree.insert(8);
	tree.insert(7);
	ASSERT_EQ(tree.head()->value(), 7);
	ASSERT_EQ(tree.head()->color(), true);
	ASSERT_EQ(tree.head()->right()->value(), 8);
	ASSERT_EQ(tree.head()->right()->color(), false);
	ASSERT_EQ(tree.head()->left()->value(), 5);
	ASSERT_EQ(tree.head()->left()->color(), false);
}

TEST(Test_RBTree, check_func_insert_LR) {
	RBTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(4);
	ASSERT_EQ(tree.head()->value(), 4);
	ASSERT_EQ(tree.head()->color(), true);
	ASSERT_EQ(tree.head()->right()->value(), 5);
	ASSERT_EQ(tree.head()->right()->color(), false);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	ASSERT_EQ(tree.head()->left()->color(), false);
}

TEST(Test_RBTree, check_func_insert_PU_head) {
	RBTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	ASSERT_EQ(tree.head()->value(), 5);
	ASSERT_EQ(tree.head()->color(), true);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->right()->color(), true);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	ASSERT_EQ(tree.head()->left()->color(), true);
	ASSERT_EQ(tree.head()->left()->left()->value(), 2);
	ASSERT_EQ(tree.head()->left()->left()->color(), false);
}

TEST(Test_RBTree, check_func_insert_PU_not_head) {
	RBTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(4);
	tree.insert(8);
	tree.insert(1);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->right()->color(), true);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	ASSERT_EQ(tree.head()->left()->color(), false);
	ASSERT_EQ(tree.head()->left()->left()->value(), 2);
	ASSERT_EQ(tree.head()->left()->left()->color(), true);
	ASSERT_EQ(tree.head()->left()->right()->value(), 4);
	ASSERT_EQ(tree.head()->left()->right()->color(), true);
	ASSERT_EQ(tree.head()->right()->right()->value(), 8);
	ASSERT_EQ(tree.head()->right()->right()->color(), false);
}

TEST(Test_RBTree, check_func_insert_hard) {
	RBTree<float> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(4);
	tree.insert(8);
	tree.insert(1);
	tree.insert(2.5);
	tree.insert(9);
	tree.insert(0);
	ASSERT_EQ(tree.head()->value(), 3);
	ASSERT_EQ(tree.head()->color(), true);
	ASSERT_EQ(tree.head()->left()->value(), 2);
	ASSERT_EQ(tree.head()->left()->color(), false);
	ASSERT_EQ(tree.head()->right()->value(), 5);
	ASSERT_EQ(tree.head()->right()->color(), false);
	ASSERT_EQ(tree.head()->left()->left()->value(), 1);
	ASSERT_EQ(tree.head()->left()->left()->color(), true);
	ASSERT_EQ(tree.head()->left()->right()->value(), 2.5);
	ASSERT_EQ(tree.head()->left()->right()->color(), true);
	ASSERT_EQ(tree.head()->right()->right()->value(), 8);
	ASSERT_EQ(tree.head()->right()->right()->color(), true);
	ASSERT_EQ(tree.head()->right()->left()->value(), 4);
	ASSERT_EQ(tree.head()->right()->left()->color(), true);
	ASSERT_EQ(tree.head()->left()->left()->left()->value(), 0);
	ASSERT_EQ(tree.head()->left()->left()->left()->color(), false);
	ASSERT_EQ(tree.head()->right()->right()->right()->value(), 9);
	ASSERT_EQ(tree.head()->right()->right()->right()->color(), false);
	ASSERT_EQ(tree.head()->right()->right()->left()->value(), 7);
	ASSERT_EQ(tree.head()->right()->right()->left()->color(), false);
}