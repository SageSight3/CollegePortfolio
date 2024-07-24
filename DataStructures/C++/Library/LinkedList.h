#pragma once
#ifndef _LINKEDLIST_
#define _LINKEDLIST_

#include <iostream>
#include <string>
#include <cstdlib>
#include "Link.h"
using namespace std;

//because I miised a lot of the lectures for linked lists, I've been referring to my java linked list for how to design them in c++

class Link;

class LinkedList {

private:

	Link* head;

public:
	LinkedList();
	~LinkedList();
	void addLink(string aTitle);
	bool checkForTitle(string aTitle); //method to check for duplicate titles in list
	//void macroSort(); //sorts the list
	void print();
	void removeSubstring(string substring); //removes titles with substring from the list
	//string testComparand();
	//void AddSorted(string s);
	//void remove(string s);
};

#endif