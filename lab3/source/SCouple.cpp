#include "SCouple.hpp"

SCouple::~SCouple() = default;
SCouple::SCouple(int first, int second, std::vector<std::pair<int, int>> couple_states_transact)
{
    this->first_state = first;
    this->second_state = second;
    this->couple_states_transact = couple_states_transact;
    return;
}

bool SCouple::operator==(SCouple scoup)
{
    return std::max(this->first_state, this->second_state) == std::max(scoup.first_state, scoup.second_state) && std::min(this->first_state, this->second_state) == std::min(scoup.first_state, scoup.second_state);
}

std::pair<int, int> SCouple::getCouple() const
{
  return std::make_pair(this->first_state, this->second_state);
}

std::vector<std::pair<int, int>> SCouple::getCoupleTrans() const{
    return this->couple_states_transact;
}

void SCouple::setCouplesStatesTransact(std::vector<std::pair<int, int>> newCouplesTransact){
    this->couple_states_transact = newCouplesTransact;
    return;
}
