#include <vector>
#include <string>
#include <bitset>
#include "Table.hpp"
#ifndef COMPUTE_HPP
#define COMPUTE_HPP

class Compute {
    private:
        std::vector<std::string> SDNF;
    public:
        std::vector<std::string> CalculateTriggerEquation(Table, int,  std::map<std::string, std::string>);
        std::vector<std::string> GetSDNF();
        std::vector<std::string> CalculateOutputEquation(Table, int, std::map<std::string, std::string>,  std::map<std::string, std::string>);
};
#endif