#include <gtest.h>
#include "string"
#include "../lib_polinom/monom.h"
#include "../lib_polinom/polinom.h"

TEST(TestMonomLib, check_func_add) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "2a^2b^3c";
	CMonom mon1 = CMonom(s, names, 3);
	s = "5a^2b^3c";
	CMonom mon2 = CMonom(s, names,3 );
	CMonom mon3 = mon1 + mon2;
	ASSERT_EQ(mon3._coef, 7);
	ASSERT_EQ(mon3._size, 3);
	ASSERT_EQ(mon3._powers[0], 2);
	ASSERT_EQ(mon3._powers[1], 3);
	ASSERT_EQ(mon3._powers[2], 1);
}

TEST(TestMonomLib, check_func_add_assign) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "a^2b^3c";
	CMonom mon1 = CMonom(s, names,3 );
	s = "3a^2b^3c";
	CMonom mon2 = CMonom(s, names,3);
	mon1 += mon2;
	ASSERT_EQ(mon1._coef, 4);
	ASSERT_EQ(mon1._size, 3);
	ASSERT_EQ(mon1._powers[0], 2);
	ASSERT_EQ(mon1._powers[1], 3);
	ASSERT_EQ(mon1._powers[2], 1);
}

TEST(TestMonomLib, check_func_add_assign_size) {
	char names[5] = { 'a', 'b', 'c', 'd', 'e'};
	std::string s = "3a^2b^3ce^5";
	CMonom mon1 = CMonom(s, names, 5);
	s = "2a^2b^3ce^5";
	CMonom mon2 = CMonom(s, names, 5);
	mon1 += mon2;
	ASSERT_EQ(mon1._coef, 5);
	ASSERT_EQ(mon1._size, 5);
	ASSERT_EQ(mon1._powers[0], 2);
	ASSERT_EQ(mon1._powers[1], 3);
	ASSERT_EQ(mon1._powers[2], 1);
	ASSERT_EQ(mon1._powers[3], 0);
	ASSERT_EQ(mon1._powers[4], 5);
}

TEST(TestMonomLib, check_func_add_throw) {
	char names1[5] = { 'a', 'b', 'c', 'd', 'e' };
	char names2[4] = { 'a', 'b', 'c', 'd'};
	std::string s = "3a^2b^3ce^5";
	CMonom mon1 = CMonom(s, names1, 5);
	s = "2a^2b^3cd^5";
	CMonom mon2 = CMonom(s, names2, 4);
	ASSERT_ANY_THROW(mon1 + mon2);
}

TEST(TestMonomLib, check_func_sub_assign) {
	char names[3] = { 'a', 'b', 'c' };
	std::string s = "a^2b^3c";
	CMonom mon1 = CMonom(s, names);
	s = "3a^2b^3c";
	CMonom mon2 = CMonom(s, names);
	mon1 -= mon2;
	ASSERT_EQ(mon1._coef, -2);
	ASSERT_EQ(mon1._size, 3);
	ASSERT_EQ(mon1._powers[0], 2);
	ASSERT_EQ(mon1._powers[1], 3);
	ASSERT_EQ(mon1._powers[2], 1);
}

TEST(TestMonomLib, check_func_sub) {
	char names[4] = { 'a', 'b', 'c', 'd'};
	std::string s = "2cd^5";
	CMonom mon1 = CMonom(s, names, 4);
	s = "cd^5";
	CMonom mon2 = CMonom(s, names, 4);
	CMonom mon3 = mon1 - mon2;
	ASSERT_EQ(mon3._coef, 1);
	ASSERT_EQ(mon3._size, 4);
	ASSERT_EQ(mon3._powers[0], 0);
	ASSERT_EQ(mon3._powers[1], 0);
	ASSERT_EQ(mon3._powers[2], 1);
	ASSERT_EQ(mon3._powers[3], 5);
}

TEST(TestMonomLib, check_func_sub_throw) {
	char names1[5] = { 'a', 'b', 'c', 'd', 'e' };
	char names2[4] = { 'a', 'b', 'c', 'd' };
	std::string s = "3a^2b^3ce^5";
	CMonom mon1 = CMonom(s, names1, 5);
	s = "2a^2b^3cd^5";
	CMonom mon2 = CMonom(s, names2, 4);
	ASSERT_ANY_THROW(mon1 - mon2);
}

