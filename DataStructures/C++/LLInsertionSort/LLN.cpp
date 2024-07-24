//
//  LLN.cpp
//  LL1
//
//  Created by Andrew Poe on 2/1/23.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include "LLN.h"
#include "LL.h"
using namespace std;

LLN::LLN(string s, LLN* n) {

	data = s;
	next = n;
}

void LLN::print() {

	cout << data << endl;
	if (next) next->print();
}

void LLN::addback(string s) {
	if (!next) next = new LLN(s, nullptr);
	else next->addback(s);
}
//in a linked list I am the first node in my part of the list.
//There may be nodes come before me, but I can't see them.
string LLN::alphabeticalfirst() {

	if (!next) //For all intents and purposes, I'm the only node
		return data;
	string firstafterme = next->alphabeticalfirst(); //Trust that this works.
	//Trust that I now have the best from next on down
	if (data < firstafterme) return data;
	return firstafterme;
}

void LLN::removeall(string s, LLN* prev, LL* L) {
	//So this method has access to my previous node AND it also has access to the 
	//Linked list as a whole.

	if (next) next->removeall(s, this, L);
	//Notice that *I* am my next's previous.
	//Now I TRUST that recursion worked.  And s is gone from next
	//on down.  The only node I have to worry about is myself.
	//If you are deleting, it is wise to do recursion first.
	if (data == s) {
		if (prev) prev->setnext(next);
		else L->sethead(next);
		next = nullptr;
		delete this;
	}
	//"delete this" is perfectly as long you never use your own
	//node's data AFTER you delete this.  If you attempt to use your
	//own data after delete this, your program can crash.  You can
	//still use local variables, but not the data stored in your own
	//object.
}

void LLN::setnext(LLN* p) {

	next = p;
}

LLN::~LLN() {
	delete next;
}

LLN* LLN::split() {
	//This method splits the list in half.  "this" will be the head of
	//one list.  The head of the other list will be returned by this
	//method.

	if (!next) return nullptr;
	LLN* second = next;
	next = next->split();
	return second;
}

LLN* LLN::merge(LLN* other) {

	//merges two sorted lists, one headed by "this" and one headed by
	//"other" and returns the head of the new sorted list.

	if (!other) return this;
	if (data <= other->getdata()) {
		//I know that this is the new head
		next = other->merge(next);//Why is next->merge(other) wrong?
		return this;
	}
	other->setnext(merge(other->getnext()));
	return other;
}

LLN* LLN::getnext() {

	return next;
}

string LLN::getdata() {

	return data;
}

LLN* LLN::mergesort() {
	//Split list into two halves.  Sort each half.  Merge sorted halves.
		//return head of merged list.

	if (!next) return this;
	LLN* other = split();
	//Split splits the list in half.  One list is "this" the other is returned.
	return mergesort()->merge(other->mergesort());

}

bool LLN::outOfOrder(LLN* aLink) { //pass out of order link as parameter, call recursively on rest of list, until sorted position found
	return data < aLink->data;
}

LLN* LLN::findSortedPos(LLN* aLink, LLN* prev) { //call first on out of order link's next
	if (next == nullptr) {
		return this;
	}
	if (outOfOrder(aLink)) {
		return next->findSortedPos(aLink, this);
	}
	return prev;
}

bool LLN::repairList(LLN* prev) {
	if (!prev) {
		return true;
	}
	prev->next = next;
	return false;
}

void LLN::insert(LLN* aLink) { //call on sorted pos prev
	aLink->next = next;
	next = aLink;
}

LLN* LLN::insertSortIteration(LLN* prev) { //will start at head each iteration
	LLN* newhead = nullptr;
	if (!(next == nullptr)) {
		next->insertSortIteration(this);
		if (next->outOfOrder(this)) {
			if (repairList(prev)) { //case for if head is out of orde
				newhead = next;
			}

			LLN* sortedPos = next->findSortedPos(this, this);
			sortedPos->insert(this);
		}
	}

	//list should be fully sorted when it runs on last link
	if (newhead == nullptr) {
		return this;
	}
	else {
		return newhead;
	}
}

bool LLN::checkSort() {
	if (next == nullptr) {
		return true;
	}
	if (data > next->data) {
		return false;
	}
	next->checkSort();
}

LLN* LLN::findLast() {
	if (next == nullptr) {
		return this;
	}
	return next->findLast();
}
