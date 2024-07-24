#include <iostream>
#include <string>
#include <cstdlib>
#include "Queue.h"
#include "LLN.h"
#include "QObj.h"
using namespace std;

Queue::Queue() {

	head = nullptr;
}

Queue::~Queue() {

	delete head;
}

void Queue::ENQUEUE(int row, int col) {
	QObj* obj = new QObj(row, col);

	if (!head) head = tail = new LLN(obj);
	else {
		tail->setnext(new LLN(obj));
		tail = tail->getnext();
	}
}

QObj* Queue::DEQUEUE() {

	if (!head) return nullptr;
	QObj* obj = head->getinfo();
	LLN* t = head;
	head = head->getnext();
	t->setnext(nullptr);
	t->setinfo(nullptr);
	delete t;
	return obj;
}

bool Queue::ISEMPTY() {

	return !head;
}