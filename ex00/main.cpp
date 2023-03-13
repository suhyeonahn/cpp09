#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>

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

int ft_itos(std::string str) {
  std::istringstream iss(str);
  int num;

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

//use unordered_set
int main(int argc, char**argv) {
    if (argc != 2) {
        std::cerr << "Error: bad argument(s)" << std::endl;
        return 1;
    }

    std::fstream newFile;

    newFile.open(argv[1], std::ios::in);
    
    if (newFile.is_open()) {
        //std::set<std::pair <std::string,std::string> > set;
        std::string line;

        while (getline(newFile, line)) { 
            std::string editedLine(line);
            editedLine.erase(remove(editedLine.begin(), editedLine.end(), ' '), editedLine.end());
            std::size_t index = editedLine.find("|");
            if (index == std::string::npos || index == 0) {
                std::cerr << "Error: bad syntax (`|` is missing) => " << line << std::endl;
            }
            else {
                std::string first = editedLine.substr(0, index);
                std::vector<std::string> date = split(first, '-');
                if (date.size() != 3) {
                    std::cerr << "Error:  => bad syntax (date) => " << line << std::endl;
                }
                else {
                    bool isDate = true;
                    std::string second = editedLine.substr(index + 1);
                    for (std::vector<std::string>::iterator it = date.begin() ; it != date.end(); ++it) {
                        if (!isDigit(*it))
                            isDate = false;
                    }
                    if (!isDate) {
                         std::cerr << "Error: date is not digit => " << line << std::endl;
                    }
                    else if (!isValidDate(ft_itos(date[2]), ft_itos(date[1]), ft_itos(date[0]))) {
                        std::cerr << "Error: invalid date => " << line << std::endl;
                    }
                    else if (!isDigit(second) || ft_itos(second) > MAX_VAL || ft_itos(second) < MIN_VAL) {
                        std::cerr << "Error: invalid value => " << line << std::endl;
                    }
                    else {
                        std::cout << first << " => " << second << " = " << ft_itos(second) * 0.3 << std::endl;
                    }
                }
                //std::pair<std::string,std::string> pair(editedLine.substr(0,index), editedLine.substr(index + 1));
                //set.insert(pair);
            }
        }
        newFile.close();

        //for (std::set<std::pair <std::string,std::string> >::iterator it=set.begin(); it!=set.end(); ++it) {
        //    std::cout << "?" << it->first << "/"  << it->second << "?"<< std::endl;
        //}
    }
    else {
        std::cerr << "Error: can't open file" << std::endl;
    }
}
