#include "Compute.hpp"
#include "DNF.hpp"
#include "CheckUtils.hpp"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <bitset>
#include <map>
#include <math.h>
#include <string.h>

std::string const states_path = "states.txt";
std::string const f_table_path = "f_table.txt";

std::vector<std::string> readStates(std::string filepath){
    std::vector<std::string> states;
    std::ifstream file(filepath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                states.push_back(line);
            }
            file.close();
        } else {
            std::exit(-1);
        }
    return states;
}

std::string findKeyByValue(const std::map<std::string, std::string>& myMap, const std::string& value) {
    for (const auto& pair : myMap) {
        if (pair.second == value) {
            return pair.first;
        }
    }
    return "";
}


std::string compareFiles(std::string current) {

    std::string result;

    std::vector<std::ifstream*> files;

    files.push_back(new std::ifstream("Q0.txt"));
    files.push_back(new std::ifstream("Q1.txt"));
    files.push_back(new std::ifstream("Q2.txt"));
    
    

    for (auto f : files) {
        std::string toCheck;
        bool flag = false;

        while (std::getline(*f, toCheck)) {
            for (size_t i = 0; i < current.size() && i < toCheck.size(); i++) {
                if (current[i] != toCheck[i] && toCheck[i] != '-') {
                    flag = false;
                    break; 
                }
                flag = true;
            }
            if (flag) {
                break;
            }
        }

        result += (flag ? "1" : "0");

        (*f).close();
    }   


    return result;
}


std::string checkOutput(std::string state){
    std::string result;

    std::vector<std::ifstream*> files;

    files.push_back(new std::ifstream("O0.txt"));
    files.push_back(new std::ifstream("O1.txt"));
    files.push_back(new std::ifstream("O2.txt"));

    for (auto f : files) {
        std::string toCheck;
        bool flag = false;

        while (std::getline(*f, toCheck)) {
            for (size_t i = 0; i < state.size() && i < toCheck.size(); i++) {
                if (state[i] != toCheck[i] && toCheck[i] != '-') {
                    flag = false;
                    break;
                }
                flag = true;
            }

            if (flag) {
                break;
            }
        }

        result += (flag ? "1" : "0");

        (*f).close();
    }


    return result;
}

int main(int argc, char const *argv[]){

    std::vector<std::string> states = readStates(states_path);          //read input

    Table table;    
    table.readTable(f_table_path);                                      //build table

    std::cout << "Provided f_table: " << std::endl;
    table.printTable();                                                 //print table

    std::map<int, int> intCount = table.countStates();                  //count appearances of each state

    
    std::vector<std::pair<int, int>> sortedNumbers(intCount.begin(), intCount.end());


    std::sort(sortedNumbers.begin(), sortedNumbers.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    });

    int memoryElements = std::log2(sortedNumbers.size());

    std::map<std::string, std::string> codedStates;
    int oneces = 0b111;

    for (int i = 0; i < sortedNumbers.size(); i++){
        codedStates[std::to_string(sortedNumbers.at(i).first)] = std::bitset<3>(oneces).to_string();
        std::cout << "State " << sortedNumbers.at(i).first << " coded into " << std::bitset<3>(oneces) << std::endl;
        oneces -= 0b001;
    }

    std::cout << "Encoded f_table: " << std::endl;
    table.replaceStates(codedStates);
    table.printTable();

    Compute computationObject;


    std::vector<std::vector<Impl>> minimizedObjects;


    for (int j = 0; j < memoryElements; j++){
        std::vector<std::string> triggerSDNF = computationObject.CalculateTriggerEquation(table, j, codedStates);

        std::string strSDNF;

        for (int i = 0b000000; i <= 0b111111; i++){
            bool flag = false;
            for (std::string s : triggerSDNF){
                if (s == std::bitset<6>(i).to_string()){
                    flag = true;
                    break;
                }
            }
            if (flag){
                strSDNF += "1";
            } else {
                strSDNF += "0";
            }
        }

        DNF dnfObject = DNF(strSDNF);
        dnfObject.Minimize();
        std::ofstream outputFile("Q" + std::to_string(j) + ".txt");
        dnfObject.Print(outputFile);
        outputFile.close();

        minimizedObjects.push_back(dnfObject.GetData());

        std::cout << strSDNF << std::endl;
    }


    std::ifstream inputFile("y.txt");

    std::map<std::string, std::string> statesToOutputs;

    std::string key;
    std::string value;

    while (inputFile >> key >> value) {
        statesToOutputs[key] = value;
    }

    inputFile.close();

    Compute outComputeObject;

    std::vector<std::vector<Impl>> outputsMin;

    for (int j = 0; j < 3; j++){

        std::string strSDNF;

        std::vector<std::string> statesOuts = outComputeObject.CalculateOutputEquation(table, j, statesToOutputs, codedStates);

        for (int i = 0b000; i <= 0b111; i++){
            bool flag = false;
            for (std::string s : statesOuts){
                if (s == std::bitset<3>(i).to_string()){
                    flag = true;
                    break;
                }
            }
            if (flag){
                strSDNF += "1";
            } else {
                strSDNF += "0";
            }
        }

        DNF dnfObject = DNF(strSDNF);
        dnfObject.Minimize();
        std::ofstream outputFile("O" + std::to_string(j) + ".txt");
        dnfObject.Print(outputFile);
        outputFile.close();

        minimizedObjects.push_back(dnfObject.GetData());

        std::cout << strSDNF << std::endl;
    }

    CheckUtils checkUtils;

    checkUtils.readFromFile("checkword_input.txt");

    std::vector<std::string> states_checked;
    std::vector<std::string> out_checked;

    states_checked.push_back(codedStates[std::to_string(checkUtils.getSGiven().at(0))]);


    for (int i = 0; i < checkUtils.getXGiven().size(); i++){
        std::string s_current = states_checked.at(i);
        std::string x_current = std::bitset<3>(checkUtils.getXGiven().at(i) - 1).to_string();

        std::string currentStep = x_current + s_current;

        out_checked.push_back(checkOutput(s_current));
        
        states_checked.push_back(compareFiles(currentStep));
        
    }

    for (int i = 0; i < out_checked.size(); i++){

        std::string thisState = findKeyByValue(codedStates, states_checked.at(i));
        std::cout << std::setw(4) <<  "State: " << std::setw(4) << thisState  << std::setw(4) <<  " Out: " << std::setw(4) << statesToOutputs[thisState] << std::endl;
    }
    
    return 0;
}

