#include <gtest.h>
#include <string>
#include "..//lib_dict/TDict.h"
#include "..//lib_bin_tree/TBinNode.h"
#include "..//lib_bin_tree/TBinTree.h"
#include "..//lib_table_btree/TBSTTable.h"

TEST(Test_TBSTTable, check_func_find) {
	BSearchTree<TDict<int, int>> tree;
	for (size_t i = 0; i < 5; i++) {
		tree.insert(TDict<int, int>(i + 1, i));
	}
	TBSTTable<int, int> table(tree);
	ASSERT_EQ(table.find(1), 0);
	ASSERT_EQ(table.find(2), 1);
	ASSERT_EQ(table.find(3), 2);
	ASSERT_EQ(table.find(4), 3);
	ASSERT_EQ(table.find(5), 4);
}

TEST(Test_TBSTTable, check_func_insert1) {
	BSearchTree<TDict<int, int>> tree;
	for (size_t i = 0; i < 5; i++) {
		tree.insert(TDict<int, int>(i + 1, i));
	}
	TBSTTable<int, int> table(tree);
	table.insert(10);
	table.insert(11);
	table.insert(12);
	ASSERT_EQ(table.find(15), 10);
	ASSERT_EQ(table.find(17), 11);
	ASSERT_EQ(table.find(19), 12);
}

TEST(Test_TBSTTable, check_func_insert2) {
	TBSTTable<int, int> table;
	table.insert(1, 3);
	table.insert(3, 5);
	table.insert(2, 7);
	ASSERT_EQ(table.find(1), 3);
	ASSERT_EQ(table.find(3), 5);
	ASSERT_EQ(table.find(2), 7);
}

TEST(Test_TBSTTable, check_func_insert_throw) {
	TBSTTable<int, int> table;
	table.insert(3, 5);
	ASSERT_ANY_THROW(table.insert(3, 7));
}

TEST(Test_TBSTTable, check_func_erase) {
	BSearchTree<TDict<int, int>> tree;
	for (size_t i = 0; i < 5; i++) {
		tree.insert(TDict<int, int>(i + 1, i));
	}
	TBSTTable<int, int> table(tree);
	ASSERT_EQ(table.find(3), 2);
	table.erase(3);
	ASSERT_ANY_THROW(table.find(3));
}

TEST(Test_TBSTTable, check_func_staples) {
	BSearchTree<TDict<int, int>> tree;
	for (size_t i = 0; i < 5; i++) {
		tree.insert(TDict<int, int>(i + 1, i));
	}
	TBSTTable<int, int> table(tree);
	ASSERT_EQ(table[1], 0);
	ASSERT_EQ(table[3], 2);
	table[3] = 7;
	ASSERT_EQ(table[3], 7);
}

TEST(Test_TBSTTable, check_initialize_str) {
	BSearchTree<TDict<std::string, std::string>> tree;
	for (size_t i = 65; i < 98; i++) {
		char s = char(i);
		char s1 = char(i + 1);
		std::string str_s(1, s);
		std::string str_s1(1, i + 1);
		TDict<std::string, std::string> t(str_s, str_s1);

		tree.insert(t);
	}
	TBSTTable<std::string, std::string> table(tree);
	ASSERT_EQ(table["A"], "B");
	ASSERT_EQ(table["B"], "C");  
	table.insert("abc");
	ASSERT_EQ(table["abc!"], "abc");
}

TEST(Test_TBSTTable, check_test_tree) {
	TBSTTable<int, int> table;
	table.insert(5,5);
	table.insert(3,3);
	table.insert(2,2);
	table.insert(4,4);
	table.insert(6,6);
	table.insert(7,7);
	ASSERT_EQ(table.data().head()->value(), 5);
	ASSERT_EQ(table.data().head()->left()->value(), 3);
	ASSERT_EQ(table.data().head()->left()->left()->value(), 2);
	ASSERT_EQ(table.data().head()->left()->right()->value(), 4);
	ASSERT_EQ(table.data().head()->right()->value(), 6);
	ASSERT_EQ(table.data().head()->right()->right()->value(), 7);
}