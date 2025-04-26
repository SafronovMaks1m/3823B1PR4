#include <gtest.h>
#include "string"
#include "../lib_monom/monom.h"
#include "../lib_polinom/polinom.h"

TEST(TestPolinomLib, check_func_eq) {
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc+a^3");
	CPolinom polinom2 = CPolinom("5a^2b^3+4bc+a^3");
	ASSERT_EQ(polinom1 == polinom2, true);
}

TEST(TestPolinomLib, check_func_not_eq1) {
	CPolinom polinom1 = CPolinom("3a^2b^3+4bc+a^3");
	CPolinom polinom2 = CPolinom("5a^2b^3+4bc+a^3");
	ASSERT_EQ(polinom1 != polinom2, true);
}

TEST(TestPolinomLib, check_func_not_eq2) {
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2+a^3");
	CPolinom polinom2 = CPolinom("5a^2b^3+4bc+a^3");
	ASSERT_EQ(polinom1 != polinom2, true);
}

TEST(TestPolinomLib, check_func_not_eq3) {
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2d+a^3", 4);
	CPolinom polinom2 = CPolinom("5a^2b^3+4bc+a^3");
	ASSERT_EQ(polinom1 != polinom2, true);
}

TEST(TestPolinomLib, check_func_add_throw) {
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2d+a^3", 4);
	CPolinom polinom2 = CPolinom("5a^2b^3+4bc+a^3");
	ASSERT_ANY_THROW(polinom1 + polinom2, true);
}

TEST(TestPolinomLib, check_func_sub_throw) {
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2d+a^3", 4);
	CPolinom polinom2 = CPolinom("5a^2b^3+4bc+a^3");
	ASSERT_ANY_THROW(polinom1 - polinom2, true);
}

TEST(TestPolinomLib, check_func_sort) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "a^3";
	CMonom mon1 = CMonom(s, names);
	s = "5a^2b^3";
	CMonom mon2 = CMonom(s, names);
	s = "4bc^2";
	CMonom mon3 = CMonom(s, names);
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2+a^3", 3);
	ASSERT_EQ(polinom1._monoms._head->value(), mon1);
	ASSERT_EQ(polinom1._monoms._head->next()->value(), mon2);
	ASSERT_EQ(polinom1._monoms._tail->value(), mon3);
}

TEST(TestPolinomLib, check_func_sort_add) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "a^3";
	CMonom mon1 = CMonom(s, names);
	s = "5a^2b^3";
	CMonom mon2 = CMonom(s, names);
	s = "8bc^2";
	CMonom mon3 = CMonom(s, names);
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2+4bc^2+a^3", 3);
	ASSERT_EQ(polinom1._monoms._head->value(), mon1);
	ASSERT_EQ(polinom1._monoms._head->next()->value(), mon2);
	ASSERT_EQ(polinom1._monoms._tail->value(), mon3);
}

TEST(TestPolinomLib, check_func_sort_mul) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "a^4b";
	CMonom mon1 = CMonom(s, names);
	s = "5a^2b^3";
	CMonom mon2 = CMonom(s, names);
	s = "8bc^2";
	CMonom mon3 = CMonom(s, names);
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2+4bc^2+a^3*ab", 3);
	ASSERT_EQ(polinom1._monoms._head->value(), mon1);
	ASSERT_EQ(polinom1._monoms._head->next()->value(), mon2);
	ASSERT_EQ(polinom1._monoms._tail->value(), mon3);
}


TEST(TestPolinomLib, check_func_sort_sub) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "a^4b";
	CMonom mon1 = CMonom(s, names);
	s = "5a^2b^3";
	CMonom mon2 = CMonom(s, names);
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2-4bc^2+a^3*ab", 3);
	ASSERT_EQ(polinom1._monoms._head->value(), mon1);
	ASSERT_EQ(polinom1._monoms._tail->value(), mon2);
}

TEST(TestPolinomLib, check_func_sort_div) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "5a^2b^3";
	CMonom mon1 = CMonom(s, names);
	s = "a";
	CMonom mon2 = CMonom(s, names);
	s = "8bc^2";
	CMonom mon3 = CMonom(s, names);
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2+4bc^2+a^3/a^2", 3);
	ASSERT_EQ(polinom1._monoms._head->value(), mon1);
	ASSERT_EQ(polinom1._monoms._head->next()->value(), mon2);
	ASSERT_EQ(polinom1._monoms._tail->value(), mon3);
}

TEST(TestPolinomLib, check_func_sort_mul_sub) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "5a^2b^3";
	CMonom mon1 = CMonom(s, names);
	s = "-4a^2bc^2";
	CMonom mon2 = CMonom(s, names);
	CPolinom polinom1 = CPolinom("5a^2b^3+4bc^2*(-a^2)", 3);
	ASSERT_EQ(polinom1._monoms._head->value(), mon1);
	ASSERT_EQ(polinom1._monoms._tail->value(), mon2);
}