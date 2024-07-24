// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LinkedList.h"
#include <assert.h>

void linkTest();
void linkedListTest();

int main(int argc, char* argv[]) {
    std::cout << "Begin Testing." << std::endl;
    linkTest();
    linkedListTest();
    std::cout << "End Testing." << std::endl;
    return 0;
}

void linkTest() {
    std::cout << "Link Test" << std::endl;
    std::string msg = "ocarina of time";
    std::string msgb = "windwaker";
    Link* aLinkPtr = new Link(msg);
    Link* bLinkPtr = new Link(msgb);
    assert(aLinkPtr != nullptr);
    assert(aLinkPtr->getItem() == msg);
    aLinkPtr->setNextLink(bLinkPtr);
    bLinkPtr->setPrevLink(aLinkPtr);
    assert(bLinkPtr->getPrevLink() == aLinkPtr);
    assert(aLinkPtr->getNextLink() == bLinkPtr);
    assert(bLinkPtr->getNextLink() == nullptr);
    assert(aLinkPtr->getPrevLink() == nullptr);
    delete bLinkPtr;
    delete aLinkPtr;
    std::cout << "All Link Tests Passed." << std::endl;
}

void testEmptyLinkedList();
void testPushingBackOnList();
void testPoppingBackOffList();

void linkedListTest() {
    std::cout << "LinkedList Test" << std::endl;
    testEmptyLinkedList();
    testPushingBackOnList();
    testPoppingBackOffList();
    std::cout << "All LinkedList Tests Passed." << std::endl;
}

void testEmptyLinkedList() {
    LinkedList* aList = new LinkedList();
    assert(aList->empty());
    assert(aList->size() == 0);
    aList->clear();
    delete aList;
    std::cout << "TestEmptyLinkedList passed." << std::endl;
}

void testPushingBackOnList() {
    LinkedList* aList = new LinkedList();
    std::string item1 = "one fish";
    std::string item2 = "two fish";
    std::string item3 = "red fish";
    std::string item4 = "blue fish";
    aList->push_back(item1);
    assert(!aList->empty());
    assert(aList->size() == 1);
    assert(aList->front() == item1);
    assert(aList->back() == item1);
    assert(aList->at(0) == item1);
    aList->push_back(item2);
    assert(!aList->empty());
    assert(aList->size() == 2);
    assert(aList->front() == item1);
    assert(aList->back() == item2);
    assert(aList->at(0) == item1);
    assert(aList->at(1) == item2);
    aList->push_back(item3);
    aList->push_back(item4);
    assert(!aList->empty());
    assert(aList->size() == 4);
    assert(aList->front() == item1);
    assert(aList->back() == item4);
    assert(aList->at(0) == item1);
    assert(aList->at(1) == item2);
    assert(aList->at(2) == item3);
    assert(aList->at(3) == item4);
    aList->clear();
    assert(aList->empty());
    delete aList;
    std::cout << "TestPushingBackOnList passed." << std::endl;
}
void testPoppingBackOffList() {
    LinkedList* aList = new LinkedList();
    std::string item1 = "one fish";
    std::string item2 = "two fish";
    std::string item3 = "red fish";
    std::string item4 = "blue fish";
    aList->push_back(item1);
    aList->push_back(item2);
    aList->push_back(item3);
    aList->push_back(item4);
    aList->pop_back();
    assert(!aList->empty());
    assert(aList->size() == 3);
    assert(aList->at(2) == item3);
    assert(aList->back() == item3);
    aList->pop_back();
    aList->pop_back();
    assert(!aList->empty());
    assert(aList->size() == 1);
    assert(aList->at(0) == item1);
    assert(aList->front() == item1);
    aList->pop_back();
    assert(aList->empty());
    assert(aList->size() == 0);
    delete aList;
    std::cout << "TestPoppingBackOffList passed." << std::endl;
}
