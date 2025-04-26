// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "cmath"
#include "../lib_easy_example/easy_example.h"
#include "../lib_stack/stack.h"
#include "../lib_lstack/lstack.h"
#include "../lib_dmassive/TDmassive.h"
#include "../lib_list/list.h"
#include "../lib_list/node.h"
#include "../lib_lexem/lexem.h"
#include "../lib_polinom/polinom.h"
#include "../lib_monom/monom.h"
#include "../lib_bin_tree/TBinTree.h"
#include "../lib_tree_output/TreeOut.h"
#include "../lib_ht_shuffle/HTSuffle.h"
#include "../lib_ht_lists/HTLists.h"
#include "../lib_dsu/dsu.h"
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

void Tree_Output1() {
    BSearchTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(121);
    tree.insert(123);
    tree.insert(125111);
    tree.insert(1000001);
    tree.insert(0);
    tree.insert(4);
    tree.insert(18);
    tree.insert(3);
    tree.tree_out(tree.head());
}

void Tree_Output2() {
    BSearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(6);
    tree.insert(2);
    tree.insert(4);
    tree.insert(7);
    tree.tree_out(tree.head());
}

void combining_dict_htsuffle(HTSuffle<std::string, int>& hash1, HTSuffle<std::string, int>& hash2) {
    HTSuffle<std::string, int> res = HTSuffle<std::string, int>(hash1.size()+hash2.size());
    for (size_t i = 0; i < hash1.capacity(); i++) {
        if (hash1.data().states()[i] != State::empty) {
            res.insert(hash1.data()[i].first(), hash1.data()[i].second());
        }
    }
    std::cout << std::endl;
    for (size_t i = 0; i < hash2.capacity(); i++) {
        if (hash2.data().states()[i] != State::empty) {
            try {
                res.find(hash2.data()[i].first());
            }
            catch (std::logic_error&) {
                res.insert(hash2.data()[i].first(), hash2.data()[i].second());
            }
        }
    }
    for (size_t i = 0; i < res.capacity(); i++) {
        if (res.data().states()[i] != State::empty)
            std::cout << "(" << res.data()[i].first() << ", " << res.data()[i].second() << ") ";
    }
    std::cout << std::endl;
}

template<class TKey, class TVal>
void combining_dict_htlist(HTList<TKey, TVal>& hash1, HTList<TKey, TVal>& hash2) {
    HTList<TKey, TVal> res = HTList<TKey, TVal>(hash1.size() + hash2.size());
    for (size_t i = 0; i < hash1.capacity(); i++) {
        if (hash1.data().states()[i] != State::empty) {
            TNode<TDict<TKey, TVal>>* cur = hash1.data()[i]._head;
            while (cur != nullptr) {
                res.insert(cur->value().key(), cur->value().value());
                cur = cur->next();
            }
        }
    }

    for (size_t i = 0; i < hash2.capacity(); i++) {
        if (hash2.data().states()[i] != State::empty) {
            TNode<TDict<TKey, TVal>>* cur = hash2.data()[i]._head;
            while (cur != nullptr) {
                try {
                    res.find(cur->value().key());
                }
                catch (std::logic_error&) {
                    res.insert(cur->value().key(), cur->value().value());
                }
                cur = cur->next();
            }
        }
    }
    for (size_t i = 0; i < res.capacity(); i++) {
        if (res.data().states()[i] != State::empty) {
            TNode<TDict<TKey, TVal>>* cur = res.data()[i]._head;
            while (cur != nullptr) {
                std::cout << "(" << cur->value().key() << ", " << cur->value().value() << ") ";
                cur = cur->next();
            }
        }
    }
    std::cout << std::endl;
}

void example_hash() {
    HTList<std::string, int> table1(4);
    table1.insert("dfgdfg", 1);
    size_t ind = table1.hash("dfgdfg");
    table1.insert("ghfgh", 2);
    table1.insert("fsdffds", 3);
    table1.insert("kkjlkj", 4);
    HTList<std::string, int> table2(5);
    table2.insert("sdfsfd", 15);
    table2.insert("cvbvcb", 16);
    table2.insert("waewe", 17);
    table2.insert("kkjlkj", 5);
    table2.insert("dfgdfg", 3);
    combining_dict_htlist(table1, table2);
}

size_t random_dsu() {
    int s = rand() % 101;
    return s;
}

void cursor_move(int y, int x) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void print_maze(TDMassive<int>& mas, size_t width) {
    int s = std::to_string(mas[mas.size() - 1]).length();
    for (size_t i = 0; i < mas.size(); i++) {
        std::cout << std::string((s - std::to_string(mas[i]).length()), ' ') << mas[i] << "|";
        if ((i + 1) % width == 0) {
            std::cout << std::endl;
            std::cout << std::string(width * (s + 1), '-') << std::endl;
        }
    }
}

void print_ending_maze(TDMassive<int>& mas, DSU& dsu, size_t width, size_t hight, int cursor_j) {
    int s = std::to_string(mas[mas.size() - 1]).length();
    for (size_t i = 0; i < hight; i++) {
        cursor_move(i * 2 + 1, cursor_j);
        for (size_t j = 0; j < width; j++) {
            size_t k = i * hight + j;
            std::cout << std::string((s - std::to_string(mas[k]).length()), ' ') << mas[k];
            if (dsu.parent()[k] == 1) {
                if (dsu.parent()[k + 1] == 1) {
                    cursor_move(i * 2 + 2, cursor_j + (j * s + j));
                    std::cout << std::string(s + 1, '-'); 
                    cursor_move(i * 2 + 1, cursor_j+((j + 1) * s + j));
                    std::cout << ' ';

                }
                else {
                    std::cout << '|';
                }
            }
            else {
                cursor_move(i * 2 + 2, cursor_j + (j * s + j));
                std::cout << std::string(s + 1, '-');
                cursor_move(i * 2 + 1, cursor_j + ((j + 1) * s + j));
                std::cout << '|';
            }
        }
        std::cout << std::endl << std::endl;
    }
    cursor_move(hight * 2, cursor_j + s * (width - 1)+ (width - 1));
    std::cout << std::string(s + 1, '-');
}

void maze() {
    srand(time(NULL));
    size_t size = 25, hight = 5, width = 5;
    TDMassive<int> mas(size);
    DSU dsu(25);
    for (size_t i = 0; i < size; i++)
        mas.push_back(i+1);
    print_maze(mas, width);
    size_t i = 0;
    size_t rand_val;
    while (i != size - 1) {
        rand_val = random_dsu();
        if (rand_val >= 0 && rand_val <= 50) {
            if ((i + 1) % width != 0)
                i += 1;
            else
                i += width;
        }
        else {
            if (i / 5 < 4)
                i += width;
            else
                i += 1;
        }
        dsu.uni(1, mas[i]);
    }
    for (size_t i = 0; i < size; i++) {
        if (dsu.parent()[i] == 1)
            std::cout << i + 1 << " ";
    }
    std::cout << std::endl;
    int cursor_j = std::to_string(mas[mas.size() - 1]).length() * width + width + 7;
    print_ending_maze(mas, dsu, width, hight, cursor_j);
}

int main() {
    maze();
}
#endif  // EASY_EXAMPLE
