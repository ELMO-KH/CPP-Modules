#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) {
    *this = other;
}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        this->_stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}

void RPN::calculate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (this->_stack.size() < 2) {
                throw std::runtime_error("Error");
            }
            int b = this->_stack.top();
            this->_stack.pop();
            int a = this->_stack.top();
            this->_stack.pop();

            if (token == "+") this->_stack.push(a + b);
            else if (token == "-") this->_stack.push(a - b);
            else if (token == "*") this->_stack.push(a * b);
            else if (token == "/") {
                if (b == 0) throw std::runtime_error("Error");
                this->_stack.push(a / b);
            }
        } else {
            if (token.length() != 1 || !isdigit(token[0])) {
                throw std::runtime_error("Error");
            }
            int value;
            std::stringstream ss(token);
            ss >> value;
            this->_stack.push(value);
        }
    }

    if (this->_stack.size() != 1) {
        throw std::runtime_error("Error");
    }

    std::cout << this->_stack.top() << std::endl;
}
