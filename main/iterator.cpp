// Copyright 2024 Marina Usova

#define LIST_ITER
#ifdef LIST_ITER

#include <iostream>
#include <iomanip>
#include "../lib_list/list.h"
#include "../lib_list/node.h"

int iter() {
    Tlist<int> list = Tlist<int>();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    for (Tlist<int>::iterator it = list.begin(); it != list.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}

#endif  // LIST_ITER