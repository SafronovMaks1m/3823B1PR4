#include "gtest.h"
#include "../lib_parser/parser.h"

TEST(TestTParserLib, check_norm_exp) {
	EXPECT_TRUE(check_expression("((x+y*5)*[x/6-y])+{((8+19)+|14x+56|)*[18y-65]}"));
}
//[(5+5)]*{9}-|6|
TEST(TestTParserLib, check_var_skob) {
	ASSERT_ANY_THROW(check_expression("(5+5}"));
}

TEST(TestTParserLib, check_empty) {
	ASSERT_ANY_THROW(check_expression("5+5}"));
}

TEST(TestTParserLib, check_no_norm_elem) {
	ASSERT_ANY_THROW(check_expression("(5+5.}"));
}

TEST(TestTParserLib, check_not_empy_end) {
	ASSERT_ANY_THROW(check_expression("(((5"));
}