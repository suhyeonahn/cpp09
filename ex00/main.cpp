#include <iostream>
#include <fstream>
#include <string>
#include<algorithm>
#include <set>

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
