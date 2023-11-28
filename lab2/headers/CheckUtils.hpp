#ifndef CHECKUTILS_HPP
#define CHECKUTILS_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class CheckUtils {
private:
    std::vector<int> x_given;
    std::vector<int> s_given;
    std::vector<std::string> y_given;

public:
    CheckUtils();  
    void readFromFile(const std::string& filename);  
    void writeToFile(const std::string& filename);   

    const std::vector<int>& getXGiven() const;
    const std::vector<int>& getSGiven() const;
    const std::vector<std::string>& getYGiven() const;
};

#endif  
