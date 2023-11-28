#include <map>
#include <fstream>
#include <vector> 
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>

class Table{
    private:
        std::vector<std::vector<std::string>> tableValues;
    public:
        std::string value(int, int);
        void readTable(const std::string&);
        std::map<int, int> countStates();
        void replaceStates(std::map<std::string, std::string>);
        void printTable();
        int GetStatesNumber();
        int GetInputsNumber();
};
