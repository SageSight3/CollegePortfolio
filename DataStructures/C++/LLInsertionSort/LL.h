//
//  LL.hpp
//  LL1
//
//  Created by Andrew Poe on 2/1/23.
//
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "LLN.h"
using namespace std;

class LLN; //since LL makes use of LLN, you should #include the LLN stuff AND make a class prototype of LLN stuff.
class LL {

private:
    LLN* head;
public:
    LL();
    void addFront(string s);
    void print();
    void addback(string s);
    string alphabeticalfirst();
    void removeall(string s);
    void sethead(LLN* p);
    void mergesort();
    void insertionSort(); //will run insertion sort
    void outOfOrder();
    ~LL();
};
