// use deque or list - stack
#include <string>
#include <deque>

// MAKE this function as template
std::deque<std::string> split (const std::string &s, char delim) {
    std::deque<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

bool isDigit(std::string str) {
  std::istringstream iss(str);
  int num;

  iss >> num;
  if (iss.fail())
    return false;
  return true;
}

bool isValidExpression(std::deque<std::string> stack) {
    //check if elements are even
    if ((stack.size() < 3) || stack.size() % 2 != 0))
        return false;
    if (!isDigit(stack[0]))
        return false;
    // find other ways to loop even index - num, uneven index - operation
    for (std::deque<std::string>::iterator it = stack.begin() ; it != stack.end(); ++it) {
        if (!isDigit(*it))
            isDate = false;
    }
}

int main(int argc, char**argv) {
    if (argc != 2) {
        std::cerr << "Error: bad argument(s)" << std::endl;
        return 1;
    }
    std::deque<std::string> stack = split(argv[1], ' ');
    
}