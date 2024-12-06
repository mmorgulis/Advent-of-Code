#include <iostream>
#include <fstream>
#include <vector>

void takeInput(std::vector<std::string> &input) {
    std::ifstream ifs;
    std::string line;
    ifs.open("input.txt");
    if(ifs.is_open()) {
        while(std::getline(ifs, line)) {
            input.push_back(line);
            line.clear();
        }
    } else {
        std::cout << "Unable to open the file" << std::endl;
    }
    ifs.close();
}

void printInput(std::vector<std::string> &input) {
    for (auto str : input)
        std::cout << str << std::endl;
}

int main() {
    std::vector<std::string> *input = new std::vector<std::string>;
    takeInput(*input);
    printInput(*input);


    return 0;
}