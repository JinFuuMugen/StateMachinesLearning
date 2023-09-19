#include <Impl.hpp>
#include <vector>
#include <string>

class DNF
{
private:
    std::vector<Impl> Data;

    static bool checkPws(std::vector<Impl>);

public:
    DNF(std::string);               //Constr from string line
    ~DNF();

    void Minimize();                //Method which minimizes DNF in field Data using Quine - McCluskey method
    void Print(std::ostream &);
    Impl& GetImpl(int);
};

