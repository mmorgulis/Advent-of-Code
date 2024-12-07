#ifndef METH_H
#define METH_H
#include <list>

typedef std::list<int> list;
typedef std::list<int>::iterator iter;

void clearIt();
void printList();
long calcDist();
long calcSimil();

#endif