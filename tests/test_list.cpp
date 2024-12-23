#include <gtest.h>
#include "../lib_list/list.h"
#include "../lib_list/node.h"

class TestListsLib : public ::testing::Test {
protected:
	Tlist<int> list = Tlist<int>();
};

TEST_F(TestListsLib, check_func_push_front) {
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	EXPECT_EQ(list._head->value(), 3);
	EXPECT_EQ(list._head->next()->value(), 2);
	EXPECT_EQ(list._tail->value(), 1);
}

TEST_F(TestListsLib, check_func_empty) {
	list.push_front(1);
	EXPECT_EQ(list._head->value(), list._tail->value());
}

TEST_F(TestListsLib, check_func_push_back) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	EXPECT_EQ(list._head->value(), 5);
	EXPECT_EQ(list._head->next()->value(), 6);
	EXPECT_EQ(list._tail->value(), 7);
}

TEST(TestLists, check_func_find) {
	Tlist<int> list;
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.push_back(8);
	TNode<int>* val = list.find(6);
	EXPECT_EQ(val->value(), 6);
	EXPECT_EQ(val->next()->value(), 7);
}

TEST_F(TestListsLib, check_func_insert_pos) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.insert(1, 2);
	EXPECT_EQ(list._head->next()->value(), 2);
	EXPECT_EQ(list._head->next()->next()->value(), 6);
}

TEST_F(TestListsLib, check_func_insert_throw) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	ASSERT_ANY_THROW(list.insert(-1, 2));
	ASSERT_ANY_THROW(list.insert(3, 2));
}

TEST_F(TestListsLib, check_func_insert_node) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	TNode<int>* val = list.find(6);
	list.insert(val, 1);
	EXPECT_EQ(val->next()->value(), 1);
	EXPECT_EQ(val->next()->next()->value(), 7);
}

TEST_F(TestListsLib, check_func_insert_node_throw) {
	list.push_back(5);
	list.push_back(6);
	ASSERT_ANY_THROW(list.insert(nullptr, 5));
}

TEST_F(TestListsLib, check_func_pop_front) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.pop_front();
	ASSERT_EQ(list._head->value(), 6);
}

TEST_F(TestListsLib, check_func_pop_front_throw) {
	ASSERT_ANY_THROW(list.pop_front());
}

TEST_F(TestListsLib, check_func_pop_back) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.push_back(8);
	list.pop_back();
	ASSERT_EQ(list._tail->value(), 7);
}

TEST_F(TestListsLib, check_func_pop_back_throw) {
	ASSERT_ANY_THROW(list.pop_back());
}

TEST_F(TestListsLib, check_func_erase_node) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.push_back(8);
	TNode<int>* val = list.find(7);
	list.erase(val);
	ASSERT_EQ(list._head->next()->next()->value(), 8);
}

TEST_F(TestListsLib, check_func_erase_node_throw) {
	ASSERT_ANY_THROW(list.erase(nullptr));
}

TEST_F(TestListsLib, check_func_erase_pos) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.erase(1);
	ASSERT_EQ(list._head->next()->value(), 7);
}

TEST_F(TestListsLib, check_func_erase_pos_throw) {
	list.push_back(5);
	ASSERT_ANY_THROW(list.erase(-1));
	ASSERT_ANY_THROW(list.erase(2));
}

TEST_F(TestListsLib, check_func_replace_node) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	TNode<int>* val = list.find(6);
	list.replace(val, 9);
	ASSERT_EQ(val->value(), 9);
}

TEST_F(TestListsLib, check_func_replace_pos) {
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.replace(1, 9);
	ASSERT_EQ(list._head->next()->value(), 9);
}

TEST(TestTListsLib, check_algo_reverse_list) {
	Tlist<int> s = Tlist<int>();
	for (int i = 0; i < 10; i++) {
		s.push_back(i);
	}
	TNode<int>* l = s.find(2);
	s._tail->next(l);
	EXPECT_EQ(s.check_cycle_reverse_list(), 1);
	s._tail->next(nullptr);
}

TEST(TestTListsLib, check_algo_rabbit_and_turtle) {
	Tlist<int> s = Tlist<int>();
	for (int i = 0; i < 10; i++) {
		s.push_back(i);
	}
	TNode<int>* l = s.find(2);
	s._tail->next(l);
	EXPECT_EQ(s.check_cycle_rabbit_turtle(), 1);
	s._tail->next(nullptr);
}

TEST(TestTListsLib, check_test_algo) {
	Tlist<int> s = Tlist<int>();
	for (int i = 0; i < 1000000; i++) {
		s.push_back(i);
	}
	TNode<int>* l = s.find(2);
	s._tail->next(l);
	EXPECT_GT(s.test_time_algorithm_rabbit_turtle(), s.test_time_algorithm_reverse_list());
	s._tail->next(nullptr);
}

TEST_F(TestListsLib, check_iterator) {
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	size_t total = 0;
	for (Tlist<int>::iterator it = list.begin(); it != list.end(); it++) {
		total++;
		EXPECT_EQ(*it, total);
	}
	EXPECT_EQ(total, 5);
}