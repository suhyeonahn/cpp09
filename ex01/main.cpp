#include "RPN.hpp"

int main(int argc, char**argv) {
    if (argc != 2) {
        std::cout << "Error: bad argument(s)" << std::endl;
        return 1;
    }
    
    RPN rpn(argv[1]);
    try {
        float result = rpn.calcul();
        std::cout << "Result is " << result << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}