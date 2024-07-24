#pragma once
#ifndef _DECK_
#define _DECK_

#include <iostream>
#include <string>
#include <cstdlib>
#include "Card.h"  //Include Card class since I need it
using namespace std;

class Card;  //Prototype the Card class since I need it <-- why does it need to be prototyped past the include?
class Deck {

private:
	Card** MyCards; //MyCards is an array of card pointers
	int deckSize;
public:
	Deck(int size);
	~Deck(); //destructor:  get rid of memory leaks
	void Shuffle();
	void print();
	void print5();
	Card* getCard(int value);
};

#endif

