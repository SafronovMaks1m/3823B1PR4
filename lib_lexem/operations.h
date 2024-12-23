#include "iostream"
#include "cmath"
#include "string"
#include <functional>

class Operations {
public:
    float execute(const std::string& op, float a, float b) const {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b != 0) 
                return a / b;
            else 
                throw std::runtime_error("Division by zero");
        }
        if (op == "^") return pow(a, b);
    }
    float execute(const std::string& op, float a) const {
        if (op == "sin") return sin(a);
        if (op == "cos") return cos(a);
        if (op == "tg") return tan(a);
        if (op == "ctg") return cos(a)/sin(a);
    }
};