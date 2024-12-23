#include <iostream>
#include <string>
#include <cmath>
#include "../lib_list/list.h"
#include "../lib_list/node.h"
#include "exception"
#include "../lib_stack/stack.h"
#include "map"
#include "../lib_lexem/operations.h"
#include <limits>

enum LexemType {
    BRACKET,
    VARIABLE,
    OPERATION,
    FUNCTION,
    INT_CONST,
    FLOAT_CONST,
    NONE
};

bool is_number(char symbol) {
    return symbol >= '0' && symbol <= '9';
}

bool is_string(char symbol) {
    return (symbol >= 65 && symbol <= 90) || (symbol >= 97 && symbol <= 122);
}

bool is_operation(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}

bool is_function(std::string exp) {
    std::string func[4] = { "sin", "cos", "tg", "ctg" };
    for (size_t i = 0; i < 4; i++) {
        if (exp == func[i])
            return true;
    }
    return false;
}

class Lexem {
protected:
    std::string _name;
    LexemType _type;
    float _value;
public:
    Lexem(std::string name, LexemType type) : _name(name), _type(type) {}
    Lexem() : _name(""), _type(NONE) {}

    void set_name(std::string name) { _name = name; }
    void set_type(LexemType type) { _type = type; }

    std::string name() { return _name; }
    LexemType type() { return _type; }

    void set_value(float value) { _value = value; }
    float value() { return _value; }

    friend std::ostream& operator<<(std::ostream& out, const Lexem& lexem);
};

std::ostream& operator<<(std::ostream& out, const Lexem& lexem) { out << lexem._name; return out; }

class FloatConst : public Lexem {
public:
    FloatConst(std::string exp) : Lexem(exp, FLOAT_CONST) {
        int curr_pos = 0;
        float result = 0;
        while (is_number(exp[curr_pos])) {
            result = result * 10 + (exp[curr_pos] - '0');
            curr_pos++;
        }
        if (exp[curr_pos] == '.') {
            curr_pos++;
            float float_part = 0.0;
            int accuracy = 0;
            while (is_number(exp[curr_pos])) {
                float_part = float_part * 10 + (exp[curr_pos] - '0');
                curr_pos++;
                accuracy++;
            }
            result += float_part * pow(10, -accuracy);
        }
        _value = result;
    }
};

class IntConst : public Lexem {
public:
    IntConst(std::string exp) : Lexem(exp, INT_CONST) {
        int result = 0;
        for (size_t i = 0; i < exp.size(); i++) {
            result = result * 10 + (exp[i] - '0');
        }
        _value = result;
    }
};

class Bracket : public Lexem {
public:
    Bracket(std::string exp) : Lexem(exp, BRACKET) {}
};

class Variable : public Lexem {
public:
    Variable(std::string exp) : Lexem(exp, VARIABLE) {}
};

class Operation : public Lexem {
public:
    Operation(std::string exp) : Lexem(exp, OPERATION) {}
    float value() = delete;
    void set_value(float value) = delete;
};

class Function : public Lexem {
public:
    Function(std::string exp) : Lexem(exp, FUNCTION) {}
    float value() = delete;
    void set_value(float value) = delete;
};

class Expression {
    Tlist<Lexem> _expression;
    std::map<std::string, int> priority;
public:
    Expression(std::string exp) { 
        delete_spaces(&exp); parse(exp); check();
        priority = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, 
        {"sin", 4}, {"cos", 4}, {"tg", 4}, {"ctg", 4}, {"(", 5} };
        build_polish_record();
    }
    float calculate(){
        set_vars_values();
        TStack<float> stack;
        Operations op;
        for (auto it = _expression.begin(); it!=_expression.end(); it++){
            if ((*it).type() == INT_CONST || (*it).type() == FLOAT_CONST || (*it).type() == VARIABLE){
                stack.push((*it).value());
            }
            else{
                if ((*it).type() == FUNCTION){
                    float res = op.execute((*it).name(), stack.top());
                    stack.pop();
                    stack.push(res);
                }
                else{
                    float cur = stack.top();
                    stack.pop();
                    float res = op.execute((*it).name(), stack.top(), cur);
                    stack.pop();
                    stack.push(res);
                }
            }
        }
        return stack.top();
    }
    void print() {
        for (auto it = _expression.begin(); it != _expression.end(); it++) {
            std::cout << *it << " ";
        }
    }
    std::string str() {
        std::string s;
        for (auto it = _expression.begin(); it != _expression.end(); it++) {
            s.append((*it).name());
        }
        return s;
    }
