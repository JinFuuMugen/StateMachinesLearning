#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


#include "SCouple.hpp"

class CompTable{
    public:
        virtual std::vector<SCouple> getPairs() const = 0;
        virtual void addPair(SCouple) = 0;
    
};