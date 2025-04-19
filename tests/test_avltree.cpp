#include <gtest.h>
#include <string>
#include "../lib_avltree/AVLTreeNode.h"
#include "../lib_avltree/AVLTree.h"

TEST(Test_AVLTree, check_func_insert_RR) {
	AVLTree<int> tree;
	tree.insert(3);
	tree.insert(6);
	tree.insert(7);
	ASSERT_EQ(tree.head()->value(), 6);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->left()->value(), 3);
}

TEST(Test_AVLTree, check_func_insert_LL) {
	AVLTree<int> tree;
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	ASSERT_EQ(tree.head()->value(), 4);
	ASSERT_EQ(tree.head()->right()->value(), 5);
	ASSERT_EQ(tree.head()->left()->value(), 3);
}

TEST(Test_AVLTree, check_func_insert_RL) {
	AVLTree<int> tree;
	tree.insert(5);
	tree.insert(7);
	tree.insert(6);
	ASSERT_EQ(tree.head()->value(), 6);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->left()->value(), 5);
}

TEST(Test_AVLTree, check_func_insert_LR) {
	AVLTree<int> tree;
	tree.insert(7);
	tree.insert(5);
	tree.insert(6);
	ASSERT_EQ(tree.head()->value(), 6);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->left()->value(), 5);
}

//      3
//     /  \
//    2    5
//		  /	\
//		 4 	 7
//			  \
//			   8

TEST(Test_AVLTree, check_func_hard_RR) {
	AVLTree<int> tree;
	tree.insert(3);
	tree.insert(2);
	tree.insert(5);
	tree.insert(7);
	tree.insert(4);
	tree.insert(8);
	ASSERT_EQ(tree.head()->value(), 5);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	ASSERT_EQ(tree.head()->right()->right()->value(), 8);
	ASSERT_EQ(tree.head()->left()->left()->value(), 2);
	ASSERT_EQ(tree.head()->left()->right()->value(), 4);
}

//      10
//     /  \
//    5    15
//   / \
//  2   7
// /
//1

TEST(Test_AVLTree, check_func_hard_LL) {                                        
	AVLTree<int> tree;															      
	tree.insert(10);
	tree.insert(5);
	tree.insert(2);
	tree.insert(1);
	tree.insert(7);
	tree.insert(15);
	ASSERT_EQ(tree.head()->value(), 5);
	ASSERT_EQ(tree.head()->right()->value(), 10);
	ASSERT_EQ(tree.head()->left()->value(), 2);
	ASSERT_EQ(tree.head()->right()->right()->value(), 15);
	ASSERT_EQ(tree.head()->left()->left()->value(), 1);
	ASSERT_EQ(tree.head()->right()->left()->value(), 7);
}

//      3
//     /  \
//    1    6
//        / \
//       4   7
//        \
//         5

TEST(Test_AVLTree, check_func_hard_RL) {
	AVLTree<int> tree;
	tree.insert(3);
	tree.insert(1);
	tree.insert(6);
	tree.insert(7);
	tree.insert(4);
	tree.insert(5);
	ASSERT_EQ(tree.head()->value(), 4);
	ASSERT_EQ(tree.head()->right()->value(), 6);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	ASSERT_EQ(tree.head()->right()->right()->value(), 7);
	ASSERT_EQ(tree.head()->left()->left()->value(), 1);
	ASSERT_EQ(tree.head()->right()->left()->value(), 5);
}

//    6
//   /  \
//  3    8
// / \
//2   4
//     \ 
//      5

TEST(Test_AVLTree, check_func_hard_LR) {
	AVLTree<int> tree;
	tree.insert(6);
	tree.insert(3);
	tree.insert(8);
	tree.insert(2);
	tree.insert(4);
	tree.insert(5);
	ASSERT_EQ(tree.head()->value(), 4);
	ASSERT_EQ(tree.head()->right()->value(), 6);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	ASSERT_EQ(tree.head()->right()->right()->value(), 8);
	ASSERT_EQ(tree.head()->left()->left()->value(), 2);
	ASSERT_EQ(tree.head()->right()->left()->value(), 5);
}

