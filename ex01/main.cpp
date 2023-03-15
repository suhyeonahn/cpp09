// use deque or list - stack
#include <iostream>
#include <sstream>
#include <string>
#include <deque>

// MAKE this function as template
std::deque<std::string> split (const std::string &s, char delim) {
    std::deque<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        if (item != "")
            result.push_back(item);
    }

    return result;
}

bool isDigit(const std::string &str) {
  std::istringstream iss(str);
  float num;

  iss >> num;
  if (iss.fail())
    return false;
  return true;
}

bool isOperation(const std::string &str)
{
    const std::string operations = "+-/*";
    char c = str[0];

    for (size_t i = 0; i < operations.size(); i++) {
        if (c == operations[i])
            return true;
    }
    return false;
}

float ft_stoi(const std::string &str) {
  std::istringstream iss(str);
  float num;

  iss >> num;
  return (num);
}

std::string ft_itos(const float &i) {
  std::stringstream ss;
  ss << i;
  std::string str = ss.str();
  return (str);
}

float calcul(const float &a, const float &b, const std::string &str) {
    float result;

    if (str == "+")
        result = a + b;
    if (str == "-")
        result = a - b;
    if (str == "*")
        result = a * b;
    if (str == "/")
        result = a / b;
    
    return (result);
}

bool isValidExpression(std::deque<std::string> stack) {
    //check if elements are even
    if ((stack.size() < 3) || (stack.size() % 2 == 0))
        return false;
    if (!isDigit(stack[0]))
        return false;
    size_t i = 1;
    while (i < stack.size() -1) {
        if (!isDigit(stack[i]) || !isOperation(stack[i+1]))
            return false;
        i += 2;
    }
    return true;
}

int main(int argc, char**argv) {
    if (argc != 2) {
        std::cout << "Error: bad argument(s)" << std::endl;
        return 1;
    }

    std::deque<std::string> stack = split(argv[1], ' ');
    for (size_t i = 0; i < stack.size(); i ++) {
        if (stack[i].empty())
            std::cout << stack[i] << std::endl;
    }

    if (!isValidExpression(stack)) {
        std::cout << "Error: invalid expression" << std::endl;
        return 1;
    }
    
    std::string result;

    size_t count = (stack.size() - 1) / 2;
    for (size_t i = 0; i < count; i++) {
        int j = 0;
        result = ft_itos(calcul(ft_stoi(stack[j]), ft_stoi(stack[j+1]), stack[j+2]));
        stack.pop_front();
        stack.pop_front();
        stack.pop_front();
        stack.push_front(result);
    }
    std::cout << "result is " + result << std::endl;
    return 0;
}