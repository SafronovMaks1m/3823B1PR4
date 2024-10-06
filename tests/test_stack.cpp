#include <gtest.h>
#include "../lib_stack/stack.h"

class TestStackLib : public ::testing::Test {
protected:
	TStack<int> stack_par = TStack<int>(3);
};

TEST(TestTStackLib, check_def_construct) {
	TStack<int> stack_def = TStack<int>();
	EXPECT_EQ(stack_def._size, 20);
}

TEST_F(TestStackLib, check_param_construct) {
	EXPECT_EQ(stack_par._size, 3);
}

TEST_F(TestStackLib, check_throw_pop) {
	ASSERT_ANY_THROW(stack_par.pop());
}

TEST_F(TestStackLib, check_top) {
	stack_par.push(4);
	stack_par.push(5);
	ASSERT_EQ(stack_par.top(), 5);
}

TEST_F(TestStackLib, check_throw_push) {
	stack_par.push(3);
	stack_par.push(4);
	stack_par.push(5);
	ASSERT_ANY_THROW(stack_par.push(6));
}

TEST_F(TestStackLib, check_func_pop) {
	stack_par.push(4);
	stack_par.push(5);
	stack_par.push(6);
	stack_par.pop();
	ASSERT_EQ(stack_par.top(), 5);
}

TEST(TestTStackLib, check_destructor) {
	TStack<int>* stack_par = new TStack<int>(3);
	delete stack_par;
}