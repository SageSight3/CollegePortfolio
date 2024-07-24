#include <iostream>
#include <string>
#include <cstdlib>
#include "LinkedList.h"
#include "Link.h"

LinkedList::LinkedList() {
	head = nullptr;
}

LinkedList::~LinkedList() {
	cout << "deleted linked list" << endl;
	delete head;
}

void LinkedList::addLink(string aTitle) {
	Link* aLink = new Link(aTitle); //initializes new link
	if (!head) { //sets aLink to head if there is none, otherwise sets it to head's next
		head = aLink;
	}
	else {
		if (head->checkForTitle(aTitle)) {
			delete aLink;
			return;
		}
		head->add(aLink);
	}
}

bool LinkedList::checkForTitle(string aTitle) {
	return head->checkForTitle(aTitle);
}

/*
void LinkedList::macroSort() {
	head = head->macroSort();
}
*/

void LinkedList::print() {
	if (head == nullptr) {
		return;
	}
	head->macroSort(head);
	head = head->findHead(head);
	head->print();
}

void LinkedList::removeSubstring(string substring) {
	if (head == nullptr) {
		return;
	}
	if (head->removeSubstring(substring)) {
		if (head == nullptr) {
			return;
		}
		head = head->guillotine();
	}
}

/*
string LinkedList::testComparand() {
	string comparand = head->setComparand("monkeys are cool", 0, 0, 6);
	return comparand;
}
*/

/*
void LinkedList::AddSorted(string s) {
	//adds a string to the linked list, maintaining the list in
	//alphabetical order

	if (!head) head = new Link(s, nullptr);
	else head = head->AddSorted(s); // <== I make the helper method return the new head
		//What are things we have to keep in mind?
		//If the new node comes before the current head, then
		//the current head will have to change
}

void LinkedList::remove(string s) {

	if (!head) return;    //What do we do if there is no head?
	//If there is a head, what can we do in this method?
	head = head->removeAll(head, s); //head->remove will remove the offending node, and return the new head


	//There has to be a mechanism to change the head
}
*/