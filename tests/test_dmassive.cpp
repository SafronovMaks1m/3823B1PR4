#include <gtest.h>
#include "../lib_dmassive/TDmassive.h"

class TestDmassiveLib : public ::testing::Test {
protected:
	TDMassive<int> massive;
	TestDmassiveLib() {
		int* arr = new int[10];
		for (size_t i = 0; i < 10; i++) {
			arr[i] = i + 1;
		}
		massive = TDMassive<int>(arr, 10);
	}
};

TEST(TestTDmassiveLib, chec_constructor_def) {
	TDMassive<int> massive = TDMassive<int>();
	EXPECT_EQ(massive.size(), 0);
	EXPECT_EQ(massive.capacity(), 15);
	EXPECT_EQ(massive.deleted(), 0);
	for (size_t i = 0; i < massive.capacity(); i++) {
		EXPECT_EQ(massive.states()[i], State::empty);
	}
}

TEST(TestTDmassiveLib, chec_constructor_value) {
	TDMassive<int> massive = TDMassive<int>(5, 6);
	EXPECT_EQ(massive.size(), 5);
	EXPECT_EQ(massive.capacity(), 15);
	EXPECT_EQ(massive.deleted(), 0);
	for (size_t i = 0; i < massive.capacity(); i++) {
		if (i < massive.size()) {
			EXPECT_EQ(massive[i], 6);
			EXPECT_EQ(massive.states()[i], State::busy);
		}
		else {
			EXPECT_EQ(massive.states()[i], State::empty);
		}
	}
}

TEST(TestTDmassiveLib, check_constructor_pos) {
	int* arr = new int[5];
	for (size_t i = 0; i < 5; i++) {
		arr[i] = i + 1;
	}
	TDMassive<int> massive1 = TDMassive<int>(arr, 5);
	TDMassive<int> massive = TDMassive<int>(massive1, 2, 3);
	EXPECT_EQ(massive.size(), 3);
	EXPECT_EQ(massive.capacity(), 15);
	EXPECT_EQ(massive.deleted(), 0);
	for (size_t i = 0; i < massive.capacity(); i++) {
		if (i < massive.size()) {
			EXPECT_EQ(massive[i], i+3);
			EXPECT_EQ(massive.states()[i], State::busy);
		}
		else {
			EXPECT_EQ(massive.states()[i], State::empty);
		}
	}
}

TEST_F(TestDmassiveLib, check_func_push_back) {
	massive.push_back(5);
	EXPECT_EQ(massive[10], 5);
	EXPECT_EQ(massive.size(), 11);
	EXPECT_EQ(massive.states()[10], State::busy);
}

TEST_F(TestDmassiveLib, check_func_push_front) {
	massive.push_front(7);
	EXPECT_EQ(massive[0], 7);
	EXPECT_EQ(massive[1], 1);
	EXPECT_EQ(massive.size(), 11);
	EXPECT_EQ(massive.states()[0], State::busy);
}

TEST_F(TestDmassiveLib, check_func_full) {
	massive.push_back(1);
	massive.push_back(2);
	massive.push_back(3);
	massive.push_back(4);
	massive.push_back(5);
	massive.push_back(6);
	EXPECT_EQ(massive[15], 6);
	EXPECT_EQ(massive[14], 5);
	EXPECT_EQ(massive.size(), 16);
	EXPECT_EQ(massive.capacity(), 30);
}

TEST_F(TestDmassiveLib, check_func_pop_back) {
	massive.pop_back();
	ASSERT_EQ(massive.states()[9], State::empty);
	ASSERT_EQ(massive.size(), 9);
}

TEST_F(TestDmassiveLib, check_func_pop_front) {
	massive.pop_front();
	ASSERT_EQ(massive.states()[0], State::deleted);
	ASSERT_EQ(massive.deleted(), 1);
}

TEST(TestTDmassiveLib, check_func_empty) {
	TDMassive<int> massive = TDMassive<int>();
	ASSERT_ANY_THROW(massive.pop_back());
}

TEST_F(TestDmassiveLib, check_func_insert) {
	massive.insert(8, 3);
	ASSERT_EQ(massive.size(), 11);
	ASSERT_EQ(massive[3], 8);
}

TEST_F(TestDmassiveLib, check_func_insert_throw) {
	ASSERT_ANY_THROW(massive.insert(8, -1));
	ASSERT_ANY_THROW(massive.insert(8, 20));
}

TEST_F(TestDmassiveLib, check_func_replace) {
	massive.replace(5, 10);
	ASSERT_EQ(massive[5], 10);
}

TEST_F(TestDmassiveLib, check_func_replace_throw) {
	ASSERT_ANY_THROW(massive.replace(-1, 10));
	ASSERT_ANY_THROW(massive.replace(-1, 20));
}

TEST(TestTDmassiveLib, check_func_remove_all) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		if (i > 1 && i < 5) {
			arr[i] = 3;
		}
		else {
			arr[i] = i + 1;
		}
	}
	TDMassive<int> massive = TDMassive<int>(arr, 10);
	massive.remove_all(3);
	EXPECT_EQ(massive.deleted(), 3);
	for (size_t i = 2; i < 5; i++) {
		EXPECT_EQ(massive.states()[i], State::deleted);
	}
}

TEST(TestTDmassiveLib, check_func_remove_first) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		if (i > 1 && i < 5) {
			arr[i] = 3;
		}
		else {
			arr[i] = i + 1;
		}
	}
	TDMassive<int> massive = TDMassive<int>(arr, 10);
	massive.remove_first(3);
	EXPECT_EQ(massive.deleted(), 1);
	EXPECT_EQ(massive.states()[2], State::deleted);
	EXPECT_EQ(massive.states()[3], State::busy);
	EXPECT_EQ(massive.states()[4], State::busy);
}

