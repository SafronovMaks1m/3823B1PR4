#include <gtest.h>
#include "../lib_matrix/matrix.h"
#include "../lib_vector/TVector.h"

TEST(TestTMatrixLib, check_constructer_size) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	for (size_t i = 0; i < 3; i++) {
		EXPECT_EQ(s[i].size(), 3 - i);
		for (size_t j = 0; j < 3-i; j++) {
			EXPECT_EQ(s[i][j], 1);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_arr) {
	int** arr = new int* [3];
	for (size_t i = 0; i < 3; i++) {
		arr[i] = new int[3];
		for (size_t j = 0; j < 3; j++) {
			arr[i][j] = i;
		}
	}
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(arr, 3);
	for (size_t i = 0; i < 3; i++) {
		EXPECT_EQ(s[i].size(), 3 - i);
		for (size_t j = 0; j < 3 - i; j++) {
			EXPECT_EQ(s[i][j], i);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_add) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> c = TUpperTriangularMatrix<int>(3, 2);
	TUpperTriangularMatrix<int> d = s + c;
	for (size_t i = 0; i < 3; i++) {
		EXPECT_EQ(d[i].size(), 3 - i);
		for (size_t j = 0; j < 3 - i; j++) {
			EXPECT_EQ(d[i][j], 3);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_add_eq) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> c = TUpperTriangularMatrix<int>(3, 2);
	s += c;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3 - i; j++) {
			EXPECT_EQ(s[i][j], 3);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_sub) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> c = TUpperTriangularMatrix<int>(3, 2);
	TUpperTriangularMatrix<int> d = s - c;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3 - i; j++) {
			EXPECT_EQ(d[i][j], -1);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_sub_eq) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> c = TUpperTriangularMatrix<int>(3, 2);
	s -= c;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3 - i; j++) {
			EXPECT_EQ(s[i][j], -1);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_mul) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> c = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> d = s * c;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3 - i; j++) {
			EXPECT_EQ(d[i][j], j+1);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_mul_value) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> d = s * 5;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3 - i; j++) {
			EXPECT_EQ(d[i][j], 5);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_mul_eq_value) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	s *= 5;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3 - i; j++) {
			EXPECT_EQ(s[i][j], 5);
		}
	}
}

TEST(TestTMatrixLib, check_constructer_serch_det) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(4, 3);
	EXPECT_EQ(s.serch_det(), 81);
}

TEST(TestTMatrixLib, check_constructer_eq) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> c = TUpperTriangularMatrix<int>(3, 1);
	EXPECT_EQ(s == c, true);
}

TEST(TestTMatrixLib, check_constructer_not_eq) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	TUpperTriangularMatrix<int> c = TUpperTriangularMatrix<int>(3, 1);
	EXPECT_EQ(s != c, false);
}