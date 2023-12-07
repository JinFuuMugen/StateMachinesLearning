#include "SMaxComp.hpp"

SMaxComp::SMaxComp(FCompTable f_comp_table, int rowNum, int colNum)
{

    std::vector<SCouple> couples = f_comp_table.getPairs();

    couples.erase(std::remove_if(couples.begin(), couples.end(), [](const SCouple &couple)
                                 {
                                     for (auto v : couple.getCoupleTrans())
                                     {
                                         if (v == std::make_pair(-2, -2))
                                         {
                                             return true;
                                         }
                                     }
                                     return false; }),
                  couples.end());

    std::vector<int> itteration_lm = {rowNum - 1};
    for (int i = rowNum - 1; i > 0; i--){
        bool flag = true;
        for (auto v : couples){
            if (v.getCouple().first == i || v.getCouple().second == i){
                flag = false;
                break;
            }
        }
        std::optional<int> cl;
        if (!flag){
            
        }
    }
}