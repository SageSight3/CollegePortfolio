#include <iostream>
#include <string>
#include <cstdlib>
#include "Card.h"  //Include Card class since I need it
#include "Deck.h"
using namespace std;

Deck::Deck(int size) {
	
	deckSize = size; //enable deck size to be dynamic
	MyCards = new Card * [size];
	int temp; //placeholder variable for individual card values
	for (int i = 0; i < size; i++) {
		cout << "Please enter the value of card " << i << ": "; //card input
		cin >> temp;
		MyCards[i] = new Card(temp);
	}
	Shuffle();

}

Deck::~Deck() {

	for (int i = 0; i < deckSize; i++)
		delete MyCards[i];
	delete MyCards;
	cout << "I have wiped out the deck!" << endl;
}
void Deck::Shuffle() {

	for (int i = 1; i < deckSize; i++) {
		int r = rand() % (i + 1);
		Card* t = MyCards[i];
		MyCards[i] = MyCards[r];
		MyCards[r] = t;
	}
}

void Deck::print() {
	for (int i = 0; i < deckSize; i++)
		MyCards[i]->print();
}

void Deck::print5() {
	for (int i = 0; i < 5; i++)
		MyCards[i]->print();
}

Card* Deck::getCard(int value) {
	return MyCards[value];
}