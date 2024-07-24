#include <iostream>
#include <string>
#include <cstdlib>
#include "Link.h"
#include "LinkedList.h"
using namespace std;

Link::Link(string aTitle) {
	title = aTitle;
	next = nullptr;
	prev = nullptr;
}

/*
Link::Link(string aTitle, Link* aLink) {
	title = aTitle;
	next = aLink;
	prev = nullptr;
}
*/

Link::~Link() {
	cout << "deleted a link" << endl;
	if (this == nullptr) {
		delete this;
	}
	delete next;
}

Link* Link::getNext() {
	return next;
}

void Link::setNext(Link* aLink) { //sets next to aLink
	next = aLink;
}

Link* Link::getPrev() {
	return prev;
}

void Link::setPrev(Link* aLink) {
	prev = aLink;
}

void Link::add(Link* aLink) { //adds aLink to the end of the list by recursively checking if each link has a next until one doesn't
	if (!next) {
		setNext(aLink);
		aLink->setPrev(this);
	}
	else {
		next->add(aLink);
	}
}

string Link::getTitle() {
	return title;
}

bool Link::checkForTitle(string aTitle) {

	//lowercase conversion for case insensitivity
	string titleLower = this->lowercase(title);
	string aTitleLower = this->lowercase(aTitle);

	//string newTitle = aTitle; 
	if (!next) {
		if (aTitleLower == titleLower) { //runs recursively down the list, and returns true if a duplicate title is found
			//cout << title << endl;
			return true;
		}
		return false;
	}
	if (aTitleLower == titleLower) {
		//cout << title << endl;
		return true;
	}
	return next->checkForTitle(aTitle);
}

/*
Link* Link::macroSort() {
	if (!next) {
		return microSort(this);
	}
	else {
		return macroSort(microSort(this), this->next);
	}
}

Link* Link::macroSort(Link* head, Link* aLink) {
	if (!next) {
		return microSort(head);
	}
	else {
		return macroSort(microSort(head), this->next);
	}
}

Link* Link::microSort(Link* aHead) {
	if (!next) {
		return aHead;
	}
	if (aHead->title < aHead->next->title) {
		microSort(aHead->next, this); //puts itself as next's previous
		return aHead;
	}
	if(aHead->title > aHead->next->title) {
		Link* newHead = aHead->next;
		aHead->next = aHead->next->next; //b = aHead->next, aHead->next = b->next
		newHead->setNext(aHead);
		microSort(aHead->next, this);
		return newHead;
	}
}


void Link::microSort(Link* aLink, Link* prev) {
	if (aLink->next == nullptr) { //checks to see if ther's a next
		return;
	}
	if (aLink->title < aLink->next->title) {
		microSort(aLink->next, this);
		return;
	}
	if (aLink->title > aLink->next->title) {
		Link* temp = aLink->next;
		aLink->next = aLink->next->next;
		temp->next = aLink;
		prev->next = temp;
		microSort(aLink->next, this);
		return;
	}
}
*/

Link* Link::findHead(Link* aLink) {
	if (aLink->prev == nullptr) {
		return aLink;
	}
	return findHead(aLink->prev);
}

void Link::macroSort(Link* aLink) {
	if (aLink->next == nullptr) {
		microSort(findHead(aLink));
	}
	else {
		microSort(findHead(aLink));
		if (!(aLink->next == nullptr)) {
			macroSort(aLink->next);
		}
	}
}

void Link::microSort(Link* aLink) {

	//lowercase conversion for case insensitivity
	string titleLower = this->lowercase(aLink->title);
	/*
	string nextTitleLower = "";
	if (!(aLink->next == nullptr)) { //in case of no next
		string nextTitleLower = this->lowercase(aLink->next->title);
	}
	*/

	if (aLink->getNext() == nullptr) {
		return;
	}
	if (titleLower < this->lowercase(aLink->next->title)) {
		microSort(aLink->getNext());
	}
	if (titleLower > this->lowercase(aLink->next->title)) {
		//swaps aLink with it's next
		if (!(aLink->next->getNext() == nullptr) && !(aLink->getPrev() == nullptr)) { //case for no next after aLink's next
			aLink->prev->setNext(aLink->getNext());
			aLink->setNext(aLink->next->getNext());
			aLink->prev->getNext()->setNext(aLink);
			aLink->prev->getNext()->setPrev(aLink->prev);
			aLink->setPrev(aLink->prev->getNext());
			aLink->next->setPrev(aLink);
			microSort(aLink->getNext());
		}
		else if (aLink->next->getNext() == nullptr && aLink->getPrev() == nullptr) {
			aLink->next->prev = nullptr;
			aLink->next->next = aLink;
			aLink->prev = aLink->next;
			aLink->next = nullptr;
		}
		else if (aLink->next->getNext() == nullptr) {
			//doesn't call microSort again, because aLink is now the end of the list
			aLink->prev->setNext(aLink->getNext());
			aLink->next = nullptr;
			aLink->prev->getNext()->setNext(aLink);
			aLink->prev->getNext()->setPrev(aLink->prev);
			aLink->setPrev(aLink->prev->getNext());
		}
		else if (aLink->getPrev() == nullptr) {
			aLink->setPrev(aLink->getNext());
			aLink->setNext(aLink->prev->getNext());
			aLink->prev->setNext(aLink);
			aLink->prev->prev = nullptr;
			aLink->next->setPrev(aLink);
			microSort(aLink->getNext());
		}
	}
}

