#include <gtest.h>
#include "../lib_min_heap/MinHeap.h"

TEST(TestMinHeap, check_func_insert) {
	MinHeap<int> heap;
	heap.insert(2);
	heap.insert(3);
	heap.insert(10);
	heap.insert(4);
	heap.insert(1);
	heap.insert(7);
	heap.insert(9);
	heap.insert(6);
	heap.insert(8);
	heap.insert(5);
	heap.insert(11); 
	ASSERT_EQ(heap.data()[0], 1);
	ASSERT_EQ(heap.data()[1], 2);
	ASSERT_EQ(heap.data()[2], 7);
	ASSERT_EQ(heap.data()[3], 4);
	ASSERT_EQ(heap.data()[4], 3);
	ASSERT_EQ(heap.data()[5], 10);
	ASSERT_EQ(heap.data()[6], 9);
	ASSERT_EQ(heap.data()[7], 6);
	ASSERT_EQ(heap.data()[8], 8);
	ASSERT_EQ(heap.data()[9], 5);
	ASSERT_EQ(heap.data()[10], 11);
}

TEST(TestMinHeap, check_func_emplace_up) {
	MinHeap<int> heap;
	heap.insert(2);
	heap.insert(3);
	heap.insert(10);
	heap.insert(4);
	heap.insert(1);
	heap.insert(7);
	heap.insert(9);
	heap.insert(6);
	heap.insert(8);
	heap.insert(5);
	heap.insert(11);
	heap.emplace(4, 0);
	ASSERT_EQ(heap.data()[0], 0);
	ASSERT_EQ(heap.data()[1], 1);
	ASSERT_EQ(heap.data()[4], 2);
}

TEST(TestMinHeap, check_func_emplace_down) {
	MinHeap<int> heap;
	heap.insert(2);
	heap.insert(3);
	heap.insert(10);
	heap.insert(4);
	heap.insert(1);
	heap.insert(7);
	heap.insert(9);
	heap.insert(6);
	heap.insert(8);
	heap.insert(5);
	heap.insert(11);
	heap.emplace(1, 6);
	ASSERT_EQ(heap.data()[1], 3);
	ASSERT_EQ(heap.data()[4], 5);
	ASSERT_EQ(heap.data()[9], 6);
}

TEST(TestMinHeap, check_func_emplace_throw) {
	MinHeap<int> heap;
	heap.insert(2);
	heap.insert(3);
	heap.insert(10);
	heap.insert(4);
	heap.insert(1);
	heap.insert(7);
	heap.insert(9);
	heap.insert(6);
	heap.insert(8);
	heap.insert(5);
	heap.insert(11);
	heap.emplace(1, 6);
	ASSERT_ANY_THROW(heap.emplace(14, 6));
}

TEST(TestMinHeap, check_func_min) {
	MinHeap<int> heap;
	heap.insert(2);
	heap.insert(3);
	heap.insert(10);
	heap.insert(4);
	heap.insert(1);
	heap.insert(7);
	heap.insert(9);
	heap.insert(6);
	heap.insert(8);
	heap.insert(5);
	heap.insert(11);
	ASSERT_EQ(heap.min(), 1);
}

TEST(TestMinHeap, check_func_min_throw) {
	MinHeap<int> heap;
	ASSERT_ANY_THROW(heap.min());
}

TEST(TestMinHeap, check_func_remove_min) {
	MinHeap<int> heap;
	heap.insert(2);
	heap.insert(3);
	heap.insert(10);
	heap.insert(4);
	heap.insert(1);
	heap.insert(7);
	heap.insert(9);
	heap.insert(6);
	heap.insert(8);
	heap.insert(5);
	heap.insert(11);
	heap.remove_min();
	ASSERT_EQ(heap.data()[0], 2);
	ASSERT_EQ(heap.data()[1], 3);
	ASSERT_EQ(heap.data()[4], 5);
	ASSERT_EQ(heap.data()[9], 11);
}

TEST(TestMinHeap, check_func_min_hepify) {
	int* arr = new int[7] {3, 7, 1, 5, 8, 6, 2};
	MinHeap<int> heap(7, arr);
	ASSERT_EQ(heap.data()[0], 1);
	ASSERT_EQ(heap.data()[1], 5);
	ASSERT_EQ(heap.data()[2], 2);
	ASSERT_EQ(heap.data()[3], 7);
	ASSERT_EQ(heap.data()[4], 8);
	ASSERT_EQ(heap.data()[5], 6);
	ASSERT_EQ(heap.data()[6], 3);
	delete[] arr;
}

TEST(TestMaxHeap, check_func_sorted) {
	int* arr = new int[7] {3, 7, 1, 5, 8, 6, 2};
	sorted(arr, 7);
	ASSERT_EQ(arr[0], 1);
	ASSERT_EQ(arr[1], 2);
	ASSERT_EQ(arr[2], 3);
	ASSERT_EQ(arr[3], 5);
	ASSERT_EQ(arr[4], 6);
	ASSERT_EQ(arr[5], 7);
	ASSERT_EQ(arr[6], 8);
	delete[] arr;
}