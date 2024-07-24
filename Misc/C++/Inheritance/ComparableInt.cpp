#include <iostream>
#include <string>
#include <cstdlib>
#include "ComparableInt.h"
using namespace std;

ComparableInt::ComparableInt(int I) {
	i = I; //sets i to constructor input
}

int ComparableInt::cmp(Comparable* c) {

	ComparableInt* ci = (ComparableInt*)c; //type casts c as a comparable int

	if (i < ci->i) {
		return -1;
	}

	if (i > ci->i) {
		return 1;
	}
	
	return 0;
}

void ComparableInt::print() { //prints i
	cout << i;
}

int ComparableInt::geti() { //returns i
	return i;
}