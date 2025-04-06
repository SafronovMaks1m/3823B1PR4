#include <gtest.h>
#include "cmath"
#include "iostream"
#include "string"
#include "../lib_ht_lists/HTLists.h";
#include "../lib_polinom/polinom.h"

TEST(TestHTList, check_func_insert) {
	HTList<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//7
	ASSERT_EQ(table.data()[0]._head->value().key(), 5);
	ASSERT_EQ(table.data()[7]._head->next()->value().key(), 11);
	ASSERT_EQ(table.data()[8]._head->value().value(), CPolinom("5a^2b^3+4bc"));
}

TEST(TestHTList, check_func_insert_throw) {
	HTList<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//7
	ASSERT_ANY_THROW(table.insert(11, CPolinom("5a^2b+3bc")));
}

TEST(TestHTList, check_func_find) {
	HTList<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//7
	ASSERT_EQ(table.find(3), CPolinom("5a^2b^3+4bc"));
	ASSERT_EQ(table.find(11), CPolinom("5a^2b+3bc"));
}

TEST(TestHTList, check_func_find_throw) {
	HTList<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//7
	ASSERT_ANY_THROW(table.find(1));
}

TEST(TestHTList, check_func_find_erase) {
	HTList<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//7
	table.insert(19, CPolinom("5a^2b+3bc"));//7
	table.erase(11);
	ASSERT_ANY_THROW(table.find(11));
	ASSERT_EQ(table.data()[7]._tail->value().key(), 19);
}

TEST(TestHTList, check_func_find_erase_throw) {
	HTList<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//7
	table.insert(19, CPolinom("5a^2b+3bc"));//7
	ASSERT_ANY_THROW(table.erase(1));
}

TEST(TestHTList, check_func_square_brackets1) {
	HTList<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//7
	ASSERT_EQ(table[11], CPolinom("5a^2b+3bc"));
	ASSERT_EQ(table[2], CPolinom("5a^2b+bc"));
}

TEST(TestHTList, check_func_square_brackets2) {
	HTList<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//3
	table[2] = CPolinom("abc+a^2");
	ASSERT_EQ(table[2], CPolinom("abc+a^2"));
}