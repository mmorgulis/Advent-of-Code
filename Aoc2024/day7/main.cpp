#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <cmath>

// Legge il file e riempie il vettore input
void getInput(std::vector<std::vector<long long>> &input)
{
    std::ifstream ifs("input.txt");
    assert(ifs.is_open());

    std::string line;
    while (std::getline(ifs, line))
    {
        std::vector<long long> row;
        size_t pos = 0;

        while ((pos = line.find_first_of(": ")) != std::string::npos)
        {
            if (!line.substr(0, pos).empty())
            {
                row.push_back(std::stoll(line.substr(0, pos)));
            }
            line.erase(0, pos + 1);
        }
        if (!line.empty())
        {
            row.push_back(std::stoll(line));
        }

        input.push_back(row);
    }
    ifs.close();
}

// Genera tutte le combinazioni di operazioni per una data lunghezza
void generateOperations(int size, std::vector<std::vector<bool>> &operations)
{
    int numCombinations = 1 << size; // 2^size combinazioni
    for (int i = 0; i < numCombinations; ++i)
    {
        std::vector<bool> op;
        for (int j = 0; j < size; ++j)
        {
            op.push_back(i & (1 << j));
        }
        operations.push_back(op);
    }
}

// Applica una combinazione di operazioni al vettore
long applyOperations(const std::vector<long long> &vettore, const std::vector<bool> &ops)
{
    long result = vettore[1];
    for (size_t i = 0; i < ops.size(); ++i)
    {
        if (ops[i])
        {
            result += vettore[i + 2];
        }
        else
        {
            result *= vettore[i + 2];
        }
    }
    return result;
}

// Verifica le operazioni e calcola il totale
long verOperation(const std::vector<std::vector<long long>> &input)
{
    long totale = 0;

    for (const auto &vect : input)
    {
        int numOps = vect.size() - 2;
        std::vector<std::vector<bool>> operations;
        generateOperations(numOps, operations);

        for (const auto &ops : operations)
        {
            if (applyOperations(vect, ops) == vect[0])
            {
                totale += vect[0];
                break; // Fermati appena trovi una soluzione valida
            }
        }
    }
    return totale;
}

int main()
{
    std::vector<std::vector<long long>> input;
    getInput(input);

    long long tot = verOperation(input);
    std::cout << tot << std::endl;

    return 0;
}