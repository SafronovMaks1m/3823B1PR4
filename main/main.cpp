// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "cmath"
#include "../lib_easy_example/easy_example.h"
#include "../lib_stack/stack.h"
#include "../lib_lstack/lstack.h"
#include "../lib_dmassive/TDmassive.h"
#include "../lib_list/list.h"
#include "../lib_list/node.h"
#include "../lib_lexem/lexem.h"
#include "../lib_polinom/polinom.h"
#include "../lib_polinom/monom.h"
#include "string.h"
#include <chrono>

void exp_list_test_1(const long long n) {
    size_t node_size = sizeof(TNode<int>);
    size_t list_size = sizeof(Tlist<int>);
    Tlist<int> list = Tlist<int>();
    auto start = std::chrono::high_resolution_clock::now();
    list.push_back(2);
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
    list.push_front(2);
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
    mas.push_back(2);
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
    mas.pop_front();
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

void Check_calculate_exp() {
    Expression exp1 = Expression("sin(x)-5*y*cos(x)");
    std::cout << exp1.calculate() << std::endl; std::cout << sin(1) - 5 * 2 * cos(1) << std::endl;
    Expression exp2 = Expression("y/3+(k*5*x-2)^5+3.15*p");
    std::cout << exp2.calculate() << std::endl; std::cout << 6 / 3 + pow((1 * 5 * 2 - 2), 5) + 3.15 * 2 << std::endl;
    Expression exp3 = Expression("5*x+(sin(y)*6-z/2+3^x)-tg(m)");
    std::cout <<  exp3.calculate() << std::endl; std::cout << 5 * 2 + (sin(3) * 6 - 9.0 / 2 + 9) - tan(5) << std::endl;
}

void Check_calculate_monom() {
    CPolinom polinom1;
    std::cin >> polinom1;
    CMonom monom;
    std::cin >> monom;
    polinom1.calculator(monom);
}

void Check_calculate_polinom() {
    CPolinom polinom1;
    std::cin >> polinom1;
    CPolinom polinom2;
    std::cin >> polinom2;
    polinom1.calculator(polinom2);
}

void Check_value_point() {
    CPolinom polinom = CPolinom("3.15a^2bc^3+abc+6b^2c^5");
    polinom.valuePoint(); std::cout << 3.15 * pow(2, 2) * 3 * pow(2, 3) + 2 * 3 * 2 + 6 * pow(3, 2) * pow(2, 5);
}

int main() {
    Check_calculate_polinom();
}
#endif  // EASY_EXAMPLE
