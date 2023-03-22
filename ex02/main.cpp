#include <iostream>
#include <sstream>
#include <string>
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

void insertionSortVector(std::vector<int> & A, int l, int r) {
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

void mergeVector(std::vector<int> & A, int l, int m, int r) {
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

void mergeSortVector(std::vector<int> & A, int l, int r) {
    if (r - l > K) {
        int m = (l + r) / 2;
        mergeSortVector(A, l, m);
        mergeSortVector(A, m + 1, r);
        mergeVector(A, l, m, r);
    } else {
        insertionSortVector(A, l, r);
    }
}

void insertionSortDeque(std::deque<int> & A, int l, int r) {
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

void mergeDeque(std::deque<int> & A, int l, int m, int r) {
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

void mergeSortDeque(std::deque<int> & A, int l, int r) {
    if (r - l > K) {
        int m = (l + r) / 2;
        mergeSortDeque(A, l, m);
        mergeSortDeque(A, m + 1, r);
        mergeDeque(A, l, m, r);
    } else {
        insertionSortDeque(A, l, r);
    }
}


int main(int argc, char**argv) {
    if (argc != 2) {
        std::cout << "Error: bad argument(s)" << std::endl;
        return 1;
    }
    std::vector<std::string> strVector = split(argv[1], ' ');
    std::vector<int> vector;
    std::deque<int> deque;
    for (size_t i = 0; i < strVector.size(); i ++) {
        std::string str = strVector.at(i);
        if (!isDigit(str)) {
            std::cout << "Error: non digit value found" << std::endl;
            return 1;
        } else {
            vector.push_back(ft_stoi(str));
            deque.push_back(ft_stoi(str));
        }
    }

    mergeSortVector(vector, 0, vector.size() -1);
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout << vector.at(i) << std::endl;
    }

    mergeSortDeque(deque, 0, deque.size() -1);
    for (size_t i = 0; i < deque.size(); i++) {
        std::cout << vector.at(i) << std::endl;
    }
    return 0;
}