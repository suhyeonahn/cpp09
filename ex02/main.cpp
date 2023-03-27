#include <ctime>
#include "PmergeMe.hpp"
int main(int argc, char**argv) {

    if (argc < 2) {
        std::cout << "Error: No input" << std::endl;
        return 1;
    }
    
    PmergeMe< std::vector<int> > vector(&argv[1]);
    PmergeMe< std::deque<int> > deque(&argv[1]);
    try {
        vector.parse();
        deque.parse();
        vector.print("before(vector): ");
        clock_t start = clock();
        vector.sort();
        clock_t end = clock();
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        vector.print("\nafter(vector): ");
        std::cout << "Time to process a range of " << vector.getContainer().size() << " elements with [std::vector]: "
            << elapsed * 1e9 << " us" << std::endl;
        deque.print("\nbefore(deque): ");
        start = clock();
        deque.sort();
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        deque.print("\nafter(deque): ");
        std::cout << "Time to process a range of " << deque.getContainer().size() << " elements with [std::deque]: "
            << elapsed * 1e9 << " us" << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}