#include <vector>
#include <iostream>
class SCouple{
    private:
        int first_state;
        int second_state;
        std::vector<std::pair<int, int>> couple_states_transact;
    public:
        ~SCouple();
        SCouple(int, int, std::vector<std::pair<int, int>>);
        bool operator==(SCouple);
        std::pair<int, int> getCouple() const;
        std::vector<std::pair<int, int>> getCoupleTrans() const;
        void setCouplesStatesTransact(std::vector<std::pair<int, int>>);
};