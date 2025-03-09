#include <gtest.h>
#include "string"
#include "..//lib_pair/TPair.h"
#include "..//lib_dmassive/TDmassive.h"
#include "..//lib_sort_table_dmassive/sort_table_dmassive.h"

TEST(TestSort_Table_DMassive, check_func_insert1) {
	Sorted_Table_DMassive<int, int> table;
	table.insert(5);
	table.insert(3);
	table.insert(7);
	ASSERT_EQ(table[5], 5);
	ASSERT_EQ(table[4], 3);
	ASSERT_EQ(table[9], 7);
	ASSERT_EQ(table.data()[0].first(), 4);
	ASSERT_EQ(table.data()[1].first(), 5);
	ASSERT_EQ(table.data()[2].first(), 9);
}

TEST(TestSort_Table_DMassive, check_func_insert2) {
	Sorted_Table_DMassive<int, int> table;
	table.insert(1, 1);
	table.insert(5, 7);
	table.insert(3, 2);
	ASSERT_EQ(table[1], 1);
	ASSERT_EQ(table[5], 7);
	ASSERT_EQ(table[3], 2);
}

TEST(TestSort_Table_DMassive, check_func_insert_throw) {
	Sorted_Table_DMassive<int, int> table;
	table.insert(1, 1);
	table.insert(5, 7);
	table.insert(3, 2);
	ASSERT_ANY_THROW(table.insert(1, 10));
	ASSERT_ANY_THROW(table.insert(2));
}

TEST(TestSort_Table_DMassive, check_func_find) {
	Sorted_Table_DMassive<int, int> table;
	table.insert(1, 1);
	table.insert(5, 7);
	table.insert(3, 2);
	ASSERT_EQ(table.find(1), 1);
	ASSERT_EQ(table.find(5), 7);
}

TEST(TestSort_Table_DMassive, check_func_find_throw) {
	Sorted_Table_DMassive<int, int> table;
	table.insert(1, 1);
	table.insert(5, 7);
	table.insert(3, 2);
	ASSERT_ANY_THROW(table.find(10));
}

TEST(TestSort_Table_DMassive, check_func_erase) {
	Sorted_Table_DMassive<int, int> table;
	table.insert(1, 1);
	table.insert(5, 7);
	table.insert(3, 2);
	table.insert(8, 12);
	ASSERT_EQ(table.find(3), 2);
	table.erase(3);
	ASSERT_ANY_THROW(table.find(3));
}

TEST(TestSort_Table_DMassive, check_combined_test) {
	Sorted_Table_DMassive<int, int> table;
	table.insert(1, 1);
	table.insert(5, 7);
	table.insert(3, 2);
	table.insert(8, 12);
	table.erase(3);
	table.insert(3, 9);
	ASSERT_EQ(table.find(3), 9);
	ASSERT_EQ(table.data()[1].first(), 3);
	ASSERT_ANY_THROW(table.insert(3, 7));
}

TEST(TestSort_Table_DMassive, check_func_staples) {
	Sorted_Table_DMassive<int, int> table;
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(10, 4);
	ASSERT_EQ(table[1], 1);
	ASSERT_EQ(table[3], 2);
	ASSERT_EQ(table[5], 3);
	ASSERT_EQ(table[10], 4);
	table[3] = 20;
	ASSERT_EQ(table[3], 20);
}

TEST(TestSort_Table_DMassive, check_initialize_str) {
	Sorted_Table_DMassive<std::string, std::string> table;
	table.insert("a", "aa");
	table.insert("c", "cc");
	table.insert("b", "bb");
	table.insert("d", "dd");
	ASSERT_EQ(table["a"], "aa");
	ASSERT_EQ(table["c"], "cc");
	ASSERT_EQ(table["b"], "bb");
	ASSERT_EQ(table["d"], "dd");
	ASSERT_EQ(table.data()[0].first(), "a");
	ASSERT_EQ(table.data()[1].first(), "b");
	ASSERT_EQ(table.data()[2].first(), "c");
	ASSERT_EQ(table.data()[3].first(), "d");
	ASSERT_EQ(table.find("b"), "bb");
	table["c"] = "abc";
	ASSERT_EQ(table.find("c"), "abc");
}