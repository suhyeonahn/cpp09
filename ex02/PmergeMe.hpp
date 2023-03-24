#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <deque>
#include <vector>
#include <exception>

template<typename Container>
class PmergeMe {

    public:
        PmergeMe();
	    PmergeMe( std::string input );
	    PmergeMe( PmergeMe const & src );
        ~PmergeMe();
        PmergeMe & operator=( PmergeMe const & rhs );

        class BadDigitException : public std::exception {
			public:
				virtual const char *	what()	const throw();
		};
        class EmptyContainerException : public std::exception {
			public:
				virtual const char *	what()	const throw();
		};

        void parse();
        void print( const std::string &str );
        void mergeSort( int l, int r );
        Container  getContainer() const;
        
    private:
        std::string _input;
        Container _c;
        
        void merge( int l, int m, int r );
        void insertionSort( int l, int r );
        
};

bool isNumber(const std::string &s);
std::vector<std::string> split(const std::string &s, char delim);
