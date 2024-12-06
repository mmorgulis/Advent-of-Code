#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>

void takeInput(std::vector<std::vector<char>> &input);
void printInput(const std::vector<std::vector<char>> &input);
long move(std::vector<std::vector<char>> &input, char simbolo,
          int riga, int colonna, int rigaMax, int colonnaMax, int numPassi);

void takeInput(std::vector<std::vector<char>> &input)
{
    std::ifstream ifs;
    std::string line;
    std::vector<char> row;
    ifs.open("input.txt");
    assert(ifs.is_open());
    while (std::getline(ifs, line))
    {
        for (char c : line)
        {
            row.push_back(c);
        }
        input.push_back(row);
        row.clear();
    }
    ifs.close();
}

void printInput(const std::vector<std::vector<char>> &input)
{
    for (auto charVect : input)
    {
        for (char c : charVect)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

long move(std::vector<std::vector<char>> &input, char simbolo,
          int riga, int colonna, int rigaMax, int colonnaMax, int numPassi)
{

    if (riga >= rigaMax || colonna >= colonnaMax || riga <= 0 || colonna <= 0) {
        return numPassi + 1;
    }
    else
    {
        if ((input[riga - 1][colonna] == '#' && simbolo == '^') 
            || (input[riga + 1][colonna] == '#' && simbolo == 'v') 
            || (input[riga][colonna + 1] == '#' && simbolo == '>') 
            || (input[riga][colonna - 1] == '#' && simbolo == '<'))
        {
            // CAMBIA DIREZIONE
            /*
            std::cout << "Posizione: (" << riga + 1 << ", " << colonna + 1 << "), "
                      << "Passi: " << numPassi << ", "
                      << "Simbolo: " << simbolo << std::endl; */ 
            if (simbolo == '^')
                return move(input, '>', riga, colonna + 1, rigaMax, colonnaMax, numPassi + 1);
            else if (simbolo == '>')
                return move(input, 'v', riga + 1, colonna, rigaMax, colonnaMax, numPassi + 1);
            else if (simbolo == '<')
                return move(input, '^', riga - 1, colonna, rigaMax, colonnaMax, numPassi + 1);
            else if (simbolo == 'v')
                return move(input, '<', riga, colonna - 1, rigaMax, colonnaMax, numPassi + 1);
        }
        else
        {
            
            if (simbolo == '^')
            {   
                if (input[riga][colonna] != 'X') {
                    input[riga][colonna] = 'X';
                    return move(input, simbolo, riga - 1, colonna, rigaMax, colonnaMax, numPassi + 1);
                } else 
                    return move(input, simbolo, riga - 1, colonna, rigaMax, colonnaMax, numPassi);
            }
            else if (simbolo == '>')
            {
                if (input[riga][colonna] != 'X') {
                    input[riga][colonna] = 'X';
                    return move(input, simbolo, riga, colonna + 1, rigaMax, colonnaMax, numPassi + 1);
                } else 
                    return move(input, simbolo, riga, colonna + 1, rigaMax, colonnaMax, numPassi);
            }
            else if (simbolo == '<')
            {   
                if (input[riga][colonna] != 'X') {
                    input[riga][colonna] = 'X';
                    return move(input, simbolo, riga , colonna - 1, rigaMax, colonnaMax, numPassi + 1);
                }   
                else
                    return move(input, simbolo, riga , colonna - 1, rigaMax, colonnaMax, numPassi);
            }
            else if (simbolo == 'v')
            {
                if (input[riga][colonna] != 'X') {
                    input[riga][colonna] = 'X';
                    return move(input, simbolo, riga + 1, colonna, rigaMax, colonnaMax, numPassi + 1);
                }
                else 
                    return move(input, simbolo, riga + 1, colonna, rigaMax, colonnaMax, numPassi);
            }
            
        }
    }
}

int main()
{
    std::vector<std::vector<char>> *input = new std::vector<std::vector<char>>;
    takeInput(*input);
    // printInput(*input);
    int riga, colonna, rigaMax, colonnaMax, numPassi = 0;
    char car = '^';
    for (size_t i = 0; i < input->size(); ++i)
    {
        auto it = std::find((*input)[i].begin(), (*input)[i].end(), car);
        if (it != (*input)[i].end())
        {
            riga = i;
            colonna = it - (*input)[i].begin();
        }
    }
    // std::cout << "riga " << riga << " colonna " << colonna << std::endl;
    rigaMax = 130;
    colonnaMax = 130;
    long tot = move(*input, car, riga, colonna, rigaMax, colonnaMax, numPassi);
    std::cout << "il numero di passi è: " << tot << std::endl;
    // 5978 too high
    // 5353 too low

    delete input;
    return 0;
}