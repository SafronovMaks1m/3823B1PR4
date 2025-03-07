#include <gtest.h>
#include "..//lib_pair/TPair.h"
#include "..//lib_list/list.h"
#include "..//lib_list/node.h"
#include "..//lib_unsort_table/unsort_table.h"

TEST(TestUnsort_Table, check_func_find) {
	Tlist<TPair<int, int>> list;
	for (size_t i = 0; i < 5; i++) {
		list.push_back(TPair<int, int>(i + 1, i));
	}
	Unsorted_Table<int, int> table(list);
	ASSERT_EQ(table.find(1), 0);
	ASSERT_EQ(table.find(2), 1);
	ASSERT_EQ(table.find(3), 2);
	ASSERT_EQ(table.find(4), 3);
	ASSERT_EQ(table.find(5), 4);
}

TEST(TestUnsort_Table, check_func_insert1) {
	Tlist<TPair<int, int>> list;
	for (size_t i = 0; i < 5; i++) {
		list.push_back(TPair<int, int>(i + 1, i));
	}
	Unsorted_Table<int, int> table(list);
	table.insert(10);
	table.insert(11);
	table.insert(12);
	ASSERT_EQ(table.find(15), 10);
	ASSERT_EQ(table.find(17), 11);
	ASSERT_EQ(table.find(19), 12);
}

TEST(TestUnsort_Table, check_func_insert2) {
	Unsorted_Table<int, int> table;
	table.insert(1, 3);
	table.insert(3, 5);
	table.insert(2, 7);
	ASSERT_EQ(table.find(1), 3);
	ASSERT_EQ(table.find(3), 5);
	ASSERT_EQ(table.find(2), 7);
}

TEST(TestUnsort_Table, check_func_insert_throw) {
	Unsorted_Table<int, int> table;
	table.insert(3, 5);
	ASSERT_ANY_THROW(table.insert(3, 7));
}

TEST(TestUnsort_Table, check_func_erase) {
	Tlist<TPair<int, int>> list;
	for (size_t i = 0; i < 5; i++) {
		list.push_back(TPair<int, int>(i + 1, i));
	}
	Unsorted_Table<int, int> table(list);
	ASSERT_EQ(table.find(3), 2);
	table.erase(3);
	ASSERT_ANY_THROW(table.find(3));
}

//TEST(TestUnsort_Table, check_func_staples) {
//	Tlist<TPair<int, int>> list;
//	for (size_t i = 0; i < 5; i++) {
//		list.push_back(TPair<int, int>(i + 1, i));
//	}
//	Unsorted_Table<int, int> table(list);
//	ASSERT_EQ(table[1], 0);
//	ASSERT_EQ(table[3], 2);
//	table[3] = 7;
//	ASSERT_EQ(table[3], 7);
//}