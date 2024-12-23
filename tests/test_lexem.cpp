#include <gtest.h>
#include "../lib_lexem/lexem.h"
#include "cmath"

TEST(TestLexemLib, check_not_throw_operation) {
	ASSERT_NO_THROW(Expression("-5*x"));
	ASSERT_NO_THROW(Expression("(5+x)/7"));
	ASSERT_NO_THROW(Expression("(-3*6)"));
}

TEST(TestLexemLib, check_throw_operation) {
	ASSERT_ANY_THROW(Expression("+5"));
	ASSERT_ANY_THROW(Expression("--5"));
	ASSERT_ANY_THROW(Expression("sin-5"));
	ASSERT_ANY_THROW(Expression("(*3*6)"));
	ASSERT_ANY_THROW(Expression("(-3*)"));
	ASSERT_ANY_THROW(Expression("(-3**6)"));
	ASSERT_ANY_THROW(Expression("-3*"));
}

TEST(TestLexemLib, check_not_throw_function) {
	ASSERT_NO_THROW(Expression("sin(x)*3"));
}

TEST(TestLexemLib, check_throw_function) {
	ASSERT_ANY_THROW(Expression("sinsin(x)"));
	ASSERT_ANY_THROW(Expression("xposicosl"));
	ASSERT_ANY_THROW(Expression("xcos(x)"));
	ASSERT_ANY_THROW(Expression("3.5sin(x)"));
	ASSERT_ANY_THROW(Expression("2tg(x)"));
	ASSERT_ANY_THROW(Expression("(5*x)sin(x)"));
	ASSERT_ANY_THROW(Expression("sin)"));
	ASSERT_ANY_THROW(Expression("sin)"));
	ASSERT_ANY_THROW(Expression("sin*(x)"));
	ASSERT_ANY_THROW(Expression("sinx"));
	ASSERT_ANY_THROW(Expression("sin3x"));
}

TEST(TestLexemLib, check_not_throw_variable) {
	ASSERT_NO_THROW(Expression("y*5"));
	ASSERT_NO_THROW(Expression("(x)"));
	ASSERT_NO_THROW(Expression("x*3"));
	ASSERT_NO_THROW(Expression("3*x"));
}

TEST(TestLexemLib, check_throw_variable) {
	ASSERT_ANY_THROW(Expression("sin(x)x"));
	ASSERT_ANY_THROW(Expression("(-3*6)x"));
	ASSERT_ANY_THROW(Expression("xsin(x)"));
	ASSERT_ANY_THROW(Expression("x(3*6)"));
}

TEST(TestLexemLib, check_not_throw_const) {
	ASSERT_NO_THROW(Expression("(3*6)"));
	ASSERT_NO_THROW(Expression("3*6"));
	ASSERT_NO_THROW(Expression("x*3"));
	ASSERT_NO_THROW(Expression("3*x"));
}

TEST(TestLexemLib, check_throw_const) {
	ASSERT_ANY_THROW(Expression("sin(x)3"));
	ASSERT_ANY_THROW(Expression("(5*6)3"));
	ASSERT_ANY_THROW(Expression("3sin(x)"));
	ASSERT_ANY_THROW(Expression("3(5*6)"));
	ASSERT_ANY_THROW(Expression("3x"));
}

TEST(TestLexemLib, check_throw_bracket) {
	ASSERT_ANY_THROW(Expression("(5+3))"));
	ASSERT_ANY_THROW(Expression("((())"));
	ASSERT_ANY_THROW(Expression(")()"));
}

TEST(TestLexemLib, check_not_throw) {
	ASSERT_NO_THROW(Expression("y/3+(tg(z)*5*x-sin(u)/6)^5+3.15*p"));
}

TEST(TestLexemLib, check_delete_spaces) {
	ASSERT_NO_THROW(Expression("5      +5*  10/  3"));
}

TEST(TestLexemLib, check_reverse_polish_entry) {
	ASSERT_EQ(Expression("5+10*(x-3/jop)^2-sin(x)").str(), "510x3jop/-2^*+xsin-");
	ASSERT_EQ(Expression("y/3+(tg(z)*5*x-sin(u)/6)^5+3.15*p").str(), "y3/ztg5*x*usin6/-5^+3.15p*+");
	ASSERT_EQ(Expression("5+10*((x-3/j)^2)-sin(x)").str(), "510x3j/-2^*+xsin-");
}