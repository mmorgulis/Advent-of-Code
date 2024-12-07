#include <iostream>
#include <fstream>
#include <vector>
#include <array>

bool isPrevious(int num, std::vector<int> before, const std::vector<std::array<int, 2>> &rules);
bool isAfter(int num, std::vector<int> after, const std::vector<std::array<int, 2>> &rules);
void stampa(const std::vector<std::array<int, 2>> &rules, const std::vector<std::vector<int>> &lists);
long verifyCorrectness(const std::vector<std::array<int, 2>> &rules, const std::vector<std::vector<int>> &lists);

void stampa(const std::vector<std::array<int, 2>> &rules, const std::vector<std::vector<int>> &lists)
{
    for (auto arr : rules)
    {
        std::cout << arr[0] << " " << arr[1] << std::endl;
    }

    for (auto vect : lists)
    {
        for (auto intero : vect)
        {
            std::cout << intero << " ";
        }
        std::cout << std::endl;
    }
}

long verifyCorrectness(const std::vector<std::array<int, 2>> &rules, const std::vector<std::vector<int>> &lists) {
    long counterTot = 0;

    // Itera attraverso ogni lista in `lists`
    for (const auto &vect : lists) {
        int counter = 0;

        // Itera su ogni elemento di `vect`
        for (size_t i = 0; i < vect.size(); ++i) {
            // Crea i sottovettori precedente e successivo
            std::vector<int> subvectorBefore(vect.begin(), vect.begin() + i);
            std::vector<int> subvectorAfter(vect.begin() + i + 1, vect.end());

            // Controlla le regole per i sottovettori
            if (!isPrevious(vect[i], subvectorBefore, rules) || !isAfter(vect[i], subvectorAfter, rules)) {
                counter++; // Incrementa se l'elemento NON soddisfa le regole
            }
        }

        // Se TUTTI gli elementi rispettano le regole
        if (counter == 0) {
            // Aggiungi il valore centrale della lista al contatore totale
            counterTot += vect[vect.size() / 2];
            // std::cout << vect[vect.size() / 2] << std::endl;
        }
    }

    return counterTot;
}

bool isPrevious(int numero, std::vector<int> before, const std::vector<std::array<int, 2>> &rules) {
    for (int i : before) {
        for (auto arr : rules) {
            if (arr[0] == numero && arr[1] == i) {
                return false;
            }
        }
    }
    return true;
}

bool isAfter(int numero, std::vector<int> after, const std::vector<std::array<int, 2>> &rules) {
    for (int i : after) {
        for (auto arr : rules) {
            if (arr[0] == i && arr[1] == numero) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    std::vector<std::array<int, 2>> rules;
    std::vector<std::vector<int>> lists;
    std::string line;
    int counter = 0;
    bool primaParteFine = false;

    std::ifstream ifs("input.txt");
    if (ifs.is_open())
    {
        while (std::getline(ifs, line))
        {
            if (line.empty())
            {
                primaParteFine = true;
                continue; // Salta la linea vuota
            }

            if (primaParteFine)
            {
                // Parsing della seconda parte (lists)
                size_t pos = 0;
                lists.emplace_back(); // Aggiungi un nuovo sottovettore
                while ((pos = line.find(',')) != std::string::npos)
                {
                    lists[counter].push_back(atoi(line.substr(0, pos).c_str()));
                    line.erase(0, pos + 1);
                }
                lists[counter].push_back(atoi(line.c_str())); // Ultimo numero
                ++counter;
            }
            else
            {
                // Parsing della prima parte (rules)
                size_t delimiter = line.find('|');
                if (delimiter != std::string::npos)
                {
                    int first = atoi(line.substr(0, delimiter).c_str());
                    int second = atoi(line.substr(delimiter + 1).c_str());
                    rules.push_back({first, second});
                }
            }
        }
        ifs.close();
    }

    //stampa(rules, lists);

    long total = verifyCorrectness(rules, lists);
    std::cout << total << std::endl;

    return 0;
}
