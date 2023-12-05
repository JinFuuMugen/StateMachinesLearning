#include "CompTable.hpp"

class PreCompTable : public CompTable
{

    private:
        std::vector<SCouple> comp_pairs;

        public:
    std::vector<SCouple> getPairs() const override;

    void addPair(SCouple pair) override;

    PreCompTable(const std::vector<std::vector<std::string>> &f_table, const std::vector<std::vector<std::string>> &g_table);
};