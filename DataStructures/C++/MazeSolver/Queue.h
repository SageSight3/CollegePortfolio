#ifndef _QUEUE_
#define _QUEUE_

#include <iostream>
#include <string>
#include <cstdlib>
#include "LLN.h"
#include "QObj.h"
using namespace std;

class LLN;
class Queue {

private:
	LLN* head, * tail;
public:
	Queue();
	~Queue();
	void ENQUEUE(int row, int col);
	QObj* DEQUEUE();
	bool ISEMPTY();
};
#endif