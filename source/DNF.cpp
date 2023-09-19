#include <DNF.hpp>
#include <cmath>
#include <iostream>
#include <set>

DNF::DNF(std::string stringDNF){
    int inputLength = stringDNF.length();
    //int varsAmount = (int)(std::log2(inputLength));

    Data.reserve(inputLength);
    
    for(int i = 0; i < inputLength; i++){
        if ((stringDNF.at(i) == 49) || (stringDNF.at(i) == 45)){
            Data.push_back(Impl{i});
        }
    }
}

bool DNF::checkPws(std::vector<Impl> implicants){
    for (Impl impl : implicants){
        if (impl.GetPw()){
            return true;
        }
    }
    return false;
}


DNF::~DNF(){}

void DNF::Minimize(){

    std::set<int> Ns;

    for (Impl impl : Data){
        Ns.insert(impl.GetNum());
    }

    std::vector<Impl> tempData;

    for(;;){

        tempData.clear();

        bool wasPatched = false;  

        for(int i = 0; i < Data.size(); i++){
            for(int j = i; j < Data.size(); j++){
                Impl *leftImpl = &Data.at(i);
                Impl *rightImpl = &Data.at(j);
                Impl patchRes = Impl::Patch(leftImpl, rightImpl);
                if (patchRes.isValid()){
                    this->Data.at(i).setPw();
                    this->Data.at(j).setPw();
                    tempData.push_back(patchRes);
                    wasPatched = true;
                } 
            }
        }

        if (!wasPatched){
            break;
        }

        for(Impl impl : Data){
            if (!impl.GetPw()){
                tempData.push_back(impl);
            }
        }

        DNF::Data = tempData;

    }


    for (int j = 0; j < Data.size(); j++){
        for (int i = 0; i < Data.size(); i++){
            if ((Data.at(i).GetNum() == Data.at(j).GetNum()) 
                && Data.at(i).GetP() == Data.at(j).GetP()
                && j != i){
                    DNF::Data.erase(Data.begin() + i);
                    j = 0;
            }
        }
    }

    bool matr[Data.size()][Ns.size()];

    int i, j = 0;

    for (Impl impl : Data){
        for (int n : Ns){
            if (impl.GetNum() & (~impl.GetP()) == n){
                matr[i][j] = 1;
            } else {
                matr[i][j] = 0;
            }
            j++;
        }
        i++;
    }
}

Impl& DNF::GetImpl(int n){
    return DNF::Data.at(n);
}

void DNF::Print(std::ostream &ost){

     for (Impl impl : DNF::Data) {

    }

    
}