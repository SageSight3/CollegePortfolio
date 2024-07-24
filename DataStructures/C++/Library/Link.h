#pragma once
#ifndef _LINK_
#define _LINK_

#include <iostream>
#include <string>
#include <cstdlib>
#include "LinkedList.h"

using namespace std;

class LinkedList;

class Link {

private:

	Link* next;

	//left prev in so i still have code for doube linked list, all changes to fucntion as single list have been made though
	Link* prev; //making Links double linked as their prevs are needed in multiple methods and having them know their prev simplifies
				//the code immensely
	string title;

public:
	Link(string aTitle);
	Link(string aTitle, Link* aLink);
	~Link();
	void setNext(Link* aLink);
	void setPrev(Link* aLink);
	bool checkForTitle(string aTitle); //checks if aTitle matches a link's title
	void add(Link* aLink);
	string getTitle();
	Link* getNext();
	Link* getPrev();
	void print();
	Link* findHead(Link *aLink);
	void macroSort(Link* aLink); //will sort full loist
	//Link* macroSort(Link* head, Link* aLink);
	void microSort(Link* aLink); //will sort head through the list
	//void microSort(Link* aLink, Link* prev); //will sort a link after head through the list
	bool removeSubstring(string substring); //is a bool that will return true if head needs to be reassigned
	//bool detectSubstring(string substring, int posInTitle); //detection method for substring in titles
	//string setComparand(string title, int titleIndex, int posInTitle, int posInComparand); //method for setting comparand in detectSubstring
	string lowercase(string aString); //method to convert strings to lowercase for case insensitivity
	Link* guillotine(); //deletes head but returns it's next so head can be reassigned
	//Link* AddSorted(string s); 
	//Link* remove(string s);
	//Link* removeAll(Link* aLink, string substring);
};

#endif