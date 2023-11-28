#include "Compute.hpp"


std::vector<std::string> Compute::GetSDNF(){
    return this->SDNF;
}

std::vector<std::string> Compute::CalculateTriggerEquation(Table table, int triggerIdx, std::map<std::string, std::string> codeMap){

    int colNum = table.GetStatesNumber();
    int rowNum = table.GetInputsNumber();
    std::vector<std::string> equation;

    for (int i = 0; i < rowNum; i++){
        for (int j = 0; j < colNum; j++){
            std::string currentValue = table.value(i, j);

            if (currentValue == "-"){
                continue;
            }else if (currentValue[triggerIdx] == '1'){
                std::string encodedState = codeMap[std::to_string(j + 1)];
                std::string temp = std::bitset<3>(i).to_string() + encodedState;
                equation.push_back(temp);
            }
        }
    }
    return equation;
}

std::vector<std::string> Compute::CalculateOutputEquation(Table table, int outputIdx, std::map<std::string, std::string> outputsStates, std::map<std::string, std::string> codeMap){

    int colNum = table.GetStatesNumber();
    std::vector<std::string> equation;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < colNum; j++){
            if (outputsStates[std::to_string(j)][outputIdx] == '1'){
                std::string encodedState = codeMap[std::to_string(j + 1)];
                equation.push_back(encodedState);
            }
        }
    }
    return equation;
}