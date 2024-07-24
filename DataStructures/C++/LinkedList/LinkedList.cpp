#include "LinkedList.h"

Link::Link(std::string& anItem) {
	this->item = anItem;
	this->nextLink = nullptr;
	this->prevLink = nullptr;
}

Link::~Link() {

}

std::string& Link::getItem() {
	return this->item;
}

Link* Link::getNextLink() {
	return this->nextLink;
}

Link* Link::getPrevLink() {
	return this->prevLink;
}

void Link::setNextLink(Link* aLink) {
	this->nextLink = aLink;
}

void Link::setPrevLink(Link* aLink) {
	this->prevLink = aLink;
}

int Link::size() {
	if(this->nextLink == nullptr) {
		return 1;
	}
	return 1 + this->nextLink->size();
}

std::string& Link::at(int n) {
	if (n == 0) {
		return this->item;
	}
	return this->nextLink->at(n - 1);
}

LinkedList::LinkedList() {
	this->firstLink = nullptr;
	this->lastLink = nullptr;
}

LinkedList::~LinkedList() {

}

bool LinkedList::empty() {
	return firstLink == nullptr && lastLink == nullptr;
}

int LinkedList::size() {
	if (firstLink == nullptr) {
		return 0;
	}
	return firstLink->size();
}

std::string& LinkedList::front() {
	return firstLink->getItem();
}

std::string& LinkedList::back() {
	return lastLink->getItem();
}

std::string& LinkedList::at(int n) {
	return firstLink->at(n);
}

void LinkedList::push_back(std::string& anItem) {
	Link* aLinkPtr = new Link(anItem);
	if (this->empty()) {
		this->firstLink = aLinkPtr;
	}
	else {
		this->lastLink->setNextLink(aLinkPtr);
		aLinkPtr->setPrevLink(lastLink);
	}
	this->lastLink = aLinkPtr;
}

void LinkedList::pop_back() {
	Link* oldLast = lastLink;
	lastLink = lastLink->getPrevLink();
	if(this->lastLink == nullptr) {
		this->firstLink = nullptr;
	}
	else {
		lastLink->setNextLink(nullptr);
	}
	delete oldLast;
}

void LinkedList::clear() {
	while (!this->empty()) {
		this->pop_back();
	}
}