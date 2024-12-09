#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

typedef std::vector<std::vector<char>> vect;
typedef std::vector<std::pair<char, std::vector<std::pair<int, int>>>> pair;
typedef std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> comb;

void takeInput(vect &input)
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

void printInput(const vect &input)
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

void findDup(const vect &input, pair &caratteri)
{
    // Mappa temporanea per tracciare le posizioni dei caratteri
    std::unordered_map<char, std::vector<std::pair<int, int>>> charPositions;

    // Scorrere la matrice per trovare caratteri ripetuti
    for (int i = 0; i < input.size(); ++i)
    {
        for (int j = 0; j < input[i].size(); ++j)
        {
            char c = input[i][j];
            if (c != '#' && c != '.')
            { // Ignora il carattere '#'
                charPositions[c].emplace_back(i, j);
            }
        }
    }

    // Trasferire i risultati nella struttura "caratteri"
    for (const auto &entry : charPositions)
    {
        if (entry.second.size() > 1)
        { // Considera solo caratteri ripetuti
            caratteri.emplace_back(entry.first, entry.second);
        }
    }
}

std::vector<char> collectAllCharacters(const vect &input) {
    std::unordered_set<char> charSet; // Per evitare duplicati
    std::vector<char> characters;    // Risultato finale

    for (const auto &row : input) {
        for (char c : row) {
            if (c != '.' && c != '#') { // Ignora i caratteri '.' e '#'
                if (charSet.find(c) == charSet.end()) {
                    charSet.insert(c); // Aggiungi al set
                    characters.push_back(c); // Aggiungi al vettore
                }
            }
        }
    }

    return characters;
}

comb generatePairCombinations(const pair &caratteri, comb &combinations)
{
    for (const auto &coppia : caratteri)
    {
        const auto &positions = coppia.second; // Lista delle posizioni associate a un carattere
        for (size_t i = 0; i < positions.size(); ++i)
        {
            for (size_t j = i + 1; j < positions.size(); ++j)
            {
                combinations.emplace_back(positions[i], positions[j]);
            }
        }
    }
    return combinations;
}

int markIfPossible(vect &input, std::vector<char> charVec, int row, int col) {
    // Controlla che la posizione sia valida
    int changes = 0;
    if (row >= 0 && row < input.size() && col >= 0 && col < input[0].size()) {
        
        if (input[row][col] == '.') {
            input[row][col] = '#';
            return 1;
        } 
        else {
           if (std::find(charVec.begin(), charVec.end(), input[row][col]) != charVec.end()) {
                return 1;
            }
        }
        
    }
    return 0;
}

int printSign(vect &input, std::vector<char> c, const std::pair<std::pair<int, int>, std::pair<int, int>> &com) {
    int totalChanges = 0;

    auto firstPosition = com.first;
    auto secondPosition = com.second;

    // Calcola gli spostamenti
    int rowShift = firstPosition.first - secondPosition.first;
    int colShift = firstPosition.second - secondPosition.second;

    // Genera le due posizioni principali da marcare
    int newRow1 = firstPosition.first + rowShift;
    int newCol1 = firstPosition.second + colShift;

    int newRow2 = secondPosition.first - rowShift;
    int newCol2 = secondPosition.second - colShift;

    // Esegui solo due chiamate a markIfPossible
    totalChanges += markIfPossible(input, c, newRow1, newCol1);
    totalChanges += markIfPossible(input, c, newRow2, newCol2);

    return totalChanges;
}

int main()
{
    vect input;
    pair caratteriRipetuti;
    comb combination;
    long tot = 0;
    // Del tipo <A; <4,5>, <6,10> ... > in cui A è
    //          <O; <7,9>, <4,6> ... >
    // il carattere e le coppie sono il luogo dell'occorrenza

    takeInput(input);
    // printInput(input);
    std::vector<char> allChar = collectAllCharacters(input);
    findDup(input, caratteriRipetuti);
    /*
    for (auto p : caratteriRipetuti) {
        std::cout << p.first << " : ";
        for (auto coppia : p.second) {
            std::cout << coppia.first << " " << coppia.second << ",";
        }
        std::cout << std::endl;
    } */
    for (auto c : caratteriRipetuti)
    {   
        combination.clear();
        combination = generatePairCombinations(caratteriRipetuti, combination);
        for (auto com : combination)
        {
            tot += printSign(input, allChar, com);
        }
        tot--; // ne ho aggiunto 1 in più
    }
    printInput(input);
    std::cout << tot << std::endl;
    // 2600 too high

    return 0;
}