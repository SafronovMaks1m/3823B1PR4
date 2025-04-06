#include <gtest.h>
#include "cmath"
#include "iostream"
#include "string"
#include "../lib_ht_shuffle/HTSuffle.h"
#include "../lib_polinom/polinom.h"

TEST(TestHTSuffle, check_func_hash_int) {
	HTSuffle<int, CPolinom> table(10);
	ASSERT_EQ(table.hash(1), 6);
	ASSERT_EQ(table.hash(2), 2);
	ASSERT_EQ(table.hash(3), 8);
	ASSERT_EQ(table.hash(5), 0);
	ASSERT_EQ(table.hash(10), 1);
	ASSERT_EQ(table.hash(13), 0);
	ASSERT_EQ(table.hash(25), 4);
}

TEST(TestHTSuffle, check_func_hash_str) {
	HTSuffle<std::string, CPolinom> table(10);
	ASSERT_EQ(table.hash("a"), 9);
	ASSERT_EQ(table.hash("b"), 5);
	ASSERT_EQ(table.hash("c"), 1);
	ASSERT_EQ(table.hash("ab"), 5);
	ASSERT_EQ(table.hash("abc"), 7);
	ASSERT_EQ(table.hash("abcde"), 9);
}

TEST(TestHTSuffle, check_func_insert1) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));
	table.insert(2, CPolinom("5a^2b+bc"));
	table.insert(3, CPolinom("5a^2b^3+4bc"));
	ASSERT_EQ(table.data()[0].first(), 5);
	ASSERT_EQ(table.data()[0].second(), CPolinom("a^2b^3+3b"));
	ASSERT_EQ(table.data()[2].first(), 2);
	ASSERT_EQ(table.data()[2].second(), CPolinom("5a^2b+bc"));
	ASSERT_EQ(table.data()[8].first(), 3);
	ASSERT_EQ(table.data()[8].second(), CPolinom("5a^2b^3+4bc"));
}


TEST(TestHTSuffle, check_func_insert2) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(6, CPolinom("a^2b^3+3b"));
	table.insert(11, CPolinom("5a^2b+bc"));
	ASSERT_EQ(table.data()[7].first(), 6);
	ASSERT_EQ(table.data()[7].second(), CPolinom("a^2b^3+3b"));
	ASSERT_EQ(table.data()[0].first(), 11);
	ASSERT_EQ(table.data()[0].second(), CPolinom("5a^2b+bc"));
}

TEST(TestHTSuffle, check_func_is_full_throw) {
	HTSuffle<int, CPolinom> table(2);
	table.insert(5, CPolinom("a^2b^3+3b"));
	table.insert(2, CPolinom("5a^2b+bc"));
	ASSERT_ANY_THROW(table.insert(3, CPolinom("5a^2b^3+4bc")));
}

TEST(TestHTSuffle, check_func_insert_throw) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(6, CPolinom("a^2b^3+3b"));
	table.insert(11, CPolinom("5a^2b+bc"));
	ASSERT_ANY_THROW(table.insert(6, CPolinom("2ab+bc")));
}

TEST(TestHTSuffle, check_func_insert_throw2) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(6, CPolinom("a^2b^3+3b"));
	table.insert(11, CPolinom("5a^2b+bc"));
	ASSERT_ANY_THROW(table.insert(11, CPolinom("a^2b+3b^3c")));
}

TEST(TestHTSuffle, check_func_find_throw) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(6, CPolinom("a^2b^3+3b"));
	table.insert(11, CPolinom("5a^2b+bc"));
	ASSERT_ANY_THROW(table.find(7));
}

TEST(TestHTSuffle, check_func_find1) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));
	table.insert(2, CPolinom("5a^2b+bc"));
	table.insert(3, CPolinom("5a^2b^3+4bc"));
	table.insert(6, CPolinom("a^2b^3+3b"));
	table.insert(11, CPolinom("5a^2b+bc"));
	ASSERT_EQ(table.find(5), CPolinom("a^2b^3+3b"));
}

TEST(TestHTSuffle, check_func_find2) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+bc"));//7
	ASSERT_EQ(table.find(11), CPolinom("5a^2b+bc"));
	ASSERT_EQ(table.data()[3].first(), 11);
}

TEST(TestHTSuffle, check_func_erase1) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+bc"));//7
	table.erase(2);
	ASSERT_ANY_THROW(table.find(2));
}

TEST(TestHTSuffle, check_func_erase2) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+bc"));//7
	ASSERT_ANY_THROW(table.erase(10));
}

TEST(TestHTSuffle, check_func_erase_throw) {
	HTSuffle<int, CPolinom> table(10);
	ASSERT_ANY_THROW(table.erase(10));
}

TEST(TestHTSuffle, check_func_insert3) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.erase(6);
	table.insert(11, CPolinom("5a^2b+bc"));//7
	ASSERT_EQ(table.data()[7].first(), 11);
}

TEST(TestHTSuffle, check_func_find3) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+bc"));//7
	table.erase(6);
	ASSERT_EQ(table.find(11), CPolinom("5a^2b+bc"));
}

TEST(TestHTSuffle, check_func_square_brackets1) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//3
	ASSERT_EQ(table[11], CPolinom("5a^2b+3bc"));
	ASSERT_EQ(table[2], CPolinom("5a^2b+bc"));
}

TEST(TestHTSuffle, check_func_square_brackets2) {
	HTSuffle<int, CPolinom> table(10);
	table.insert(5, CPolinom("a^2b^3+3b"));//0
	table.insert(2, CPolinom("5a^2b+bc")); //2
	table.insert(3, CPolinom("5a^2b^3+4bc"));//8
	table.insert(6, CPolinom("a^2b^3+3b"));//7
	table.insert(11, CPolinom("5a^2b+3bc"));//3
	table[2] = CPolinom("abc+a^2");
	ASSERT_EQ(table[2], CPolinom("abc+a^2"));
}
