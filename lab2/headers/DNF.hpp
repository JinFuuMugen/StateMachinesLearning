#include "Impl.hpp"
#include <vector>
#include <cmath>
#include <iostream>
#include <bitset>
#include <algorithm>
#include <string>

class DNF
{
private:
    std::vector<Impl> Data;
    std::vector<int> SDNFnums;                  //nums of given sdnf
    int varsAmount;                             //amount of variables

    void TDNFtoMDNF();

public:
    explicit DNF(std::string);               //Constr from string line
    ~DNF();

    void Minimize();                //Method which minimizes DNF in field Data using Quine - McCluskey method
    void Print(std::ostream &);
    std::vector<Impl> GetData();
};

