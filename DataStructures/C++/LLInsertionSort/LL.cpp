//
//  LL.cpp
//  LL1
//
//  Created by Andrew Poe on 2/1/23.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include "LL.h"
using namespace std;

LL::LL() {

    head = nullptr;
}
void LL::addFront(string s) {

    head = new LLN(s, head);

}

void LL::addback(string s) {
    if (!head) head = new LLN(s, nullptr);
    else head->addback(s);
}

void LL::print() {
    if (head) head->print();
}

string LL::alphabeticalfirst() {

    if (!head) return "EMPTY LIST";
    return head->alphabeticalfirst();
}

void LL::removeall(string s) {
    //remove ALL entries with s
    if (!head) return;
    head->removeall(s, nullptr, this);
    //When I call head->removeall, I have it head's previous, which is null,
    //And I have to give it head's linked list, which is myself.
}

void LL::sethead(LLN* p) {

    head = p;
}

LL::~LL() {
    delete head;
}

void LL::mergesort() {
    //This will split the list in half.  Sort each half.  Merge the
    //sorted halves together.

    if (head) head = head->mergesort();
}

void LL::outOfOrder() {
    if (head->outOfOrder(head->getnext())) {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
}

void LL::insertionSort() {
    if (!(head == nullptr)) {
        if (!(head->checkSort())) {
            head = head->insertSortIteration(nullptr);
            insertionSort();
        }
    }
}