void Link::print() { //prints the list recursively
	if (!next) {
		cout << title << endl;
	}
	else {
		cout << title << endl;
		next->print();
	}
}

/*
void Link::removeSubstring(string substring) {
	if (!(this->next == nullptr) && !(this->prev == nullptr)) {
		//maybe problem child
		this->next->removeSubstring(substring); //sets recursion to happen first so method isn't called on a null object
		if (detectSubstring(substring, 0)) {
			this->prev->next = this->next;
			this->next->prev = this->prev;
			this->next = nullptr; //sets our next to null so delete doesn't wipe out the list
			delete this;
		}
	}
	else if (this->next == nullptr) {
		if (detectSubstring(substring, 0)) {
			this->prev->next = nullptr;
			delete this;
		}
	}
	else if (this->prev == nullptr) {
		this->next->removeSubstring(substring);
		if (detectSubstring(substring, 0)) {
			this->next->prev = nullptr;
			this->next = nullptr;
			delete this;
		}
	}
}

/*
bool Link::detectSubstring(string substring, int posInTitle) {
	string comparand = substring; //sets comparand to string of substring's length
	if (posInTitle + substring.length() >= title.length()) { //checks if substring is still possible in info
		comparand = setComparand(title, posInTitle, 0, comparand.length()); //sets comparand to piece of info
		if (comparand == substring) { //returns true if substring found
			return true;
		}
		return false;
	}
	if (comparand == substring) {
		return true;
	}
	detectSubstring(substring, posInTitle + 1); //runs recursively if more characters in info
}


//problem child
string Link::setComparand(string title, int titleIndex, int posInComparand, int comparandLength) {
	string comparandPiece = ""; //holds onto a piece of comparand to append with others into the full one
		if (comparandLength = posInComparand) {
			if (titleIndex + posInComparand <= title.length()); { //checks to make sure appending comparandPiece doesn't cause an out of bounds error
				comparandPiece += title[titleIndex + posInComparand];
				return comparandPiece;
			}
			return comparandPiece; //returns empty string if no characters can be added
		}
	if (titleIndex + posInComparand <= title.length()) {
		comparandPiece += title[titleIndex + posInComparand];
		comparandPiece += setComparand(title, titleIndex, posInComparand + 1, comparandLength); //runs recursively until all pieces of comparand have been appended together
			return comparandPiece;
	}
	return comparandPiece;
}
*/

bool Link::removeSubstring(string substring) {

	//lowercase conversion for case insensitivity
	string titleLower = this->lowercase(title);
	string substringLower = this->lowercase(substring);

	if (next) {
		next->removeSubstring(substringLower);
	}
	if (!(titleLower.find(substringLower) == string::npos)) {
		if (!(next == nullptr) && !(prev == nullptr)) {
			prev->next = this->next;
			next->prev = this->prev;
			next = nullptr;
			delete this;
			return false;
		}
		else if (next == nullptr && prev == nullptr) {
			//delete this;
			return true;
		}
		else if (next == nullptr) {
			prev->next = nullptr;
			delete this;
			return false;
		}
		else if (prev == nullptr) {
			return true;
		}
	}
	return false;
}

Link* Link::guillotine() {
	Link* newHead = getNext();
	if (!(next == nullptr)) {
		next->prev = nullptr;
	}
	next = nullptr;
	delete this;
	return newHead;
}

string Link::lowercase(string aString) {
	for (int index = 0; index < aString.length(); ++index) {
		aString[index] = tolower(aString[index]); //found through string library: https://cplusplus.com/reference/cctype/tolower/
	}
	return aString;
}

/*
Link* Link::AddSorted(string s) {
	//this will add the node to the list and will return the new "head." (It will return the "head"
	//of the list beginning with me.
	//Is there something we can check before even checking whether we have a next?
	//Even without checking my next, I can test whether the "new guy" will
		//be first in the list.

	if (s < title) { //Does the new guy come before me?

		Link* newguy = new Link(s, this); //"this" in C++ or Java means myself
		return newguy;
	}
	if (!next) {
		next = new Link(s, nullptr);
		return this;
	}

	next = next->AddSorted(s);
	return this;
}

Link* Link::remove(string substring) { //only removes one link 

	//lowercase conversion for case insensitivity
	string titleLower = this->lowercase(title);
	string substringLower = this->lowercase(substring);

	if (!(titleLower.find(substringLower) == string::npos)) { //If I am the node that needs to be deleted
		Link* newhead = next;
		next = nullptr;
		delete this;  //At this point, I can't use my own stuff.
		return newhead;
	}
	if (!next) return this;  //I'm the only node...and I don't match, so I am still the head
	next = next->remove(substring);  //See if next can remove a bad node
	return this;  //But I'm still the head either way.
}

Link* Link::removeAll(Link* aLink, string substring) {
	Link* finalHead = this;
	if (aLink->next == nullptr) {
		finalHead = aLink->remove(substring);
	}
	else {
		if (!(aLink->next == nullptr)) {
			removeAll(aLink->next, substring);
			aLink = aLink->remove(substring);
		}
	}
	return finalHead;
}
*/