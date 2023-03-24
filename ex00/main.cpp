#include "BitcoinExchange.hpp"

int main(int argc, char**argv) {
    if (argc != 2) {
        std::cout << "Error: bad argument(s)" << std::endl;
        return 1;
    }

    BitcoinExchange bitcoinExchange;
    try {
        bitcoinExchange.print(argv[1]);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}