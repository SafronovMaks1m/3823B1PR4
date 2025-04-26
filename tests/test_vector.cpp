#include <gtest.h>
#include "iostream"
#include "algorithm"
#include "../lib_DMassive/TDmassive.h"
#include "../lib_matrix/TVector.h"

TEST(TestTVectorLib, check_constructor_mas) {
	int* arr = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i+1;
	}
	TVector<int> vector = TVector<int>(arr, 4);
	for (size_t i = 0; i < 4; i++) {
		EXPECT_EQ(vector[i], i+1);
	}
	delete[] arr;
}

TEST(TestTVectorLib, check_operator_add) {
	int* arr = new int[4];
	int* mas = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i;
		mas[i] = i + 2;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(mas, 4);
	TVector<int> vector = vector1+vector2;
	for (size_t i = 0; i < 4; i++) {
		ASSERT_EQ(vector[i], arr[i] + mas[i]);
	}
	delete[] arr;
	delete[] mas;
}

TEST(TestTVectorLib, check_operator_sub) {
	int* arr = new int[4];
	int* mas = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i - 1;
		mas[i] = i + 3;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(mas, 4);
	TVector<int> vector = vector1 - vector2;
	for (size_t i = 0; i < 4; i++) {
		ASSERT_EQ(vector[i], arr[i] - mas[i]);
	}
	delete[] arr;
	delete[] mas;
}

TEST(TestTVectorLib, check_operator_add_assingment) {
	int* arr = new int[4];
	int* mas = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i + 1;
		mas[i] = i - 2;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(mas, 4);
	vector1 += vector2;
	for (size_t i = 0; i < 4; i++) {
		ASSERT_EQ(vector1[i], arr[i] + mas[i]);
	}
	delete[] arr;
	delete[] mas;
}

TEST(TestTVectorLib, check_operator_sub_assingment) {
	int* arr = new int[4];
	int* mas = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i + 3;
		mas[i] = i+1;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(mas, 4);
	vector1 -= vector2;
	for (size_t i = 0; i < 4; i++) {
		ASSERT_EQ(vector1[i], arr[i] - mas[i]);
	}
	delete[] arr;
	delete[] mas;
}

TEST(TestTVectorLib, check_operator_mul) {
	int* arr = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(arr, 4);
	int total = vector1 * vector2;
	ASSERT_EQ(total, 14);
	delete[] arr;
}

TEST(TestTVectorLib, check_operator_mul_this_number) {
	int* arr = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i+1;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	vector1 *= 5;
	for (size_t i = 0; i < 4; i++) {
		EXPECT_EQ(vector1[i], arr[i] * 5);
	}
	delete[] arr;
}

TEST(TestTVectorLib, check_operator_mul_number) {
	int* arr = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i + 1;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = vector1*4;
	for (size_t i = 0; i < 4; i++) {
		EXPECT_EQ(vector2[i], arr[i] * 4);
	}
	delete[] arr;
}

TEST(TestTVectorLib, check_func_lenght) {
	int* arr = new int[3];
	double sum = 0;
	for (size_t i = 0; i < 3; i++) {
		arr[i] = i + 2;
		sum += arr[i] * arr[i];
	}
	sum = sqrt(sum);
	TVector<int> vector1 = TVector<int>(arr, 3);
	double total = vector1.search_length();
	EXPECT_EQ(total, sum);
	delete[] arr;
}

TEST(TestTVectorLib, check_operator_eq) {
	int* arr = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(arr, 4);
	ASSERT_EQ(vector1 == vector2, true);
	delete[] arr;
}

TEST(TestTVectorLib, check_operator_eq_not) {
	int* arr = new int[4];
	int* mas = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i + 3;
		mas[i] = i;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(mas, 4);
	ASSERT_EQ(vector1 == vector2, false);
	delete[] arr;
	delete[] mas;
}

TEST(TestTVectorLib, check_operator_not_eq) {
	int* arr = new int[4];
	int* mas = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i + 3;
		mas[i] = i;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(mas, 4);
	ASSERT_EQ(vector1 != vector2, true);
	delete[] arr;
	delete[] mas;
}

TEST(TestTVectorLib, check_operator_not_not_eq) {
	int* arr = new int[4];
	for (size_t i = 0; i < 4; i++) {
		arr[i] = i;
	}
	TVector<int> vector1 = TVector<int>(arr, 4);
	TVector<int> vector2 = TVector<int>(arr, 4);
	ASSERT_EQ(vector1 != vector2, false);
	delete[] arr;
}

TEST(TestTVectorLib, check_throw) {
	TVector<int> vector1 = TVector<int>(4);
	TVector<int> vector2 = TVector<int>(5);
	TVector<int> vector;
	ASSERT_ANY_THROW(vector = vector1 + vector2);
}