#include <iostream>
#include <string>
#include <cstdlib>
#include "QObj.h"
#include "LLN.h"
using namespace std;

LLN::LLN(QObj* obj) {

	info = obj;
	next = nullptr;
}

LLN::~LLN() {

	delete info;
	delete next;
}

QObj* LLN::getinfo() {

	return info;
}

void LLN::setinfo(QObj* obj) {

	info = obj;
}

LLN* LLN::getnext() {

	return next;
}

void LLN::setnext(LLN* n) {

	next = n;
}