// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"
#include "../lib_list/list.h"
#include "../lib_list/node.h"
#include "../lib_stack/stack.h"
#include "../lib_lstack/lstack.h"
#include <chrono>

int main() {
    size_t node_size = sizeof(TNode<int>);
    size_t list_size = sizeof(Tlist<int>);
    Tlist<int> list = Tlist<int>();
    long long n = 100000000;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; i++) {
        list.push_back(5);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Используемая память: " << list_size + node_size * n << "байт" << std::endl;
    std::cout << "Время выполнения: " << duration.count() << " миллисекунд" << std::endl;
    return 0; //Test 1
    

    /*Tlist<int> list = Tlist<int>();
    long long n = 100000000;
    for (size_t i = 0; i < n; i++) {
        if (i == n-1)
            list.push_back(4);
        else
            list.push_back(5);
    }
    auto start = std::chrono::high_resolution_clock::now();
    TNode<int>* s = list.find(4);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Используемая память: " << list_size + node_size * n << "байт" << std::endl;
    std::cout << "Время выполнения: " << duration.count() << " миллисекунд" << std::endl;
    return 0;*/ //Test 2

    /*Tlist<int> list = Tlist<int>();
    long long n = 100000;
    for (size_t i = 0; i < n; i++) {
        if (i == n-1)
            list.push_back(4);
        else
            list.push_back(5);
    }
    auto start = std::chrono::high_resolution_clock::now();
    list.pop_back();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Используемая память: " << list_size + node_size * n << "байт" << std::endl;
    std::cout << "Время выполнения: " << duration.count() << " миллисекунд" << std::endl;
    return 0;*/ //Test 3

    /*Tlist<int> list = Tlist<int>();
    long long n = 10000000;
    for (size_t i = 0; i < n; i++) {
        list.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; i++) {
        list.pop_front();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Используемая память: " << list_size + node_size * n << "байт" << std::endl;
    std::cout << "Время выполнения: " << duration.count() << " миллисекунд" << std::endl;
    return 0;*/ //Test 3
} //Exp_List

//int main() {
//    size_t stack_size = sizeof(TStack<int>);
//    size_t data_size = sizeof(int);
//
//	long long n = 100000;
//	TStack<int> stack = TStack<int>(n);
//	auto start = std::chrono::high_resolution_clock::now();
//	for (size_t i = 0; i < n; i++) {
//		stack.push(2);
//	}
//	auto end = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    std::cout << "Используемая память: " << stack_size + data_size * n << "байт" << std::endl;
//	std::cout << "Время выполнения: " << duration.count() << " миллисекунд" << std::endl;
//	return 0; //Test 1
//
//	/*long long n = 10000000;
//	TStack<int> stack = TStack<int>(n);
//	auto start = std::chrono::high_resolution_clock::now();
//	for (size_t i = 0; i < n; i++) {
//		stack.push(i);
//	}
//	auto start = std::chrono::high_resolution_clock::now();
//	for (size_t i = 0; i < n; i++) {
//		stack.pop();
//	}
//	auto end = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    std::cout << "Используемая память: " << stack_size + data_size * n << "байт" << std::endl;
//	std::cout << "Время выполнения: " << duration.count() << " миллисекунд" << std::endl;
//	return 0;*/ //Test 2
//} //Exp_Stack_Massive

//int main() {
//	long long n = 1000000000000;
//	TLStack<int> stack = TLStack<int>(n);
//    size_t node_size = sizeof(TNode<int>);
//    size_t list_size = sizeof(stack._data);
//    size_t stack_size = sizeof(stack);
//	auto start = std::chrono::high_resolution_clock::now();
//	for (size_t i = 0; i < n; i++) {
//		stack.push(2);
//	}
//	auto end = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    std::cout << "Используемая память: " << stack_size + list_size + node_size * n << "байт" << std::endl;
//    std::cout << "Время выполнения: " << duration.count() << " миллисекунд" << std::endl;
//	return 0; //Test 1
//
//	/*long long n = 1000000000000;
//	TLStack<int> stack = TLStack<int>(n);
//    size_t node_size = sizeof(TNode<int>);
//    size_t list_size = sizeof(stack._data);
//    size_t stack_size = sizeof(stack);
//	for (size_t i = 0; i < n; i++) {
//		stack.push(i);
//	}
//	auto start = std::chrono::high_resolution_clock::now();
//	for (size_t i = 0; i < n; i++) {
//		stack.pop();
//	}
//	auto end = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//	std::cout << "Используемая память: " << stack_size + list_size + node_size * n << "байт" << std::endl;
//    std::cout << "Время выполнения: " << duration.count() << " миллисекунд" << std::endl;
//	return 0;*/ //Test 2
//
//} //Exp_Stack_List
#endif  // EASY_EXAMPLE
