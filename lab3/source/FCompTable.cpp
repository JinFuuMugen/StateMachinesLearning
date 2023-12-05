#include "FCompTable.hpp"

FCompTable::FCompTable(PreCompTable pre_comp_table)
{

    std::vector<SCouple> current(pre_comp_table.getPairs());

    std::vector<std::pair<int, int>> incompatible;

    bool flag;

    do
    {
        flag = false;

        for (int i = 0; i < current.size(); i++)
        {
            SCouple couple = current.at(i);
            if (!couple.getCoupleTrans().empty())
            {
                auto value = couple.getCoupleTrans().at(0);
                if (value.first < 0)
                {
                    incompatible.push_back(couple.getCouple());
                }
            }
        }

        for (int i = 0; i < current.size(); i++)
        {
            SCouple couple = current.at(i);
            if (!couple.getCoupleTrans().empty())
            {
                for (auto sc : couple.getCoupleTrans())
                {
                    for (auto p : incompatible)
                    {
                        if (sc.first == p.first && sc.second == p.second)
                        {
                            incompatible.push_back(couple.getCouple());
                            current.at(i).setCouplesStatesTransact({std::make_pair(-2, -2)});
                            flag = true;
                        }
                    }
                }
            }
        }

        this->comp_pairs = current;

    } while (flag);
};

std::vector<SCouple> FCompTable::getPairs() const
{
    return this->comp_pairs;
}

void FCompTable::addPair(SCouple pair)
{
    this->comp_pairs.push_back(pair);
}