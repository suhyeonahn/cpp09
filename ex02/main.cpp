#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <iterator>  
#include <deque>
#include <vector>

const int K = 5;

bool isDigit(const std::string &str) {
  std::istringstream iss(str);
  int num;

  iss >> num;
  if (iss.fail())
    return false;
  return true;
}

int ft_stoi(const std::string &str) {
  std::istringstream iss(str);
  int num;

  iss >> num;
  return (num);
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        if (item != "")
            result.push_back(item);
    }

    return result;
}

template<typename Container>
void insertionSort(Container & c, int l, int r) {
    for (int i = l; i < r; i++) {
        int temp = c.at(i+1);
        int j = i + 1;
        while (j > l && c.at(j-1) > temp) {
            c.at(j) = c.at(j-1);
            j--;
        }
        c.at(j) = temp;
    }
}

template<typename Container>
void merge(Container & c, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int lArray[m-l+1];
    int rArray[r-m];
    int k = 0;
    for (int i = l; i < m+1; i++) {
        lArray[k++] = c.at(i);
    }
    k = 0;
    for (int i = m+1; i <= r; i++) {
        rArray[k++] = c.at(i);
    }

    int rIndex = 0;
    int lIndex = 0;

    for (int i = l; i < r - l + 1; i++) {
        if (rIndex == n2) {
            c.at(i) = lArray[lIndex];
            lIndex++;
        } else if (lIndex == n1) {
            c.at(i) = rArray[rIndex];
            rIndex++;
        } else if (rArray[rIndex] > lArray[lIndex]) {
            c.at(i) = lArray[lIndex];
            lIndex++;
        } else {
            c.at(i) = rArray[rIndex];
            rIndex++;
        }
    }
}

template<typename Container>
void mergeSort(Container & A, int l, int r) {
    if (r - l > K) {
        int m = (l + r) / 2;
        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        merge(A, l, m, r);
    } else {
        insertionSort(A, l, r);
    }
}

template<typename Container>
void print_container(const Container & c, const std::string &str) {
    std::cout << str;
    for (size_t i = 0; i < c.size(); i++) {
        std::cout << c.at(i) << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char**argv) {
    if (argc != 2) {
        std::cout << "Error: bad argument(s)" << std::endl;
        return 1;
    }
    std::vector<std::string> str = split(argv[1], ' ');
    std::vector<int> vector;
    std::deque<int> deque;
    for (size_t i = 0; i < str.size(); i++) {
        if (!isDigit(str.at(i))) {
            std::cout << "Error: non digit value found" << std::endl;
            return 1;
        } else {
            vector.push_back(ft_stoi(str.at(i)));
            deque.push_back(ft_stoi(str.at(i)));
        }
    }    
    
    print_container(vector, "before(vector): ");
    clock_t start = clock();
    mergeSort(vector, 0, vector.size() -1);
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    print_container(vector, "after(vector): ");
    std::cout << "Time to process a range of " << vector.size() << " elements with [std::vector]: "
        << elapsed * 1e9 << " us" << std::endl;

    print_container(deque, "before(deque): ");
    start = clock();
    mergeSort(deque, 0, deque.size() -1);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    print_container(deque, "after(deque): ");
    std::cout << "Time to process a range of " << deque.size() << " elements with [std::deque]: "
        << elapsed * 1e9 << " us" << std::endl;

    return 0;
}