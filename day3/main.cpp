#include <iostream>
#include "main.h"
#include <fstream>
#include <regex>


void inputToString(std::string &str) {
    std::ifstream fileInput;
    std::string temp;
    fileInput.open("input.txt");
    if (fileInput.is_open()) {
        while(std::getline(fileInput, temp)) {
            str.append(temp);
        }
    } else {
        std::cerr << "Unable to open the file" << std::endl;
    }

}

long calculateRegex(std::string &str) {
    long counter = 0;
    std::regex pattern("mul\\((\\d+),(\\d+)\\)");
    std::smatch m;
    std::string temp(str);

    while (std::regex_search (temp, m, pattern)) {
        // Estraggo solo i due numeri dai gruppi di cattura
        int num1 = std::stoi(m[1].str());  // Primo numero (m[1])
        int num2 = std::stoi(m[2].str());  // Secondo numero (m[2])
        // std::cout << num1 << " " << num2 << std::endl;
        counter += (num1*num2);
        temp = m.suffix().str();
    }
    return counter;
}

long calculateRegexDoDont(std::string &str) {
    long counterDo = 0;
    bool calcola = 1; //all'inzio è true
    std::regex pattern("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)"); 
    std::smatch m;
    std::string temp(str);

    while (std::regex_search (temp, m, pattern)) {
        if (m.str() == "don't()") {
            calcola = 0;  // Disabilita il calcolo se trovi "don't()"
        } else if (m.str() == "do()") {
            calcola = 1;  // Abilita il calcolo se trovi "do()"
        } else if (m[1].matched && m[2].matched) {  // Se trovo mul(x,y) trovo anche i due gruppi
            int num1 = std::stoi(m[1].str());
            int num2 = std::stoi(m[2].str());
            counterDo += (num1 * num2 * calcola);  // Somma se calcola è vero
        }
        temp = m.suffix().str();
    }
    return counterDo;
}

int main() {
    std::string *input = new std::string;
    inputToString(*input);
    
    long total = calculateRegex(*input);
    std::cout << total << std::endl;

    long totalDo = calculateRegexDoDont(*input);
    std::cout << totalDo << std::endl;

    delete input;
    return 0;
}