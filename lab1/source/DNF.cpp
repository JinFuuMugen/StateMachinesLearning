#include <DNF.hpp>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h>

bool compareData(const Impl& i1, const Impl& i2) {                  //lambda sort function
    if (i1.GetNum() < i2.GetNum()) {
        return true;
    } else if (i1.GetNum() == i2.GetNum()) {
        return i1.GetP() < i2.GetP();
    }
    return false;
}

bool allColsHaveOnes(bool **matrix, int rowNum, int colNum){          //checks if all columns have at least single one
    for (int j = 0; j < colNum; j++){
        bool sum = false;
        for (int i = 0; i < rowNum; i++){
            sum += (*(*(matrix + i) + j));
        }
        if (!sum)
            return false;
    }
    return true;
}

bool** dropRow(bool **matrix, int rowNum, int colNum, int rowIdx){                  //function that returns copy of given matrix but one row at rowIdx
    bool** temp = (bool**)malloc(sizeof(bool**) * (rowNum - 1));
    if (rowIdx == 0){
        for (int i = 0; i < rowNum - 1; i++){
            *(temp + i) = (bool*)malloc(sizeof(bool*) * colNum);
            *(temp + i) = *(matrix + i + 1);
        }
    } else if (rowIdx == rowNum - 1){
        for (int i = 0; i < rowNum - 1; i++){
            *(temp + i) = (bool*)malloc(sizeof(bool*) * colNum);
            *(temp + i) = *(matrix + i);
        }
    } else {
        for (int i = 0; i < rowIdx; i++){
            *(temp + i) = (bool*)malloc(sizeof(bool*) * colNum);
            *(temp + i) = *(matrix + i);
        }
        for (int i = rowIdx; i < rowNum; i++){
            *(temp + i) = (bool*)malloc(sizeof(bool*) * colNum);
            *(temp + i) = *(matrix + i + 1);
        }
    }
    return temp;
}

DNF::DNF(std::string stringDNF){                                                //constructor
    int inputLength = stringDNF.length();

    if (((inputLength & (inputLength - 1))) != 0){                              //checks input (amount of symbols is power of two)
        std::cerr << "Invalid input" << std::endl;
        exit(-1);
    }

    this->varsAmount = std::log2(inputLength);                              //count number of variables

    this->Data.reserve(inputLength);
    
    for(int i = 0; i < inputLength; i++){
        if ((stringDNF.at(i) == '1') || (stringDNF.at(i) == '-')){
            this->Data.emplace_back(i);
            if (stringDNF.at(i) != '-') {
                this->SDNFnums.push_back(i);
            }
        }
    }
    sort(this->SDNFnums.begin(), this->SDNFnums.end());
}



DNF::~DNF()= default;

void DNF::Minimize(){
    std::vector<Impl> tempData;

    for(;;){

        tempData.clear();

        bool wasPatched = false;  

        for(int i = 0; i < Data.size(); i++){
            for(int j = i; j < Data.size(); j++){
                Impl *leftImpl = &Data.at(i);
                Impl *rightImpl = &Data.at(j);
                Impl patchRes = Impl::Patch(leftImpl, rightImpl);                           //call patch
                if (patchRes.isValid()){
                    this->Data.at(i).setPw();                                           //set pw
                    this->Data.at(j).setPw();                                           //set pw
                    tempData.push_back(patchRes);
                    wasPatched = true;
                } 
            }
        }

        if (!wasPatched){
            break;                                                                          //loop exit point
        }

        for(const Impl& impl : Data){
            if (!impl.GetPw()){                                                            //add impl to temp vector if it was not patched
                tempData.push_back(impl);                                                  //in order to save unpatched impls
            }
        }
        DNF::Data = tempData;
    }

    for (int j = 0; j < Data.size(); j++){
        for (int i = 0; i < Data.size(); i++){
            if ((Data.at(i).GetNum() == Data.at(j).GetNum()) 
                && Data.at(i).GetP() == Data.at(j).GetP()
                && j != i){
                    DNF::Data.erase(Data.begin() + i);                             //delete duplicates for Data vector
                    j = 0;
            }
        }
    }

    sort(Data.begin(), Data.end(), compareData);

    TDNFtoMDNF();                                                                       //calls transformation from TDNF to MDNF
}

void DNF::TDNFtoMDNF() {

    int mintermsAmount = this->SDNFnums.size();                                         //amount of given minterms
    bool **matr = (bool**) malloc(this->Data.size() * sizeof(bool**));            //matrix to find excesses

    for (int i = 0; i < this->Data.size(); i++){
        *(matr + i) = (bool *) malloc(mintermsAmount * sizeof(bool*));
        for (int j = 0; j < mintermsAmount; j++){
            *(*(matr + i) + j) = ((SDNFnums.at(j) & ~this->Data.at(i).GetP()) == this->Data.at(i).GetNum());
        }
    }

    for (int i = 0; i < this->Data.size(); i++){
        bool** temp = dropRow(matr, this->Data.size(), mintermsAmount, i);              //try row drop for every row index

        if (allColsHaveOnes(temp, this->Data.size() - 1, mintermsAmount)){                   //and delete impl from vector if all
            this->Data.erase(this->Data.begin() + i);                                                      //columns still have ones
        }

    }

    for (int i = 0; i < this->Data.size(); i++){
        free(*(matr + i));                                                                                  //memory freeing
    }
    free(matr);

}

void DNF::Print(std::ostream &ost){                                                                                 //impl vector to stream output

    for (const Impl& impl : DNF::Data) {
        std::string line;

        std::string mask = std::bitset<128>(~impl.GetP()).to_string();                                         //category is 128, can be changed
        std::string vars = std::bitset<128>(impl.GetNum()).to_string();                                        //category is 128, can be changed

        mask = mask.substr(mask.length() - this->varsAmount, mask.length());                                //cut only needed part
        vars = vars.substr(vars.length() - this->varsAmount, vars.length());                                //cut only needed part


        for (int i = 0; i < mask.length(); i++){
            if (mask.at(i) == '0'){                                                                             //logic of binaries to symbols transforming
                line += '-';
            } else if (mask.at(i) == '1'){
                line += vars.at(i);
            }
        }

        ost << line << std::endl;
    }
}