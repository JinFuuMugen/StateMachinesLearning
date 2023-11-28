#include "CheckUtils.hpp"


CheckUtils::CheckUtils() {}

void CheckUtils::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open the file.");
    }

    std::string line;

    while (std::getline(file, line)) {
        char type;
        std::istringstream iss(line);

        iss >> type;

        switch (type) {
            case 'X': {
                int value;
                char comma;
                while (iss >> value >> comma) {
                    x_given.push_back(value);
                }
                break;
            }
            case 'S': {
                int value;
                char comma;
                while (iss >> value >> comma) {
                    s_given.push_back(value);
                }
                break;
            }
            case 'Y': {
                std::string value;
                char comma;
                while (iss >> value >> comma) {
                    y_given.push_back(value);
                }
                break;
            }
            default:
                throw std::runtime_error("Invalid line format.");
        }
    }

    file.close();
}

void CheckUtils::writeToFile(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open the file for writing.");
    }

    file << "X ";
    for (int value : x_given) {
        file << value << ",";
    }
    file.seekp(-1, std::ios_base::end);
    file << ";" << std::endl;

    file << "S ";
    for (int value : s_given) {
        file << value << ",";
    }
    file.seekp(-1, std::ios_base::end);
    file << ";" << std::endl;

    file << "Y ";
    for (const std::string& value : y_given) {
        file << value << ",";
    }
    file.seekp(-1, std::ios_base::end);
    file << ";" << std::endl;

    file.close();
}

const std::vector<int>& CheckUtils::getXGiven() const {
    return x_given;
}

const std::vector<int>& CheckUtils::getSGiven() const {
    return s_given;
}

const std::vector<std::string>& CheckUtils::getYGiven() const {
    return y_given;
}
