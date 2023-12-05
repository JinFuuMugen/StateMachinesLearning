#include "PreCompTable.hpp"

std::vector<SCouple> PreCompTable::getPairs() const
{
    return this->comp_pairs;
}

void PreCompTable::addPair(SCouple pair)
{
    this->comp_pairs.push_back(pair);
    return;
}

PreCompTable::PreCompTable(const std::vector<std::vector<std::string>> &f_table, const std::vector<std::vector<std::string>> &g_table)
{
    for (int i = 0; i < f_table.at(0).size(); i++)
    {
        for (int j = 0; j < f_table.at(0).size(); j++)
        {
            if (i != j)
            {
                std::vector<std::pair<int, int>> temp;
                bool flag = false;
                for (int k = 0; k < f_table.size(); k++)
                {
                    if (f_table.at(k).at(i) != "-" && f_table.at(k).at(j) != "-")
                    {   
                        if (g_table.at(k).at(i) != g_table.at(k).at(j) && g_table.at(k).at(i) != "-" && g_table.at(k).at(j) != "-"){
                            flag = true;
                        }
                        
                        if (g_table.at(k).at(i) == g_table.at(k).at(j) || g_table.at(k).at(i) == "-" || g_table.at(k).at(j) == "-")
                        {
                            int next_state_left = std::stoi(f_table.at(k).at(i));
                            int next_state_right = std::stoi(f_table.at(k).at(j));

                            if (next_state_left != next_state_right)
                            {
                                std::pair<int, int> tmp_pair = std::make_pair(std::min(next_state_left, next_state_right), std::max(next_state_left, next_state_right));

                                auto it = std::find_if(temp.begin(), temp.end(),
                                                       [&tmp_pair](auto &element)
                                                       {
                                                           return element == tmp_pair;
                                                       });

                                if (it == temp.end())
                                {
                                    temp.push_back(tmp_pair);
                                }
                            }
                        }
                    }
                }

                if (flag){
                    temp.push_back(std::make_pair(-2, -2));
                }
                SCouple couple = SCouple(std::min(i, j), std::max(i, j), temp);

                auto jt = std::find_if(this->comp_pairs.begin(), this->comp_pairs.end(),
                                       [&couple](auto &element)
                                       {
                                           return element == couple;
                                       });

                if (jt == this->comp_pairs.end())
                {
                    this->comp_pairs.push_back(couple);
                }
            }
        }
    }
}

void PreCompTable::setPair(int idx, std::vector<std::pair<int, int>> newPairs){
    this->comp_pairs[idx].setCouplesStatesTransact(newPairs);
}

