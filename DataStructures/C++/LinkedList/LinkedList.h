#pragma once
#include <string>

class Link {
	Link* nextLink;
	Link* prevLink;
	std::string item;
public:
	Link(std::string& anItem);
	~Link();
	int size();
	std::string& at(int n);
	std::string& getItem();
	Link* getNextLink();
	Link* getPrevLink();
	void setNextLink(Link* aLink);
	void setPrevLink(Link* aLink);
};

class LinkedList {
	Link* firstLink;
	Link* lastLink;
public:
	LinkedList();
	~LinkedList();
	bool empty();
	int size();
	std::string& front();
	std::string& back();
	std::string& at(int n);
	void clear();
	void pop_back();
	void push_back(std::string& anItem);
};