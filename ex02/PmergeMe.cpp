#include "PmergeMe.hpp"

bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    if (*it == '-' && it+1 != s.end())
        it++;
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
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
PmergeMe<Container>::PmergeMe() {}

template<typename Container>
PmergeMe<Container>::PmergeMe(char **input) : _input(input){}

template<typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe &src) {*this = src;}

template<typename Container>
PmergeMe<Container>::~PmergeMe() {}

template<typename Container>
PmergeMe<Container> &PmergeMe<Container>::operator=(PmergeMe const &rhs)
{
    if (this == &rhs)
        return *this;
    this->_input = rhs._input;
    this->_c = rhs._c;
    return *this;
}

template<typename Container>
void PmergeMe<Container>::parse()
{
    for (size_t i = 0; _input[i]; i++) {
        std::string input = _input[i];
        if (isNumber(input)) {
            _c.push_back(std::atoi(_input[i]));
        } else {
            throw BadDigitException();
        }
    }
}

template<typename Container>
void PmergeMe<Container>::insertionSort(int l, int r) {
    for (int i = l; i < r; i++) {
        int temp = _c.at(i+1);
        int j = i + 1;
        while (j > l && _c.at(j-1) > temp) {
            _c.at(j) = _c.at
            (j-1);
            j--;
        }
        _c.at(j) = temp;
    }
}

template<typename Container>
void PmergeMe<Container>::merge(int l, int m, int r) {
    int len1 = m-l+1, len2 = r-m;
    Container left(len1), right(len2);
    for (int i = 0; i < len1; i++) {
        left[i] = _c.at(l+i);
    }
    for (int i = 0; i < len2; i++) {
        right[i] = _c.at(m+1+i);
    }
    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            _c.at(k) = left[i];
            i++;
        } else {
            _c.at(k) = right[j];
            j++;
        }
        k++;
    }

while (i < len1) {
    _c.at(k) = left[i];
    i++;
    k++;
}

while (j < len2) {
    _c.at(k) = right[j];
    j++;
    k++;
}
}

template<typename Container>
void PmergeMe<Container>::mergeSort(int l, int r) {
    if (l >= r) {
        return;
    }
    if (r-l < 5) {
        insertionSort(l, r);
        return;
    }
    int m = (l+r-1)/2;
    mergeSort(l, m);
    mergeSort(m+1, r);
    merge(l, m, r);
}

template<typename Container>
void PmergeMe<Container>::sort() {
    mergeSort(0, _c.size()-1);
}

template<typename Container>
Container PmergeMe<Container>::getContainer() const {
    return _c;
}

template<typename Container>
void PmergeMe<Container>::print(const std::string &str) {
    if (_c.empty())
        throw EmptyContainerException();
    std::cout << str;
    for (size_t i = 0; i < _c.size(); i++) {
        std::cout << _c.at(i) << " ";
    }
    std::cout << std::endl;
}

template<typename Container>
const char *PmergeMe<Container>::BadDigitException::what() const throw() {
	return "Input contains non-numeric character(s).";
}
template<typename Container>
const char *PmergeMe<Container>::EmptyContainerException::what() const throw() {
	return "Container is empty.";
}