TEST(Test_AVLTree, check_func_search) {
	AVLTree<int> tree;
	tree.insert(6);
	tree.insert(3);
	tree.insert(8);
	tree.insert(2);
	tree.insert(4);
	tree.insert(5);
	ASSERT_EQ(tree.search(6)->value(), 6);
	ASSERT_EQ(tree.search(8)->value(), 8);
}

//										 5
//									   /   \
//									  3     8
//									 / \    / \
//									2   4   6   10
//								   /       /  \   \
//								  1		  5.5  7   15
//                                            /
//                                           6.5

TEST(Test_AVLTree, check_func_hard_erase) {
	AVLTree<float> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(8);
	tree.insert(2);
	tree.insert(4);
	tree.insert(6);
	tree.insert(10);
	tree.insert(1);
	tree.insert(5.5);
	tree.insert(7);
	tree.insert(15);
	tree.insert(6.5);
	tree.erase(3);
	ASSERT_EQ(tree.head()->value(), 6);
	ASSERT_EQ(tree.head()->left()->value(), 5);
	ASSERT_EQ(tree.head()->left()->right()->value(), 5.5);
	ASSERT_EQ(tree.head()->left()->left()->value(), 2);
	ASSERT_EQ(tree.head()->left()->left()->right()->value(), 4);
	ASSERT_EQ(tree.head()->left()->left()->left()->value(), 1);
	ASSERT_EQ(tree.head()->right()->value(), 8);
	ASSERT_EQ(tree.head()->right()->left()->value(), 7);
	ASSERT_EQ(tree.head()->right()->left()->left()->value(), 6.5);
	ASSERT_EQ(tree.head()->right()->right()->value(), 10);
	ASSERT_EQ(tree.head()->right()->right()->right()->value(), 15);
}


TEST(Test_AVLTree, check_func_erase_RR) {
	AVLTree<float> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(6);
	tree.insert(7);
	tree.erase(3);
	ASSERT_EQ(tree.head()->value(), 6);
	ASSERT_EQ(tree.head()->left()->value(), 5);
	ASSERT_EQ(tree.head()->right()->value(), 7);
}

//       6
//     /   \
//    3     8
//   / \    /
//  2   4  7  
// /
//1

TEST(Test_AVLTree, check_func_erase_LL) {
	AVLTree<float> tree;
	tree.insert(6);
	tree.insert(3);
	tree.insert(8);
	tree.insert(2);
	tree.insert(4);
	tree.insert(7);
	tree.insert(1);
	tree.erase(6);
	ASSERT_EQ(tree.head()->value(), 3);
	ASSERT_EQ(tree.head()->left()->value(), 2);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->left()->left()->value(), 1);
	ASSERT_EQ(tree.head()->right()->left()->value(), 4);
	ASSERT_EQ(tree.head()->right()->right()->value(), 8);
}

//       3
//     /   \
//    2     7
//   /     /  \
//  1     6    8
//       /
//      5

TEST(Test_AVLTree, check_func_erase_RL) {
	AVLTree<float> tree;
	tree.insert(3);
	tree.insert(2);
	tree.insert(7);
	tree.insert(1);
	tree.insert(6);
	tree.insert(8);
	tree.insert(5);
	tree.erase(2);
	ASSERT_EQ(tree.head()->value(), 6);
	ASSERT_EQ(tree.head()->left()->value(), 3);
	ASSERT_EQ(tree.head()->right()->value(), 7);
	ASSERT_EQ(tree.head()->left()->left()->value(), 1);
	ASSERT_EQ(tree.head()->right()->right()->value(), 8);
	ASSERT_EQ(tree.head()->left()->right()->value(), 5);
}
