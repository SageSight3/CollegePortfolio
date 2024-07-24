#include <iostream>
#include <string>
#include <cstdlib>
#include "ComparableArray.h"
using namespace std;

ComparableArray::ComparableArray(int s) {
	CA = new Comparable * [s]; //initializes array of comparables
	sz = s; //sets size to CA length
}

ComparableArray::~ComparableArray() { //runs loops to delete all of
	for (int i = 0; i < sz; ++i) { //deletes all compaarables in CA
		delete CA[i];
	}
}

void ComparableArray::seti(int i, Comparable* c) { //sets aa comparable at index i to c
	CA[i] = c;
}

Comparable* ComparableArray::smallest() { //returns smallest comparable in CA
	Comparable* smallest = CA[0];

	for (int i = 0; i < sz; ++i) { //runs through each element in array and reassigns smallest if a new one is found
		if (smallest->cmp(CA[i]) == 1) {
			smallest = CA[i];
		}
	}
	return smallest;
}

Comparable* ComparableArray::largest() { //returns largest comparable in CA
	Comparable* largest = CA[0];

	for (int i = 0; i < sz; ++i) {
		if (largest->cmp(CA[i]) == -1) {
			largest = CA[i];
		}
	}
	return largest;
}