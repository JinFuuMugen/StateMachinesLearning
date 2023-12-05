#include "PreCompTable.hpp"

class FCompTable : public CompTable
{
private:
    std::vector<SCouple> comp_pairs;

public:
    FCompTable(PreCompTable);
    std::vector<SCouple> getPairs() const override;
    void addPair(SCouple pair) override;
};