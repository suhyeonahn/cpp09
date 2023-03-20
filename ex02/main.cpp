#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>  

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

bool isdequeDigit(std::deque<std::string> deque) {
    size_t i = 0;
    while (i < deque.size() -1) {
        if (!isDigit(deque[i]))
            return false;
        i++;
    }
    return true;
}

std::deque<std::string> split(const std::string &s, char delim) {
    std::deque<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        if (item != "")
            result.push_back(item);
    }

    return result;
}

void insertionSort(std::vector<int> & A, int l, int r) {
    for (int i = l; i < r; i++) {
        int temp = A.at(i+1);
        int j = i + 1;
        while (j > l && A.at(j-1) > temp) {
            A.at(j) = A.at(j-1);
            j--;
        }
        A.at(j) = temp;
    }
}

void merge(std::vector<int> & A, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int lArray[m-l+1];
    int rArray[r-m];
    int k = 0;
    for (int i = l; i < m+1; i++) {
        lArray[k++] = A.at(i);
    }
    k = 0;
    for (int i = m+1; i <= r; i++) {
        rArray[k++] = A.at(i);
    }

    int rIndex = 0;
    int lIndex = 0;

    for (int i = l; i < r - l + 1; i++) {
        if (rIndex == n2) {
            A.at(i) = lArray[lIndex];
            lIndex++;
        } else if (lIndex == n1) {
            A.at(i) = rArray[rIndex];
            rIndex++;
        } else if (rArray[rIndex] > lArray[lIndex]) {
            A.at(i) = lArray[lIndex];
            lIndex++;
        } else {
            A.at(i) = rArray[rIndex];
            rIndex++;
        }
    }
}

void mergeSort(std::vector<int> & A, int l, int r) {
    if (r - l > K) {
        int m = (l + r) / 2;
        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        merge(A, l, m, r);
    } else {
        insertionSort(A, l, r);
    }
}


int main(int argc, char**argv) {
    if (argc != 2) {
        std::cout << "Error: bad argument(s)" << std::endl;
        return 1;
    }

    std::deque<std::string> deque = split(argv[1], ' ');

    if (!isdequeDigit(deque)) {
        std::cout << "Error: non digit" << std::endl;
        return 1;
    }
    
    std::vector<int> vector;
    for (size_t i = 0; i < deque.size(); i ++) {
        vector.push_back(ft_stoi(deque[i]));
    }

    mergeSort(vector, 0, vector.size() -1);
    size_t i = 0;
    while (i < vector.size()) {
        std::cout << vector.at(i) << std::endl;
        i++;
    }
    return 0;
}