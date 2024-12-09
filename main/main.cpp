// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"
#include "../lib_stack/stack.h"
#include "../lib_lstack/lstack.h"
#include "../lib_dmassive/TDmassive.h"
#include "../lib_list/list.h"
#include "../lib_list/node.h"
#include "../lib_lexem/lexem.h"
#include "string.h"
#include <chrono>

void exp_list_test_1(const long long n) {
    size_t node_size = sizeof(TNode<int>);
    size_t list_size = sizeof(Tlist<int>);
    Tlist<int> list = Tlist<int>();
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; i++){
        list.push_back(2);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << list_size + node_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void exp_list_test_2(const long long n) {
    size_t node_size = sizeof(TNode<int>);
    size_t list_size = sizeof(Tlist<int>);
    Tlist<int> list = Tlist<int>();
    for (long long i = 0; i < n; i++) {
        if (i == n - 1)
            list.push_back(4);
        else
            list.push_back(5);
    }
    auto start = std::chrono::high_resolution_clock::now();
    TNode<int>* s = list.find(4);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << list_size + node_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void exp_list_test_3(long long n) {
    size_t node_size = sizeof(TNode<int>);
    size_t list_size = sizeof(Tlist<int>);
    Tlist<int> list = Tlist<int>();
    for (size_t i = 0; i < n; i++) {
        if (i == n - 1)
            list.push_back(4);
        else
            list.push_back(5);
    }
    auto start = std::chrono::high_resolution_clock::now();
    list.pop_back();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << list_size + node_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void exp_list_test_4(const long long n) {
    size_t node_size = sizeof(TNode<int>);
    size_t list_size = sizeof(Tlist<int>);
    Tlist<int> list = Tlist<int>();
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; i++) {
        list.push_front(2);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << list_size + node_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void exp_massive_test_1(const long long n) {
    size_t int_size = sizeof(int);
    size_t mas_size = sizeof(TDMassive<int>);
    TDMassive<int> mas = TDMassive<int>(n);
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; i++) {
        mas.push_back(2);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << mas_size + int_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void exp_massive_test_2(const long long n) {
    size_t int_size = sizeof(int);
    size_t mas_size = sizeof(TDMassive<int>);
    TDMassive<int> mas = TDMassive<int>(n);
    for (long long i = 0; i < n; i++) {
        if (i == n - 1)
            mas.push_back(4);
        else
            mas.push_back(5);
    }
    auto start = std::chrono::high_resolution_clock::now();
    size_t d = mas.find_first(4);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << mas_size + int_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void exp_massive_test_3(long long n) {
    size_t int_size = sizeof(int);
    size_t mas_size = sizeof(TDMassive<int>);
    TDMassive<int> mas = TDMassive<int>(n);
    for (size_t i = 0; i < n; i++) {
        if (i == n - 1)
            mas.push_back(4);
        else
            mas.push_back(5);
    }
    auto start = std::chrono::high_resolution_clock::now();
    mas.remove_first(4);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << mas_size + int_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void exp_massive_test_4(const long long n) {
    size_t int_size = sizeof(int);
    size_t mas_size = sizeof(TDMassive<int>);
    TDMassive<int> mas = TDMassive<int>(n, 1);
    auto start = std::chrono::high_resolution_clock::now();
    mas.push_front(2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << mas_size + int_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void Exp_Stack_Massive_test_1(const long long n) {
    size_t stack_size = sizeof(TStack<int>);
    size_t mas_size = sizeof(TDMassive<int>);
    size_t data_size = sizeof(int);

    TStack<int> stack = TStack<int>(n);
    auto start = std::chrono::high_resolution_clock::now();
    stack.push(2);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << stack_size + mas_size + data_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void Exp_Stack_Massive_test_2(const long long n) {
    size_t stack_size = sizeof(TStack<int>);
    size_t mas_size = sizeof(TDMassive<int>);
    size_t data_size = sizeof(int);

    TStack<int> stack = TStack<int>(n);
    for (size_t i = 0; i < n; i++) {
        stack.push(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    stack.pop();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << stack_size + mas_size + data_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void Exp_Stack_List_test_1(const long long n) {
    TLStack<int> stack = TLStack<int>(n);
    size_t node_size = sizeof(TNode<int>);
    size_t list_size = sizeof(stack._data);
    size_t stack_size = sizeof(stack);
    auto start = std::chrono::high_resolution_clock::now();
    stack.push(2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << stack_size + list_size + node_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void Exp_Stack_List_test_2(const long long n) {
    TLStack<int> stack = TLStack<int>(n);
    size_t node_size = sizeof(TNode<int>);
    size_t list_size = sizeof(stack._data);
    size_t stack_size = sizeof(stack);
    for (size_t i = 0; i < n; i++) {
        stack.push(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    stack.pop();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Used Memory: " << stack_size + list_size + node_size * n << " byte" << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}

void Check_spliting_exp() {
    std::string str = "3.15 +   sin(x)+5*x+3/c";
    Expression exp = Expression(str);
    exp.print();
}

int main() {
    exp_massive_test_4(100000);
}
#endif  // EASY_EXAMPLE
