#include "RPN.hpp"

RPN::RPN() : _input(""){}
RPN::RPN(std::string input) : _input(input){}
RPN::RPN( const RPN & src) {*this = src;}
RPN::~RPN() {}

float RPN::calcul() {
    std::stack<float> stack;
    for (std::string::const_iterator it = _input.begin(); it != _input.end(); ++it) {
			char c = *it;
        if (std::isdigit(c)) {
            stack.push(c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            float n1, n2, res;
            if (stack.size() < 2) {
                throw BadFormulaException();
            }
            else {
                n2 = stack.top();
                stack.pop();
                n1 = stack.top();
                stack.pop();
            }
            switch(c) {
                case '+': res = n1 + n2; break;
                case '-': res = n1 - n2; break;
                case '*': res = n1 * n2; break;
                case '/': res = n1 / n2; break;
            }
            stack.push(res);
        }
        else {
            if (c != ' ')
                throw BadCharException();
        }
    }
    if (stack.empty())
        throw LowStackException();
    else if (stack.size() != 1)
        throw BadFormulaException();
    return stack.top();
}

const char *RPN::LowStackException::what() const throw() {
	return "Stack runs low.";
}

const char *RPN::BadCharException::what() const throw() {
	return "Not a valid character.";
}

const char *RPN::BadFormulaException::what() const throw() {
	return "Not a valid formula.";
}