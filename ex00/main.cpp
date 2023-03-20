#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

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

bool isDigit(std::string str) {
  std::istringstream iss(str);
  int num;

  iss >> num;
  if (iss.fail())
    return false;
  return true;
}

float ft_stof(std::string str) {
  std::istringstream iss(str);
  float num;

  iss >> num;
  return (num);
}

// MAKE this function as template to use string and int
std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

std::map<std::string, float> readData() {
    std::map<std::string, float> data;
    std::fstream dataFile;

    dataFile.open("./data.csv", std::ios::in);
    if (dataFile.is_open()) {
        std::string line;

        while (getline(dataFile, line)) { 
            std::size_t index = line.find(",");
            if (line == "date,exchange_rate")
                ;
            else if (index == std::string::npos || index == 0) {
                std::cout << "Error: data: bad syntax (`,` is missing) => " << line << std::endl;
            }
            else {
                std::string first = line.substr(0, index);
                std::vector<std::string> date = split(first, '-');
                if (date.size() != 3) {
                    std::cout << "Error: data: => bad syntax (date) => " << line << std::endl;
                }
                else {
                    bool isDate = true;
                    std::string second = line.substr(index + 1);
                    for (std::vector<std::string>::iterator it = date.begin() ; it != date.end(); ++it) {
                        if (!isDigit(*it))
                            isDate = false;
                    }
                    if (!isDate) {
                         std::cout << "Error: data: date is not digit => " << line << std::endl;
                    }
                    else if (!isValidDate(ft_stof(date[2]), ft_stof(date[1]), ft_stof(date[0]))) {
                        std::cout << "Error: data: invalid date => " << line << std::endl;
                    }
                    else {
                        data.insert(std::make_pair(first, ft_stof(second)));
                        //std::cout << first << " => " << second << std::endl;
                    }
                }
            }
        }
        dataFile.close();
    }
    else {
        std::cout << "Error: data: can't open file" << std::endl;
    }
    return data;
}

int main(int argc, char**argv) {
    if (argc != 2) {
        std::cout << "Error: bad argument(s)" << std::endl;
        return 1;
    }

    std::map<std::string, float> data = readData();
    std::fstream newFile;

    newFile.open(argv[1], std::ios::in);
    
    if (newFile.is_open()) {
        std::string line;

        while (getline(newFile, line)) {
            std::string editedLine(line);
            editedLine.erase(remove(editedLine.begin(), editedLine.end(), ' '), editedLine.end());
            std::size_t index = editedLine.find("|");
            if (line == "date | value")
                ;
            else if (index == std::string::npos || index == 0) {
                std::cout << "Error: bad syntax (`|` is missing) => " << line << std::endl;
            }
            else {
                std::string first = editedLine.substr(0, index);
                std::vector<std::string> date = split(first, '-');
                if (date.size() != 3) {
                    std::cout << "Error:  => bad syntax (date) => " << line << std::endl;
                }
                else {
                    bool isDate = true;
                    std::string second = editedLine.substr(index + 1);
                    for (std::vector<std::string>::iterator it = date.begin() ; it != date.end(); ++it) {
                        if (!isDigit(*it))
                            isDate = false;
                    }
                    if (!isDate) {
                         std::cout << "Error: date is not digit => " << line << std::endl;
                    }
                    else if (!isValidDate(ft_stof(date[2]), ft_stof(date[1]), ft_stof(date[0]))) {
                        std::cout << "Error: invalid date => " << line << std::endl;
                    }
                    else if (!isDigit(second) || ft_stof(second) > MAX_VAL || ft_stof(second) < MIN_VAL) {
                        std::cout << "Error: invalid value => " << line << std::endl;
                    }
                    else {
                        std::cout << first << " => " << second << " = ";
                        if ((--data.end())->first < first) {
                            std::cout << ft_stof(second) * (--data.end())->second << std::endl;
                        }
                        else {
                            std::map<std::string,float>::iterator it = data.find(first);
                            if (data.find(first) != data.end())
                                std::cout << ft_stof(second) * (*it).second << std::endl;
                            else
                                std::cout << ft_stof(second) * (--data.lower_bound(first))->second << std::endl;
                        }
                    }
                }
            }
        }
        newFile.close();
    }
    else {
        std::cout << "Error: can't open file" << std::endl;
    }
    return 0;
}