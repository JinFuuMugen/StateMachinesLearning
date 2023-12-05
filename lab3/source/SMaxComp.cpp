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
                                             return true; // Remove this couple
                                         }
                                     }
                                     return false; // Keep this couple
                                 }),
                  couples.end());

    printf("Size new: %d\n", couples.size());
}