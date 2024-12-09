#include <gtest.h>
#include "../lib_lstack/lstack.h"

class TestLStackLib : public ::testing::Test {
protected:
	TLStack<int> lstack;
};

TEST_F(TestLStackLib, check_push) {
	lstack.push(4);
	lstack.push(5);
	ASSERT_EQ(lstack.top()->value(), 5);
}

TEST_F(TestLStackLib, check_throw_push) {
	lstack.push(3);
	lstack.push(4);
	lstack.push(5);
	lstack.push(6);
	lstack.push(7);
	ASSERT_ANY_THROW(lstack.push(5));
}

TEST_F(TestLStackLib, check_func_pop) {
	lstack.push(4);
	lstack.push(5);
	lstack.push(6);
	lstack.pop();
	ASSERT_EQ(lstack.top()->value(), 5);
}

TEST_F(TestLStackLib, check_throw_pop) {
	ASSERT_ANY_THROW(lstack.pop());
}