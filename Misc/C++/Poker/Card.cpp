#include <iostream>
#include <string>
#include <cstdlib>
#include "Card.h"
using namespace std;

Card::Card(int v) {

	//Classname::Methodname

	value = v;
	suit = value / 13; //0-3
	rank = value % 13; //0-12
/*
A value is from 0 to 51.
0-12 /13 = 0.    Suits
13-25  / 13 = 1.
26-38  / 13 = 2.
39-51  / 13 = 3.

0,13,26,39  % 13 = 0.
1,14,27,40  % 13 = 1.
...
12,25,37,51  % 13 = 12.

*/
	switch (rank) {
	case 0: name = "ACE"; break;
	case 1: name = "TWO"; break;
	case 2: name = "THREE"; break;
	case 3: name = "FOUR"; break;
	case 4: name = "FIVE"; break;
	case 5: name = "SIX"; break;
	case 6: name = "SEVEN"; break;
	case 7: name = "EIGHT"; break;
	case 8: name = "NINE"; break;
	case 9: name = "TEN"; break;
	case 10: name = "JACK"; break;
	case 11: name = "QUEEN"; break;
	case 12: name = "KING"; break;
	}
	name += " OF ";
	switch (suit) {
	case 0: name += "CLUBS"; break;
	case 1: name += "DIAMONDS"; break;
	case 2: name += "HEARTS"; break;
	case 3: name += "SPADES"; break;
	}
	/*
	string suitstr[4] = {"CLUBS","DIAMONDS","HEARTS","SPADES"};'
	name += suitstr[i];
	*/
}

Card::~Card() {
	//cout << "I have wiped out a card." << endl;
}

void Card::print() {
	cout << name << endl;
}
int Card::getrank() { return rank; }
int Card::getsuit() { return suit; }
int Card::getvalue() { return value; }
string Card::getname() { return name; }

void Card::setrank(int i) { rank = i; }
void Card::setsuit(int i) { suit = i; }
void Card::setvalue(int i) { value = i; }
void Card::setname(string s) { name = s; }