#include <iostream>
#include <fstream>
#include <array>
#include "main.h"

long wordSearch(char (&matrix)[SIZE][SIZE], std::string parola) {
    long counter = 0;

    // Ricerca in tutte le direzioni la parola XMAS
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // Ricerca a destra
            if (j <= SIZE - parola.size() && searchDx(matrix, i, j, parola)) {
                ++counter;
            }

            // Ricerca a sinistra
            if (j >= parola.size() - 1 && searchSx(matrix, i, j, parola)) {
                ++counter;
            }

            // Ricerca diagonale sud-est
            if (i <= SIZE - parola.size() && j <= SIZE - parola.size() && searchDiagonalSE(matrix, i, j, parola)) {
                ++counter;
            }

            // Ricerca diagonale nord-est
            if (i >= parola.size() - 1 && j <= SIZE - parola.size() && searchDiagonalNE(matrix, i, j, parola)) {
                ++counter;
            }

            // Ricerca diagonale sud-ovest
            if (i <= SIZE - parola.size() && j >= parola.size() - 1 && searchDiagonalSW(matrix, i, j, parola)) {
                ++counter;
            }

            // Ricerca diagonale nord-ovest
            if (i >= parola.size() - 1 && j >= parola.size() - 1 && searchDiagonalNW(matrix, i, j, parola)) {
                ++counter;
            }

            // Ricerca sopra
            if (i >= parola.size() - 1 && searchUp(matrix, i, j, parola)) {
                ++counter;
            }

            // Ricerca sotto
            if (i <= SIZE - parola.size() && searchDown(matrix, i, j, parola)) {
                ++counter;
            }
        }
    }

    return counter;
}

long wordSearch2(char (&matrix)[SIZE][SIZE], std::string parola) {
    // ricerco parola MAS in formazioni a X
    long counter = 0;
    // CON LA PAROLA INVERSA
    std::string inv = std::string(parola.rbegin(), parola.rend());
    // Faccio una ricerca in diagonale (SE, NE, NO, SO) della parola
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // Ricerca match SE + SW (sia mas sia sam)
            if (i <= SIZE - parola.size() && j <= SIZE - parola.size() 
                && (searchDiagonalSE(matrix, i, j, parola) || searchDiagonalSE(matrix, i, j, inv))  // ricerca sudest sia 'mas' sia 'sam'
                && (searchDiagonalSW(matrix, i, j+2, parola) || searchDiagonalSW(matrix, i, j+2, inv))) { // ricerca sudovest due colonne dopo e nordovest due righe, le condizioni si verificano per forza
                ++counter;
            }

        }
    }

    return counter;
}


bool searchDx(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola) {
    for (int k = 0; k < parola.size(); ++k) {
        if (matrix[i][j + k] != parola[k]) {
            return false;
        }
    }
    return true;
}

bool searchSx(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola) {
    for (int k = 0; k < parola.size(); ++k) {
        if (matrix[i][j - k] != parola[k]) {
            return false;
        }
    }
    return true;
}

bool searchDiagonalSE(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola) {
    for (int k = 0; k < parola.size(); ++k) {
        if (matrix[i + k][j + k] != parola[k]) {
            return false;
        }
    }
    return true;
}

bool searchDiagonalNE(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola) {
    for (int k = 0; k < parola.size(); ++k) {
        if (matrix[i - k][j + k] != parola[k]) {
            return false;
        }
    }
    return true;
}

bool searchDiagonalSW(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola) {
    for (int k = 0; k < parola.size(); ++k) {
        if (matrix[i + k][j - k] != parola[k]) {
            return false;
        }
    }
    return true;
}

bool searchDiagonalNW(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola) {
    for (int k = 0; k < parola.size(); ++k) {
        if (matrix[i - k][j - k] != parola[k]) {
            return false;
        }
    }
    return true;
}

bool searchUp(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola) {
    for (int k = 0; k < parola.size(); ++k) {
        if (matrix[i - k][j] != parola[k]) {
            return false;
        }
    }
    return true;
}

bool searchDown(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola) {
    for (int k = 0; k < parola.size(); ++k) {
        if (matrix[i + k][j] != parola[k]) {
            return false;
        }
    }
    return true;
}

int main() {
    char inputString[SIZE][SIZE];
    int i = 0;
    std::ifstream myFile;
    myFile.open("input.txt");

    if (myFile.is_open()) {
        while (myFile >> inputString[i]) {
            ++i;
        }
        myFile.close();

        std::string word = "XMAS";  // La parola da cercare
        std::string word2 = "MAS";  // Un'altra parola da cercare

        // Chiamata alla funzione di ricerca
        long totalMatches = wordSearch(inputString, word);
        long totalMatches2 = wordSearch2(inputString, word2);
        std::cout << "Numero parole 'XMAS': " << totalMatches << std::endl;
        std::cout << "Numero parole 'X-MAS': " << totalMatches2 << std::endl;
        // 622 too low
    } else {
        std::cout << "Unable to open the file";
        return 1;
    }

    return 0;
}
