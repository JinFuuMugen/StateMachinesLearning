#include "PreCompTable.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

const std::string f_table_path = "static/f_table.txt";
const std::string g_table_path = "static/g_table.txt";

void fillTableFromFile(const std::string &file_path, std::vector<std::vector<std::string>> &table)
{
    std::ifstream file(file_path);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::vector<std::string> row;
            std::string token;
            while (iss >> token)
            {
                if (token == "-")
                {
                    row.push_back(token);
                }
                else
                {
                    row.push_back(std::to_string(std::stoi(token) - 1));
                }
            }
            table.push_back(row);
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        std::exit(1);
    }
}

int main()
{

    std::vector<std::vector<std::string>> f_table;
    std::vector<std::vector<std::string>> g_table;

    // Заполнение f_table
    fillTableFromFile(f_table_path, f_table);

    // Заполнение g_table
    fillTableFromFile(g_table_path, g_table);

    // Ваши действия с векторами f_table и g_table здесь

    PreCompTable pre_comp_table = PreCompTable(f_table, g_table);

    for (auto &couple : pre_comp_table.getPairs()) {
        printf("%d, %d at ", couple.getCouple().first + 1, couple.getCouple().second + 1);
        for (auto v : couple.getCoupleTrans()){
            printf(" %d%d, ",v.first + 1, v.second + 1);
        }
        printf("\n");
    }

    return 0;
}