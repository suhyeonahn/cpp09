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

const int N = 5;

template<typename Container>
PmergeMe<Container>::PmergeMe() : _input(""){}
template<typename Container>
PmergeMe<Container>::PmergeMe( std::string input ) : _input(input){}
template<typename Container>
PmergeMe<Container>::PmergeMe( const PmergeMe & src ) {*this = src;}
template<typename Container>
PmergeMe<Container>::~PmergeMe() {}
template<typename Container>
PmergeMe<Container> & PmergeMe<Container>::operator=(PmergeMe const & rhs)
{
    if (this == &rhs)
        return *this;
    this->_input = rhs._input;
    this->_c = rhs._c;
    return *this;
}

template<typename Container>
void PmergeMe<Container>::insertionSort(int l, int r) {
    for (int i = l; i < r; i++) {
        int temp = _c.at(i+1);
        int j = i + 1;
        while (j > l && _c.at(j-1) > temp) {
            _c.at(j) = _c.at(j-1);
            j--;
        }
        _c.at(j) = temp;
    }
}

template<typename Container>
void PmergeMe<Container>::merge(int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int lArray[m-l+1];
    int rArray[r-m];
    int k = 0;
    for (int i = l; i < m+1; i++) {
        lArray[k++] = _c.at(i);
    }
    k = 0;
    for (int i = m+1; i <= r; i++) {
        rArray[k++] = _c.at(i);
    }

    int rIndex = 0;
    int lIndex = 0;

    for (int i = l; i < r - l + 1; i++) {
        if (rIndex == n2) {
            _c.at(i) = lArray[lIndex];
            lIndex++;
        } else if (lIndex == n1) {
            _c.at(i) = rArray[rIndex];
            rIndex++;
        } else if (rArray[rIndex] > lArray[lIndex]) {
            _c.at(i) = lArray[lIndex];
            lIndex++;
        } else {
            _c.at(i) = rArray[rIndex];
            rIndex++;
        }
    }
}

template<typename Container>
void PmergeMe<Container>::mergeSort(int l, int r) {
    if (r - l > N) {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    } else {
        insertionSort(l, r);
    }
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
void PmergeMe<Container>::parse() {
    std::vector<std::string> str = split(_input, ' ');
    for (size_t i = 0; i < str.size(); i++) {
        if (!isNumber(str.at(i))) {
            throw BadDigitException();
        }
        _c.push_back(std::atoi(str.at(i).c_str()));
    } 
}

template<typename Container>
Container PmergeMe<Container>::getContainer() const {
    return _c;
}
template<typename Container>
const char *PmergeMe<Container>::BadDigitException::what() const throw() {
	return "Not a valid digit.";
}
template<typename Container>
const char *PmergeMe<Container>::EmptyContainerException::what() const throw() {
	return "Container is empty.";
}