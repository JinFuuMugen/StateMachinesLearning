#include "Table.hpp"

    std::string Table::value(int input, int state){
        if (input < tableValues.size()) {
            const std::vector<std::string>& row = tableValues[input];
            if (state < row.size()) {
                return row[state];
            }
        }
        std::exit(-1);
        return "";
    }

    void Table::readTable(const std::string& filename){
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::vector<std::string> row;
                std::string token;
                while (iss >> token) {
                    row.push_back(token);
                }
                tableValues.push_back(row);
            }
            file.close();
        } else {
            std::exit(-1);
        }
    }

    std::map<int, int> Table::countStates() {
        std::map<int, int> intCount;

        for (const std::vector<std::string>& row : tableValues) {
            for (const std::string& token : row) {
                for (char c : token) {
                    if (c != '-') {
                        int number = c - '0';
                        if (intCount.count(number) == 0) {
                            intCount[number] = 1;
                        } else {
                            intCount[number]++;
                        }
                    }
                }
            }
        }

        return intCount;
    }

    void Table::replaceStates(std::map<std::string, std::string> codedStates){
       for (auto& row : tableValues) {
            for (auto& cell : row) {
                auto it = codedStates.find(cell);
                if (it != codedStates.end()) {
                    // Найдено соответствие, заменяем значение
                    cell = it->second;
                }
            }
        }
    }


    void Table::printTable() {
        for (const auto& row : tableValues) {
            for (const auto& cell : row) {
                std::cout << std::setw(4) << cell << ' ';
            }
            std::cout << std::endl;
        }
    }

    int Table::GetStatesNumber(){
        return tableValues.at(0).size();
    }

    int Table::GetInputsNumber(){
        return tableValues.size();
    }
