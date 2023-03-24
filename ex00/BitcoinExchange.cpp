#include "BitcoinExchange.hpp"

const int MAX_YR = 9999;
const int MIN_YR = 1800;

const int MAX_VAL = 1000;
const int MIN_VAL = 0;

bool isLeap(int y) {
    return (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0));
}
  
bool isValidDate(int d, int m, int y) {
    if (y > MAX_YR || y < MIN_YR || m < 1 || m > 12 || d < 1 || d > 31)
        return false;
  
    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);

    return true;
}

bool isDateFormat(std::string str) {
    char y[100], m[100], d[100];
    if (std::sscanf(str.c_str(), "%[^-]-%[^-]-%s", y, m, d) != 3 ||
        !isValidDate(std::atoi(d), std::atoi(m), std::atoi(y))) {
        return false;
    }
    return true;
}

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange & src) {*this = src;}
BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & rhs)
{
    if (this == &rhs)
        return *this;
    this->_data = rhs._data;
    return *this;
}

void BitcoinExchange::readData() {
    std::fstream dataFile;
    dataFile.open("./data.csv", std::ios::in);

    if (!dataFile.is_open())
        throw NoFileException();
        
    std::string line;
    while (getline(dataFile, line)) {
        std::stringstream ss(line);
		std::string date, rate;

		getline(ss, date, ',');
		getline(ss, rate);
		if (date != "date") 
            _data.insert(std::make_pair(date,std::atof(rate.c_str())));
    }
    dataFile.close();
}

void BitcoinExchange::print(const char* input) {
    readData();
    std::fstream inputFile;

    inputFile.open(input, std::ios::in);
    if (!inputFile.is_open())
        throw NoFileException();
    
    if (inputFile.is_open()) {
        std::string line;

        while (getline(inputFile, line)) {
            std::stringstream ss(line);
            std::string date, value;

            getline(ss, date, '|');
            getline(ss, value);

            float val = std::atof(value.c_str());

            if (date.empty() || value.empty())
                std::cout << "Error: bad syntax => " << line << std::endl;
			else if (val > MAX_VAL || val < MIN_VAL)
                std::cout << "Error: invalid value => " << line << std::endl;
            else if (!isDateFormat(date))
                std::cout << "Error: invalid date => " << line << std::endl;
            else {
                std::cout << date << " => " << value << " = ";
                if ((--_data.end())->first < date) {
                    std::cout << val * (--_data.end())->second << std::endl;
                }
                else {
                    std::map<std::string,float>::iterator it = _data.find(date);
                    if (_data.find(date) != _data.end())
                        std::cout << val * (*it).second << std::endl;
                    else
                        std::cout << val * (--_data.lower_bound(date))->second << std::endl;
                }
            }
		}
        inputFile.close();
    }
}

const char *BitcoinExchange::NoFileException::what() const throw() {
	return "Can't open the file.";
}