#include <iostream>
#include <fstream>
#include <string>
#include<algorithm>
#include <set>

const int MAX_YR = 9999;
const int MIN_YR = 1800;
  
bool isLeap(int y)
{
    return (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0));
}
  
bool isValidDate(int d, int m, int y)
{
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

int main() {
    std::fstream newFile;

    newFile.open("input.txt", std::ios::in);
    
    if (newFile.is_open()) {

        std::set<std::pair <std::string,std::string> > set;
        std::string line;

        while (getline(newFile, line)) { 
            std::string editedLine(line);
            editedLine.erase(remove(editedLine.begin(), editedLine.end(), ' '), editedLine.end());
            std::size_t index = editedLine.find("|");
            if (index == std::string::npos) {
                std::cout << "Error: bad input => " << line << std::endl;
            }
            else {
                std::pair<std::string,std::string> pair(editedLine.substr(0,index), editedLine.substr(index + 1));
                set.insert(pair);
            }
        }
        newFile.close();

        for (std::set<std::pair <std::string,std::string> >::iterator it=set.begin(); it!=set.end(); ++it) {
            std::cout << "?" << it->first << "/"  << it->second << "?"<< std::endl;
        }

    }
}
