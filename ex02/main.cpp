#include <iostream>
#include <sstream>
#include <string>
#include <deque>

bool isDigit(const std::string &str) {
  std::istringstream iss(str);
  float num;

  iss >> num;
  if (iss.fail())
    return false;
  return true;
}

float ft_stof(const std::string &str) {
  std::istringstream iss(str);
  float num;

  iss >> num;
  return (num);
}

bool isStackDigit(std::deque<std::string> stack) {
    size_t i = 0;
    while (i < stack.size() -1) {
        if (!isDigit(stack[i]))
            return false;
        i++;
    }
    return true;
}

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

void sort(std::deque<float>) {

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

    if (!isStackDigit(stack)) {
        std::cout << "Error: non digit" << std::endl;
        return 1;
    }
    
    std::deque<float> deque;
    for (size_t i = 0; i < stack.size(); i ++) {
        deque.push_back(ft_stof(stack[i]));
    }

    size_t count = (stack.size() - 1) / 2;
    for (size_t i = 0; i < count; i++) {
        int j = 0;
        result = ft_itos(calcul(ft_stoi(stack[j]), ft_stoi(stack[j+1]), stack[j+2]));
        stack.pop_front();
        stack.pop_front();
        stack.pop_front();
        stack.push_front(result);
    }
    std::cout << "Result is " + result << std::endl;
    return 0;
}