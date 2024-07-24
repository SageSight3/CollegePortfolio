#pragma once
#ifndef _LIBRARY_
#define _LIBRARY_

#include <iostream>
#include <string>
#include <cstdlib>
#include "LinkedList.h"
using namespace std;

class Library {
public:
	//all methods have aList parameter, since they're defined independently from one
	void runCommand(string command, string argument, LinkedList* aList);
	void add(string aTitle, LinkedList* aList);
	void help();
	void exit(LinkedList* aList);
	void print(LinkedList* aList);
	void removeSubstring(LinkedList* aList, string substring);
	//void AddSorted(string aTitle, LinkedList* aList);
	//void remove(string aTitle, LinkedList* aList);
};

#endif
