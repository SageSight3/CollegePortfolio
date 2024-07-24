#include <iostream>
#include <string>
#include <cstdlib>
#include "ComparableString.h"
using namespace std;

ComparableString::ComparableString(string S) {
	s = S; //sets s to constructor input
}

int ComparableString::cmp(Comparable* c) {

	ComparableString* cs = (ComparableString*)c; //type casts c as a comparable int

	//case insensitivity
	string comps = "";
	for (int i = 0; i < s.length(); ++i) {
		comps += tolower(s[i]);
	}

	string compS = ""; 
	for (int i = 0; i < cs->s.length(); ++i) {
		compS += tolower(cs->s[i]);
	}


	if (comps < compS) {
		return -1;
	}

	if (comps > compS) {
		return 1;
	}
	
	return 0;
}

void ComparableString::print() { //prints i
	cout << s;
}

string ComparableString::gets() { //returns i
	return s;
}