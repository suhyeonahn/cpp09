#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

class BitcoinExchange {

    public:
        BitcoinExchange();
	    BitcoinExchange( BitcoinExchange const & src );
        ~BitcoinExchange();
        BitcoinExchange &   operator=( BitcoinExchange const & rhs );

        class NoFileException : public std::exception {
			public:
				virtual const char *	what()	const throw();
		};
        
        void readData();
        void print( const char* input );

    private:
        std::map<std::string, double> _data;
        
};

bool isLeap(int y);
bool isValidDate(int d, int m, int y);
bool isDateFormat(std::string str);
bool isSpace(const std::string &str);
bool isSpaceValue(const std::string &str);