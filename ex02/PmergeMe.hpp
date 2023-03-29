#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <exception>
#include <cstdlib>

template<typename Container>
class PmergeMe
{

    public:
        PmergeMe();
        PmergeMe(char** input);
        PmergeMe(const PmergeMe &src);
        ~PmergeMe();
        PmergeMe &operator=(PmergeMe const &rhs);

        void parse();
        void sort();
        void print(const std::string &str);

        Container getContainer() const;
        class BadDigitException : public std::exception {
			public:
				virtual const char *	what()	const throw();
		};
        class EmptyContainerException : public std::exception {
			public:
				virtual const char *	what()	const throw();
		};

    private:
        char ** _input;
        Container _c;
        void insertionSort(int l, int r);
        void merge(int l, int m, int r);
        void mergeSort(int l, int r);

};

bool isNumber(const std::string &s);

#include "PmergeMe.cpp"
#endif
