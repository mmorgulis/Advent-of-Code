#include <iostream>
#include <fstream>
#include <sstream>
#include "main.h"

bool verifyCondition(std::vector<int> &numeri)
{
    bool isDecreasing = numeri[0] >= numeri[1];
    return (checkSequence(numeri, isDecreasing));
}

bool checkSequence(const std::vector<int>& numeri, bool isDecreasing) {
    for (size_t i = 0; i < numeri.size() - 1; ++i) {
        if (isDecreasing) {
            if (numeri[i] <= numeri[i + 1] || abs(numeri[i] - numeri[i + 1]) > 3)
                return false;
        } else {
            if (numeri[i] >= numeri[i + 1] || abs(numeri[i] - numeri[i + 1]) > 3)
                return false;
        }
    }
    return true;
}

bool verifyConditionTol(std::vector<int> &numeri) {
    if (verifyCondition(numeri)) {
        return true;
    }

    // Testa togliendo un elemento alla volta
    for (size_t i = 0; i < numeri.size(); ++i) {
        std::vector<int> temp = numeri; 
        temp.erase(temp.begin() + i);

        if (temp.size() >= 2) {
            bool isDecreasing = temp[0] >= temp[1];
            if (checkSequence(temp, isDecreasing)) {
                return true;
            }
        }
    }

    return false;
}



int main()
{
    long numSafeReport = 0;
    long numSafeTolerated = 0;
    std::ifstream myFile;
    std::string str;
    std::vector<int> *numeri = new std::vector<int>;
    int temp;

    myFile.open("input.txt");
    if (myFile.is_open())
    {
        while (std::getline(myFile, str))
        {
            std::stringstream istr(str);
            while (istr >> temp)
            {
                numeri->push_back(temp);
            }
            if (verifyCondition(*numeri))
                ++numSafeReport;
            if (verifyConditionTol(*numeri)) 
                ++numSafeTolerated;

            str.clear();
            numeri->clear();
        }
    }
    else
    {
        std::cout << "Unable to open the file";
    }

    std::cout << "Il numero di report safe è: " << numSafeReport << std::endl;
    std::cout << "Il numero di report safe con la tolleranza è: " 
                << numSafeTolerated << std::endl;

    delete numeri;

    return 0;
}
