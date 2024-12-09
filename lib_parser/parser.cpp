#include "../lib_parser/parser.h"
#include "../lib_stack/stack.h"

bool check_expression(std::string mas) {
    TStack<char> stack = TStack<char>(mas.length());
    for (int i = 0; i < stack._size; i++) {
        if (mas[i] == '(' || mas[i] == '{' || mas[i] == '[' || (mas[i] == '|' && stack.top()!='|')){
            stack.push(mas[i]);
        }
        else if (mas[i] == ')' || mas[i] == '}' || mas[i] == ']' || mas[i] == '|') {
            if (stack.isEmpty()) {
                throw std::logic_error("there is no opening bracket");
            }
            else if (stack.top() == '(' && mas[i] == ')'|| stack.top() == '[' && mas[i] == ']' || stack.top() == '{' && mas[i] == '}' || stack.top() == mas[i]) {
                stack.pop();
            }
            else {
                throw std::logic_error("brackets are not equal");
            }
        }
        else if ((mas[i] < '0' || (mas[i]>'9' && mas[i] < 'A') || (mas[i]>'Z' && mas[i] < 'a') || mas[i]>'z') && (mas[i] != '*' && mas[i] != '/' && mas[i] != '+' && mas[i] != '-')) {
            throw std::logic_error("unidentified object");
        }
    }
    if (stack.isEmpty() == false) {
        throw std::logic_error("The stack is not empty");
    }
    return true;
}