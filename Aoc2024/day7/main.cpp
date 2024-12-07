#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <cmath>

void getInput(std::vector<std::vector<long long>> &input)
{
    std::ifstream ifs("input.txt");
    assert(ifs.is_open()); // Assicura che il file sia aperto

    std::string line;
    while (std::getline(ifs, line))
    {
        std::vector<long long> row;
        size_t pos = 0;

        // Processa i numeri separati da ':'
        while ((pos = line.find(':')) != std::string::npos)
        {
            if (!line.substr(0, pos).empty())
            { // Evita stringhe vuote
                row.push_back(atol(line.substr(0, pos).c_str()));
            }
            line.erase(0, pos + 1); // Rimuovi fino al separatore incluso
        }

        // Processa i numeri separati da spazi
        while ((pos = line.find(' ')) != std::string::npos)
        {
            if (!line.substr(0, pos).empty())
            { // Evita stringhe vuote
                row.push_back(atol(line.substr(0, pos).c_str()));
            }
            line.erase(0, pos + 1); // Rimuovi fino al separatore incluso
        }

        // Aggiungi l'ultimo numero della riga, se esiste
        if (!line.empty())
        {
            row.push_back(atoll(line.c_str()));
        }

        // Aggiungi la riga al vettore di input
        input.push_back(row);
    }

    ifs.close();
}

void printInput(std::vector<std::vector<long long>> &input)
{
    for (auto vect : input)
    {
        for (auto num : vect)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

void generateOperations(int size, std::vector<std::string> &operations)
{
    int numCombinations = pow(2, size); // 2^size combinazioni
    for (int i = 0; i < numCombinations; ++i)
    {
        std::string op = "";
        for (int j = 0; j < size; ++j)
        {
            if (i & (1 << j))
            { // Controlla il bit j di i
                op += '+';
            }
            else
            {
                op += '*';
            }
        }
        operations.push_back(op);
    }
}



long combineOperation(std::vector<long long> &vettore, std::vector<std::string> &operation)
{
    long tot = 0;
    long primoTermine = vettore[0];
    int pos = 1;

    for (auto str : operation)
    {   
        tot = vettore[1];
        pos = 1;
        for (auto c : str)
        {
            if (c == '+')
            {
                tot += vettore[pos + 1];
            }
            else
            {
                tot *=  vettore[pos + 1];
            }
            ++pos;
        }
        if (tot == primoTermine)
        {
            return primoTermine;
        }
    }
    return 0;
}


long verOperation(std::vector<std::vector<long long>> &input)
{
    long totale = 0;
    std::vector<std::string> operation;

    for (auto vect : input) // testo su tutte le equazioni di input
    {
        generateOperations(vect.size() - 2, operation); // trovo tutte le combinazioni di + e *
        for (auto string : operation)
        {
            if (combineOperation(vect, operation) != 0)
            {
                totale += vect[0];
                operation.clear(); // stoppo il for se trovo una combinazione
                break;
            }
        }
    }
    return totale;
}


int main()
{
    std::vector<std::vector<long long>> *input = new std::vector<std::vector<long long>>;
    getInput(*input);
    // printInput(*input);
    long long tot = verOperation(*input);
    std::cout << tot << std::endl;

    delete input;
    return 0;
}