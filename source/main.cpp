#include <DNF.hpp>
#include <string>
#include <iostream>
#include <fstream>


int main(int argc, char *argv[]){
    if (argc != 2){
        std::cerr << "Please provide filepath (as cmd flag)" << std::endl;
        return 1;
    }

    std::string fileLocation = argv[1];

    std::ifstream inputFile(fileLocation);

    if (!inputFile.is_open()){
        std::cerr << "Cannot open file: " << fileLocation << std::endl;
        return 1;
    }

    std::string inputLine;

    std::getline(inputFile, inputLine);

    inputFile.close();

    DNF dnfObject = DNF(inputLine);
    

    dnfObject.Minimize();

    dnfObject.Print(std::cout);

    return 0;
}