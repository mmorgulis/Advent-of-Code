#ifndef MAIN_H
#define MAIN_H

// Costante per la dimensione della matrice
const int SIZE = 140;

// Funzione principale per cercare una parola nella matrice
long wordSearch(char (&matrix)[SIZE][SIZE], std::string parola);

// Funzione per la ricerca a destra (orizzontale)
bool searchDx(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola);

// Funzione per la ricerca a sinistra (orizzontale)
bool searchSx(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola);

// Funzione per la ricerca diagonale sud-est (in basso a destra)
bool searchDiagonalSE(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola);

// Funzione per la ricerca diagonale nord-est (in alto a destra)
bool searchDiagonalNE(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola);

// Funzione per la ricerca diagonale sud-ovest (in basso a sinistra)
bool searchDiagonalSW(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola);

// Funzione per la ricerca diagonale nord-ovest (in alto a sinistra)
bool searchDiagonalNW(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola);

// Funzione per la ricerca sopra (verticale)
bool searchUp(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola);

// Funzione per la ricerca sotto (verticale)
bool searchDown(char (&matrix)[SIZE][SIZE], int i, int j, std::string parola);

#endif // WORD_SEARCH_H
