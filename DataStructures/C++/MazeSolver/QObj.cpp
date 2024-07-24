#include <iostream>
#include <string>
#include <cstdlib>
#include "QObj.h"
#include "PG3.h"
using namespace std;

QObj::QObj(int rowCoord, int colCoord) {
	r = rowCoord;
	c = colCoord;
}

QObj::~QObj() {

}

int QObj::getr() {
	return r;
}

int QObj::getc() {
	return c;
}

