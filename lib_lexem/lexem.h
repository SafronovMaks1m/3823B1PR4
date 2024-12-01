#include <iostream>
#include <string>
#include <cmath>
#include "../lib_list/list.h"
#include "../lib_list/node.h"
#include "exception"

enum ParsingErrorType {
    EXTRA_BRACKET = 1,
    MISSING_BRACKET = 2,
    MISMATCHED_BRACKET = 3,
    UNVALID_BRACKET = 4,
    NON_ERROR = 0
};

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
public:
    Lexem(std::string name, LexemType type) : _name(name), _type(type) {}
    Lexem() : _name(""), _type(NONE) {}

    void set_name(std::string name) { _name = name; }
    void set_type(LexemType type) { _type = type; }

    std::string name() { return _name; }
    LexemType type() { return _type; }

    friend std::ostream& operator<<(std::ostream& out, const Lexem& lexem);
};

std::ostream& operator<<(std::ostream& out, const Lexem& lexem) { out << lexem._name; return out; }

class FloatConst : public Lexem {
    float _value;
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

    void set_value(float value) { _value = value; }
    float value() { return _value; }
};

class IntConst : public Lexem {
    int _value;
public:
    IntConst(std::string exp) : Lexem(exp, INT_CONST) {
        int result = 0;
        for (size_t i = 0; i < exp.size(); i++) {
            result = result * 10 + (exp[i] - '0');
        }
        _value = result;
    }

    void set_value(int value) { _value = value; }
    int value() { return _value; }
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
};

class Function : public Lexem {
public:
    Function(std::string exp) : Lexem(exp, FUNCTION) {}
};

class Expression {
    Tlist<Lexem> _expression;
    // <what type?> polish_record;
public:
    Expression(std::string exp) { delete_spaces(&exp); parse(exp); }
    //void set_vars_values();
    //void calculate();
    void print() {
        // std::cout << _expression;  // ���� � ������ ���� <<
        for (auto it = _expression.begin(); it != _expression.end(); it++) {
            std::cout << *it << " ";
        }
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
        int total = 0;
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
                if (is_operation(exp[curr_pos + 1]))
                    throw std::logic_error("invalid order of operations");
                Operation new_lexem(exp.substr(curr_pos, 1));
                _expression.push_back(new_lexem);
                curr_pos++;
            }
            else if (is_string(exp[curr_pos])) {
                int start_pos = curr_pos;
                while (is_string(exp[curr_pos])) { curr_pos++; }
                if (curr_pos - start_pos == 1) {
                    Variable new_lexem(exp.substr(start_pos, 1));
                    _expression.push_back(new_lexem);
                }
                else {
                    if (!is_function(exp.substr(start_pos, curr_pos - start_pos)))
                        throw std::logic_error("incorrect function");
                    Function new_lexem(exp.substr(start_pos, curr_pos - start_pos));
                    _expression.push_back(new_lexem);
                }
            }
            else if (exp[curr_pos] == '(' || exp[curr_pos] == ')') {
                if (exp[curr_pos] == '(')
                    total++;
                else if (exp[curr_pos] == ')') {
                    if (total == 0)
                        throw std::logic_error("incorrect placement of brackets");
                    total--;
                }
                Bracket new_lexem(exp.substr(curr_pos, 1));
                _expression.push_back(new_lexem);
                curr_pos++;
            }
            else {
                throw std::logic_error("incorrect symbol");
            }
        }
        if (total != 0)
            throw std::logic_error("incorrect placement of brackets");
    }
    //void check();
    //void build_polish_record();
};