#include <gtest.h>
#include "../lib_matrix/matrix.h"
#include "../lib_matrix/TVector.h"

TEST(TestTMatrixLib, check_constructer_size) {
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(3, 1);
	for (size_t i = 0; i < 3; i++) {
		EXPECT_EQ(s[i].size(), 3 - i);
		for (size_t j = 0; j < 3; j++) {
			if (j<i)
				EXPECT_EQ(s[i][j], 0);
			else
				EXPECT_EQ(s[i][j], 1);
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
		int total = 0;
		for (size_t j = 0; j < 3; j++) {
			if (j < i) {
				EXPECT_EQ(d[i][j], 0);
				total += 1;
			}
			else
				EXPECT_EQ(d[i][j], j+1-total);
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
			if (j < i)
				EXPECT_EQ(s[i][j], 0);
			else
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

TEST(TestTMatrixLib, check_hard_primer) {
	int** arr = new int* [2];
	int** mas = new int* [2];
	for (size_t i = 0; i < 2; i++) {
		arr[i] = new int[2];
		mas[i] = new int[2];
	}
	arr[0][0] = 1; arr[0][1] = 3; arr[1][0] = 5; arr[1][1] = 2;
	mas[0][0] = 3; mas[0][1] = 2; mas[1][0] = 1; mas[1][1] = 6;
	TUpperTriangularMatrix<int> s = TUpperTriangularMatrix<int>(arr, 2);
	TUpperTriangularMatrix<int> c = TUpperTriangularMatrix<int>(mas, 2);
	TUpperTriangularMatrix<int> d = s * c;
	EXPECT_EQ(d[0][0], 3); EXPECT_EQ(d[0][1], 20); EXPECT_EQ(d[1][1], 12);
}