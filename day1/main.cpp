#include <iostream>
#include <fstream>
#include <cmath>
#include "meth.h"

// variabili globali
list *l1 = new std::list<int>();
list *l2 = new std::list<int>();
unsigned int linesInFile = 1000;
iter it1, it2; 

void clearIt() 
{
    it1 = l1->begin();
    it2 = l2->begin();
}

void openfile() 
{
    clearIt();
    int num_input1 = 0;
    int num_input2 = 0;

    std::ifstream myfile;
    myfile.open("input.txt");
    if (myfile.is_open())
    {
        for (int i = 0; i < linesInFile; ++i)
        {
            // prendo il contenuto fino a spazio e metto in l1 il resto il l2
            myfile >> num_input1;
            l1->insert(it1, num_input1);
            myfile >> num_input2;
            l2->insert(it2, num_input2);
            ++it1;
            ++it2;
        }        
    } else {
        std::cout << "Unable to open the file" << std::endl;
    } 
    myfile.close(); 
}

void printList() 
{
    it1 = l1->begin();
    it2 = l2->begin();
    for (;it1 != l1->end(); ++it1)
    {
        std::cout << " " << *it1;
    }
    std::cout << std::endl;
    for (;it2 != l2->end(); ++it2)
    {
        std::cout << " " << *it2;
    }
    std::cout << std::endl;
}

long calcDist() 
{
    // ordino le liste
    l1->sort();
    l2->sort();
    long distanzaTot = 0;
    clearIt();
    // calcolo distanza
    for (;it1 != l1->end(); ++it1, ++it2)
    {
        distanzaTot += abs(*it1 - *it2);
    }
    return distanzaTot;
}

long calcSimil()
{
    // calcolo similarity
    // prendo ogni numero da l1 e lo moltiplico per il numero di volte che appare in l2
    long simil = 0;
    clearIt();
    for (; it1 != l1->end(); ++it1)
    {
        for (; it2 != l2->end(); ++it2) 
        {
            if (*it1 == *it2) 
            {
                simil += *it1;
            }
        }
        it2 = l2->begin();
    }
    return simil;

} 


int main() 
{
    // creo due liste ordinate (ordine crescente) da input
    // calcolo distanza totale con un for sulle due liste
    openfile();
    long distanza = calcDist();
    long similarity = calcSimil();
    std::cout << "distanza: " << distanza << std::endl;
    std::cout << "similarity: " << similarity << std::endl;
    
    delete l1;
    delete l2;
    l1 = nullptr;
    l2 = nullptr;

    return 0;
}