private:
    void delete_spaces(std::string* exp) {
        for (size_t i = 0; i < exp->size(); i++) {
            if ((*exp)[i] == ' ') {
                exp->replace(i, 1, "");
                i--;
            }
        }
    }

    void parse(std::string exp) {
        std::map<std::string, float> var;
        int curr_pos = 0;
        while (curr_pos < exp.size()) {
            if (is_number(exp[curr_pos])) {
                int start_pos = curr_pos;
                while (is_number(exp[curr_pos])) { curr_pos++; }
                if (exp[curr_pos] == '.') {
                    curr_pos++;
                    while (is_number(exp[curr_pos])) { curr_pos++; }
                    FloatConst new_lexem(exp.substr(start_pos, curr_pos - start_pos));
                    _expression.push_back(new_lexem);
                }
                else {
                    IntConst new_lexem(exp.substr(start_pos, curr_pos - start_pos));
                    _expression.push_back(new_lexem);
                }
            }
            else if (is_operation(exp[curr_pos])) {
                Operation new_lexem(exp.substr(curr_pos, 1));
                _expression.push_back(new_lexem);
                curr_pos++;
            }
            else if (is_string(exp[curr_pos])) {
                int start_pos = curr_pos;
                std::string str;
                while (is_string(exp[curr_pos])) {
                    if (exp[curr_pos] == 'c' || exp[curr_pos] == 's'){
                        if (is_function(exp.substr(curr_pos, 3))){
                            if (str.length()!=0){
                                Variable new_lexem(str);
                                _expression.push_back(new_lexem);
                                str.clear();
                            }
                            Function new_lexem = Function(exp.substr(curr_pos, 3));
                            curr_pos+=3;
                            _expression.push_back(new_lexem);
                        }
                        else {
                            str.append(exp.substr(curr_pos, 1));
                            curr_pos+=1;
                        }
                    }
                    else if (exp[curr_pos] == 't'){
                        if (is_function(exp.substr(curr_pos, 2))){
                            if (str.length()!=0){
                                Variable new_lexem(str);
                                _expression.push_back(new_lexem);
                                str.clear();
                            }
                            Function new_lexem = Function(exp.substr(curr_pos, 2));
                            curr_pos+=2;
                            _expression.push_back(new_lexem);
                        }
                        else {
                            str.append(exp.substr(curr_pos, 1));
                            curr_pos+=1;
                        }
                    }
                    else{
                        str.append(exp.substr(curr_pos, 1));
                        curr_pos++;
                    }
                }
                if (str.length()!=0){
                    Variable new_lexem(str);
                    _expression.push_back(new_lexem);
                    str.clear();
                }
            }
            else if (exp[curr_pos] == '(' || exp[curr_pos] == ')') {
                Bracket new_lexem(exp.substr(curr_pos, 1));
                _expression.push_back(new_lexem);
                curr_pos++;
            }
            else {
                throw std::logic_error("incorrect symbol");
            }
        }
    }
    void check() {
        Tlist<Lexem>::iterator prev = _expression.begin();
        Tlist<Lexem>::iterator next = _expression.begin();
        TStack<Lexem> stack = TStack<Lexem>();
        for (auto it = _expression.begin(); it != _expression.end(); it++) {
            if (next!= _expression._tail)
                next++;
            if ((*it).type() == OPERATION) {
                if ((*it).name() == "-" && it == _expression.begin()) {
                    Operation zero_lexem("0");
                    _expression.push_front(zero_lexem);
                    continue;
                }
                else if (it == _expression.begin()) {
                    throw std::logic_error("unexpected first symbol");
                }
                else if ((*prev).name()!=")" && ((*prev).type() == OPERATION || (*prev).type() == FUNCTION || (*prev).name()=="(")) {
                    if ((*prev).type() == BRACKET && (*prev).name() == "(" && (*it).name() == "-") {
                        Operation zero_lexem("0");
                        _expression.push_front(zero_lexem);
                    }
                    else
                        throw std::logic_error("incorrect a");
                }
                else if ((*next).name() == ")" || (*next).type() == OPERATION || it ==_expression._tail) {
                    throw std::logic_error("incorrect b");
                }
            }
            else if ((*it).type() == FUNCTION) {
                if (it!= _expression.begin() && ((*prev).type() == FUNCTION || (*prev).type() == VARIABLE || (*prev).type() == FLOAT_CONST || (*prev).type() == INT_CONST)) {
                    throw std::logic_error("incorrect c");
                }
                else if ((*prev).name() == ")") {
                    throw std::logic_error("incorrect d");
                }
                else if ((*next).name() != "(" && it!=_expression._tail) {
                    throw std::logic_error("incorrect e");
                }
            }
            else if ((*it).type() == VARIABLE) {
                if (it != _expression.begin() && ((*prev).type() == FUNCTION || (*prev).type() == FLOAT_CONST || (*prev).type() == INT_CONST || (*prev).name() == ")"))
                    throw std::logic_error("incorrect q");
                else if((*next).name()!=")" && (*next).type()!=OPERATION && it!=_expression._tail)
                    throw std::logic_error("incorrect w");
            }
            else if ((*it).type() == FLOAT_CONST || (*it).type() == INT_CONST) {
                if (it!= _expression.begin() && (*prev).type()!=OPERATION && (*prev).name() != "(")
                    throw std::logic_error("incorrect r");
                else if((*next).type()!=OPERATION && (*next).name() != ")" && it!=_expression._tail)
                    throw std::logic_error("incorrect y");
            }
            else if ((*it).type() == BRACKET) {
                if ((*it).name() == "(")
                    stack.push((*it));
                else if ((*it).name() == ")") {
                    if (stack.isEmpty())
                        throw std::logic_error("incorrect p");
                    else
                        stack.pop();
                }
            }
            if (it!=_expression.begin()) {
                prev++;
            }
        }
        if (!stack.isEmpty())
            throw std::logic_error("incorrect n");
    }
    void build_polish_record(){
        Tlist<Lexem> record;
        TStack<Lexem> stack;
        for (auto it = _expression.begin(); it!=_expression.end(); it++){
            if ((*it).type() == INT_CONST || (*it).type() == FLOAT_CONST || (*it).type() == VARIABLE){
                record.push_back((*it));
            }
            else{
                if (stack.isEmpty()){
                    stack.push((*it));
                }
                else if ((*it).type() == BRACKET && (*it).name() == ")") {
                    while (stack.top().name()!="("){
                        record.push_back(stack.top());
                        stack.pop();

                    }
                    stack.pop();
                }
                else if(priority[(*it).name()]>priority[stack.top().name()]){
                    stack.push((*it));
                }
                else if(priority[(*it).name()] == priority[stack.top().name()]){
                    if (stack.top().type() != BRACKET){
                        record.push_back(stack.top());
                        stack.pop();
                    }
                    stack.push((*it));
                }
                else{
                    if (stack.top().type() != BRACKET){ 
                        while (!stack.isEmpty() && stack.top().name()!="(" && priority[stack.top().name()]>=priority[(*it).name()]){
                            record.push_back(stack.top());
                            stack.pop();
                        }
                    }
                    stack.push((*it));
                }
            }
        }
        while (!stack.isEmpty()){
            record.push_back(stack.top());
            stack.pop();
        }
        _expression = record;
    }
    void set_vars_values(){
        std::map<std::string, float> var;
        for (auto it = _expression.begin(); it!=_expression.end(); it++){
            if ((*it).type() == VARIABLE){
                std::string str = (*it).name();
                if (var.count(str) == 0){
                    float value;
                    std::cout << "enter a value " << str << ": "; std::cin >> value;
                    std::cout << std::endl;
                    (*it).set_value(value);
                    var[str] = value; 
                }
                else
                    (*it).set_value(var[str]);
            }
        }
    }
};