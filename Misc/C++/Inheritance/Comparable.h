//Andrew A. Poe, Professor, CS201-02-16F
//Northern Michigan University (Marquette Co, MI)
//Comparable definitions

#ifndef _COMPARABLE_
#define _COMPARABLE_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Comparable {
public:
	virtual int cmp(Comparable* c) = 0;
	// if a < b, a->cmp (b) should return a negative number
	// if a > b, a->cmp (b) should return a positive number
	// if a = b, a->cmp (b) should return zero

	virtual void print() = 0;
	//prints the data stored in this object
};


#endif