TEST(TestTDmassiveLib, check_func_remove_last) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		if (i > 1 && i < 5) {
			arr[i] = 3;
		}
		else {
			arr[i] = i + 1;
		}
	}
	TDMassive<int> massive = TDMassive<int>(arr, 10);
	massive.remove_last(3);
	EXPECT_EQ(massive.deleted(), 1);
	EXPECT_EQ(massive.states()[4], State::deleted);
	EXPECT_EQ(massive.states()[3], State::busy);
	EXPECT_EQ(massive.states()[2], State::busy);
}

TEST(TestTDmassiveLib, check_func_remove_by_index) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		if (i > 1 && i < 5) {
			arr[i] = 3;
		}
		else {
			arr[i] = i + 1;
		}
	}
	TDMassive<int> massive = TDMassive<int>(arr, 10);
	massive.remove_by_index(3);
	EXPECT_EQ(massive.deleted(), 1);
	EXPECT_EQ(massive.states()[3], State::deleted);
	EXPECT_EQ(massive.states()[4], State::busy);
	EXPECT_EQ(massive.states()[2], State::busy);
}

TEST_F(TestDmassiveLib, check_func_remove_by_index_throw) {
	ASSERT_ANY_THROW(massive.remove_by_index(-1));
	ASSERT_ANY_THROW(massive.remove_by_index(20));
}

TEST(TestTDmassiveLib, check_func_overexposure_del) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		if (i > 1 && i < 6) {
			arr[i] = 3;
		}
		else {
			arr[i] = i + 1;
		}
	}
	TDMassive<int> massive = TDMassive<int>(arr, 10);
	massive.remove_all(3);
	EXPECT_EQ(massive.deleted(), 0);
	EXPECT_EQ(massive.size(), 6);
	EXPECT_EQ(massive[2], 7);
}

TEST(TestTDmassiveLib, check_func_find_all) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		if (i > 1 && i < 6) {
			arr[i] = 3;
		}
		else {
			arr[i] = i + 1;
		}
	}
	TDMassive<int> massive = TDMassive<int>(arr, 10);
	EXPECT_EQ(massive.find_all(3), 4);
}

TEST(TestTDmassiveLib, check_func_find_first) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		if (i > 1 && i < 6) {
			arr[i] = 3;
		}
		else {
			arr[i] = i + 1;
		}
	}
	TDMassive<int> massive = TDMassive<int>(arr, 10);
	EXPECT_EQ(massive.find_first(3), 2);
}

TEST(TestTDmassiveLib, check_func_find_last) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		if (i > 1 && i < 6) {
			arr[i] = 3;
		}
		else {
			arr[i] = i + 1;
		}
	}
	TDMassive<int> massive = TDMassive<int>(arr, 10);
	EXPECT_EQ(massive.find_last(3), 5);
}

TEST_F(TestDmassiveLib, check_func_swap) {
	int* mas = new int[9];
	for (size_t i = 0; i < 9; i++) {
		mas[i] = i + 2;
	}
	TDMassive<int> obj = TDMassive<int>(mas, 9);
	massive.swap(obj);
	EXPECT_EQ(massive.size(), 9);
	EXPECT_EQ(obj.size(), 10);
	for (size_t i = 0; i < 9; i++) {
		EXPECT_EQ(massive[i], i + 2);
	}
	for (size_t i = 0; i < 10; i++) {
		EXPECT_EQ(obj[i], i + 1);
	}
}

TEST_F(TestDmassiveLib, check_func_assign) {
	int* mas = new int[9];
	for (size_t i = 0; i < 9; i++) {
		mas[i] = i + 2;
	}
	TDMassive<int> obj = TDMassive<int>(mas, 9);
	massive.assign(obj);
	EXPECT_EQ(massive.size(), 9);
	EXPECT_EQ(obj.size(), 9);
	for (size_t i = 0; i < 9; i++) {
		EXPECT_EQ(massive[i], i + 2);
	}
}

TEST_F(TestDmassiveLib, check_func_clear) {
	massive.clear();
	EXPECT_EQ(massive.deleted(), 0);
	EXPECT_EQ(massive.size(), 0);
	EXPECT_EQ(massive.capacity(), 0);
}

TEST_F(TestDmassiveLib, check_func_resize) {
	massive.resize(20, 5);
	EXPECT_EQ(massive.capacity(), 30);
	EXPECT_EQ(massive.size(), 20);
	for (size_t i = 0; i < massive.size(); i++) {
		EXPECT_EQ(massive[i], 5);
		EXPECT_EQ(massive.states()[i], State::busy);
	}
}
TEST_F(TestDmassiveLib, check_func_resize_throw) {
	ASSERT_ANY_THROW(massive.resize(0, 5));
}

TEST_F(TestDmassiveLib, check_func_insert_pos) {
	int* mas = new int[10];
	for (size_t i = 0; i < 10; i++) {
		mas[i] = i + 10;
	}
	massive = massive.insert(mas, 10, 5);
	EXPECT_EQ(massive.size(), 20);
	EXPECT_EQ(massive.capacity(), 30);
	for (size_t i = 5; i < 15; i++) {
		EXPECT_EQ(massive[i], i + 5);
	}
}

TEST_F(TestDmassiveLib, check_func_erase) {
	massive = massive.erase(3, 2);
	EXPECT_EQ(massive.deleted(), 2);
	EXPECT_EQ(massive.states()[3], State::deleted);
	EXPECT_EQ(massive.states()[4], State::deleted);
}

