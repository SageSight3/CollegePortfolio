//
//  LLN.hpp
//  LL1
//
//  Created by Andrew Poe on 2/1/23.
//
#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include "LL.h"
using namespace std;

class LL;
class LLN {
private:
    string data;
    LLN* next;
public:
    LLN(string s, LLN* n);
    void print();
    void addback(string s);
    string alphabeticalfirst();
    void removeall(string s, LLN* prev, LL* L);
    void setnext(LLN* p);
    LLN* split();
    ~LLN();
    LLN* merge(LLN* other);
    LLN* getnext();
    string getdata();
    LLN* mergesort();
    LLN* findLast(); //will find last link in list
    bool outOfOrder(LLN* aLink); //will compare this to aLink and return true, if aLink->data is less than this->data
    bool repairList(LLN* prev); //after an out of order link is found, will change pointers to fix list, returns true if head needs to 
                                //be reassigned
    void insert(LLN* aLink); //inserts a link in the middle of the list
    LLN* findSortedPos(LLN* aLink, LLN* prev); //will find sorted position for an out of order link
    LLN* insertSortIteration(LLN* prev); //will sort a out of order link
    bool checkSort(); //will return true if list is fully sorted
 };
