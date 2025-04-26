#include <gtest.h>
#include "../lib_max_heap/MaxHeap.h"

TEST(TestMaxHeap, check_func_insert) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	ASSERT_EQ(heap.data()[0], 12);
	ASSERT_EQ(heap.data()[1], 8);
	ASSERT_EQ(heap.data()[2], 11);
	ASSERT_EQ(heap.data()[3], 5);
	ASSERT_EQ(heap.data()[4], 7);
	ASSERT_EQ(heap.data()[5], 10);
	ASSERT_EQ(heap.data()[6], 6);
	ASSERT_EQ(heap.data()[7], 2);
	ASSERT_EQ(heap.data()[8], 4);
	ASSERT_EQ(heap.data()[9], 1);
	ASSERT_EQ(heap.data()[10], 3);
	ASSERT_EQ(heap.data()[11], 9);
}

TEST(TestMaxHeap, check_func_left) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	ASSERT_EQ(heap.left(3), 7);
	ASSERT_EQ(heap.left(2), 5);
	ASSERT_EQ(heap.left(4), 9);
}

TEST(TestMaxHeap, check_func_right) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	ASSERT_EQ(heap.right(3), 8);
	ASSERT_EQ(heap.right(2), 6);
	ASSERT_EQ(heap.right(4), 10);
}

TEST(TestMaxHeap, check_func_parent) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	ASSERT_EQ(heap.parent(3), 1);
	ASSERT_EQ(heap.parent(10), 4);
}

TEST(TestMaxHeap, check_func_left_throw) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	ASSERT_ANY_THROW(heap.left(15));
}

TEST(TestMaxHeap, check_func_empty) {
	MaxHeap<int> heap;
	ASSERT_EQ(heap.is_empty(), true);
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	ASSERT_EQ(heap.is_empty(), false);
}

TEST(TestMaxHeap, check_func_emplace_up) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	heap.emplace(4, 9);
	ASSERT_EQ(heap.data()[1], 9);
	ASSERT_EQ(heap.data()[4], 8);
}

TEST(TestMaxHeap, check_func_emplace_down) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	heap.emplace(0, 5);
	ASSERT_EQ(heap.data()[0], 11);
	ASSERT_EQ(heap.data()[2], 10);
	ASSERT_EQ(heap.data()[5], 9);
	ASSERT_EQ(heap.data()[11], 5);
}

TEST(TestMaxHeap, check_func_emplace_throw) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	ASSERT_ANY_THROW(heap.emplace(12, 5));
}

TEST(TestMaxHeap, check_func_max) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	ASSERT_EQ(heap.max(), 12);
}

TEST(TestMaxHeap, check_func_max_throw) {
	MaxHeap<int> heap;
	ASSERT_ANY_THROW(heap.max());
}

TEST(TestMaxHeap, check_func_remove_max) {
	MaxHeap<int> heap;
	heap.insert(11);
	heap.insert(7);
	heap.insert(10);
	heap.insert(5);
	heap.insert(8);
	heap.insert(9);
	heap.insert(6);
	heap.insert(2);
	heap.insert(4);
	heap.insert(1);
	heap.insert(3);
	heap.insert(12);
	heap.remove_max();
	ASSERT_EQ(heap.data()[0], 11);
	ASSERT_EQ(heap.data()[2], 10);
	ASSERT_EQ(heap.data()[5], 9);
	ASSERT_EQ(heap.data()[6], 6);
} 

TEST(TestMaxHeap, check_func_max_heapify) {
	int* arr = new int[7] {3, 7, 1, 5, 8, 6, 2};
	MaxHeap<int> heap(7, arr);
	ASSERT_EQ(heap.data()[0], 8);
	ASSERT_EQ(heap.data()[1], 7);
	ASSERT_EQ(heap.data()[2], 6);
	ASSERT_EQ(heap.data()[3], 5);
	ASSERT_EQ(heap.data()[4], 3);
	ASSERT_EQ(heap.data()[5], 1);
	ASSERT_EQ(heap.data()[6], 2);
	delete[] arr;
}

TEST(TestMaxHeap, check_func_reverse_sorted) {
	int* arr = new int[7] {3, 7, 1, 5, 8, 6, 2};
	reverse_sorted(arr, 7);
	ASSERT_EQ(arr[0], 8);
	ASSERT_EQ(arr[1], 7);
	ASSERT_EQ(arr[2], 6);
	ASSERT_EQ(arr[3], 5);
	ASSERT_EQ(arr[4], 3);
	ASSERT_EQ(arr[5], 2);
	ASSERT_EQ(arr[6], 1);
	delete[] arr;
}