TEST(TestMonomLib, check_func_mul) {
	char names[4] = { 'a', 'b', 'c', 'd' };
	std::string s = "2cd^5";
	CMonom mon1 = CMonom(s, names, 4);
	char names2[3] = { 'a', 'b', 'c'};
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	CMonom mon3 = mon1 * mon2;
	ASSERT_EQ(mon3._coef, 6);
	ASSERT_EQ(mon3._size, 4);
	ASSERT_EQ(mon3._powers[0], 2);
	ASSERT_EQ(mon3._powers[1], 0);
	ASSERT_EQ(mon3._powers[2], 2);
	ASSERT_EQ(mon3._powers[3], 5);
}

TEST(TestMonomLib, check_func_mul_assign) {
	char names[4] = { 'a', 'b', 'c', 'd' };
	std::string s = "2cd^5";
	CMonom mon1 = CMonom(s, names, 4);
	char names2[3] = { 'a', 'b', 'c' };
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	mon1 *= mon2;
	ASSERT_EQ(mon1._coef, 6);
	ASSERT_EQ(mon1._size, 4);
	ASSERT_EQ(mon1._powers[0], 2);
	ASSERT_EQ(mon1._powers[1], 0);
	ASSERT_EQ(mon1._powers[2], 2);
	ASSERT_EQ(mon1._powers[3], 5);
}

TEST(TestMonomLib, check_func_div) {
	char names[4] = { 'a', 'b', 'c', 'd' };
	std::string s = "6cd^5";
	CMonom mon1 = CMonom(s, names, 4);
	char names2[3] = { 'a', 'b', 'c' };
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	CMonom mon3 = mon1 / mon2;
	ASSERT_EQ(mon3._coef, 2);
	ASSERT_EQ(mon3._size, 4);
	ASSERT_EQ(mon3._powers[0], -2);
	ASSERT_EQ(mon3._powers[1], 0);
	ASSERT_EQ(mon3._powers[2], 0);
	ASSERT_EQ(mon3._powers[3], 5);
}

TEST(TestMonomLib, check_func_div_assign) {
	char names[4] = { 'a', 'b', 'c', 'd' };
	std::string s = "6cd^5";
	CMonom mon1 = CMonom(s, names, 4);
	char names2[3] = { 'a', 'b', 'c' };
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	mon1 /= mon2;
	ASSERT_EQ(mon1._coef, 2);
	ASSERT_EQ(mon1._size, 4);
	ASSERT_EQ(mon1._powers[0], -2);
	ASSERT_EQ(mon1._powers[1], 0);
	ASSERT_EQ(mon1._powers[2], 0);
	ASSERT_EQ(mon1._powers[3], 5);
}

TEST(TestMonomLib, check_func_eq) {
	char names2[3] = { 'a', 'b', 'c' };
	std::string s = "a^2c";
	CMonom mon1 = CMonom(s, names2, 3);
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	ASSERT_EQ(mon1 == mon2, true);
}

TEST(TestMonomLib, check_func_not_eq) {
	char names2[3] = { 'a', 'b', 'c' };
	std::string s = "a^2c^2";
	CMonom mon1 = CMonom(s, names2, 3);
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	ASSERT_EQ(mon1 == mon2, false);
}

TEST(TestMonomLib, check_func_gt1) {
	char names2[3] = { 'a', 'b', 'c' };
	std::string s = "a^2c^2";
	CMonom mon1 = CMonom(s, names2, 3);
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	ASSERT_EQ(mon1 > mon2, true);
}

TEST(TestMonomLib, check_func_gt2) {
	char names1[4] = { 'a', 'b', 'c', 'd'};
	std::string s = "a^2cd";
	CMonom mon1 = CMonom(s, names1, 4);
	char names2[3] = { 'a', 'b', 'c'};
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	ASSERT_EQ(mon1 > mon2, true);
}

TEST(TestMonomLib, check_func_gt3) {
	char names1[4] = { 'a', 'b', 'c', 'd' };
	std::string s = "a^2cd^-1";
	CMonom mon1 = CMonom(s, names1, 4);
	char names2[3] = { 'a', 'b', 'c' };
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	ASSERT_EQ(mon1 > mon2, false);
}

TEST(TestMonomLib, check_func_less) {
	char names2[3] = { 'a', 'b', 'c' };
	std::string s = "4ac^2";
	CMonom mon1 = CMonom(s, names2, 3);
	s = "3a^2c";
	CMonom mon2 = CMonom(s, names2, 3);
	ASSERT_EQ(mon1 < mon2, true);
}

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