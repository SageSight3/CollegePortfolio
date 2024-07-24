#ifndef _QOBJ_
#define _QOBJ_

#include <iostream>
#include <string>
#include <cstdlib>
#include "Queue.h"
#include "QObj.h"
using namespace std;

class QObj {

private:
	int r, c;
public:
	QObj(int rowCoord, int colCoord);
	~QObj();
	int getr();
	int getc();
};
#endif