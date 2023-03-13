#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<algorithm>
#include <set>
#include <vector>

const int MAX_YR = 9999;
const int MIN_YR = 1800;
  
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
  if (iss.fail()) {
    std::cerr << "ERROR!\n";
    return 1;
  }
  std::cout << num << "\n";
  return 0;
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
int main() {
    std::fstream newFile;

    newFile.open("input.txt", std::ios::in);
    
    if (newFile.is_open()) {

        //std::set<std::pair <std::string,std::string> > set;
        std::string line;

        while (getline(newFile, line)) { 
            std::string editedLine(line);
            editedLine.erase(remove(editedLine.begin(), editedLine.end(), ' '), editedLine.end());
            std::size_t index = editedLine.find("|");
            if (index == std::string::npos) {
                std::cerr << "Error: bad input => " << line << std::endl;
            }
            else {
                std::vector<std::string> date = split(editedLine.substr(0,index), '-');
                if (date.size() != 3) {
                    std::cerr << "Error: bad input(date) => " << line << std::endl;
                    return ;
                }
                for (std::vector<std::string>::iterator it = date.begin() ; it != date.end(); ++it) {
                    if (!isDigit(*it))
                        return ;
                }
                if (!isValidDate(ft_itos(date[0]), ft_itos(date[1]), ft_itos(date[1]))) {
                    std::cerr << "Error: bad input(date) => " << line << std::endl;
                    return ;
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
}
