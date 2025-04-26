#include <gtest.h>
#include "iostream"
#include "../lib_dsu/dsu.h"

TEST(TestLibDSU, check_constructor) {
	DSU obj = DSU(5);
	for (size_t i = 0; i < 1; i++) {
		ASSERT_EQ(obj.parent()[i], i + 1);
		ASSERT_EQ(obj.rank()[i], 0);
	}
}

TEST(TestLibDSU, check_make_set) {
	DSU obj = DSU(5);
	obj.make_set(5);
	obj.make_set(6);
	ASSERT_EQ(obj.parent()[4], 5);
	ASSERT_EQ(obj.parent()[5], 6);
}

TEST(TestLibDSU, check_uni) {
	DSU obj = DSU(5);
	obj.uni(1, 4);
	obj.uni(2, 4);
	ASSERT_EQ(obj.parent()[1], 1);
	ASSERT_EQ(obj.rank()[0], 1);
}

TEST(TestLibDSU, check_find_throw) {
	DSU obj = DSU(5);
	ASSERT_ANY_THROW(obj.find(7));
	ASSERT_ANY_THROW(obj.find(0));
}

TEST(TestLibDSU, check_find) {
	DSU obj = DSU(5);
	obj.uni(1, 4);
	obj.uni(2, 3);
	obj.uni(1, 2);
	ASSERT_EQ(obj.find(3), 1);
}