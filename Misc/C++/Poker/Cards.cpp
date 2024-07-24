#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Cards.h"
#include "Card.h"
#include "Deck.h"
#include "PokerHand.h"
using namespace std;

int main(int argc, char** argv) {

	srand(time(NULL));
	{
#ifdef _COMMENT_ // <== Compiler variable
		for (int i = 0; i < 52; i++) {
			Card* c = new Card(i);
			c->print();
		}
#endif
	}

	int sizeInput; //placeholder variable for deck size input until it's in the constructor
	cout << "Please enter the size of your deck: "; //size input
	cin >> sizeInput;

	cout << endl;

	Deck* aDeck = new Deck(sizeInput);
	cout << endl;
	aDeck->print(); 

	cout << endl; //break in console text for prganization

	//card counter
	int* cardCounts = new int[52];
	for (int i = 0; i < 52; ++i) { //sets all card counts to 0 at start
		cardCounts[i] = 0;
	}

	//hand checker

	//hand condition variables
	int singles = 0;
	int pairs = 0;
	int three = 0;
	int four = 0;
	bool straight = false;
	bool flush = false;
	bool royal = false;
	Card* high = new Card(-1);

	for (int i = 0; i < 5; ++i) { //increments the respective card counts from the top 5 cards of deck (the hand)
		cardCounts[aDeck->getCard(i)->getvalue()] = cardCounts[aDeck->getCard(i)->getvalue()] + 1;
	}

	int consecutiveSuit = 1; //tracks back to back suit detections for flush detection
	int prevRank = -1; //stores last card found's rank
	int prevSuit = -1; //stores last card found's suit

	for (int i = 0; i < 52; ++i) {
		if (cardCounts[i] != 0) {
			Card* temp = new Card(i);
			if (i % 13 > high->getrank() && !(high->getrank() == 0)) { //updates high if a new one is found
				high = temp;
			}
			if (temp->getrank() == 0) {
				high = temp;
			}

			if (i / 13 == prevSuit) { //increments consecutiveSuit if matching suits are found back to back
				consecutiveSuit = consecutiveSuit + 1;
			}

			//updates prev rank and suit
			prevRank = i % 13;
			prevSuit = i / 13;
		}
	}

	//multi-card checks
	int* rankCounts = new int[13];
	for (int i = 0; i < 13; ++i) {
		rankCounts[i] = 0;
	}

	for (int i = 0; i < 52; ++i) {
		if (cardCounts[i] != 0) {
			rankCounts[i % 13] = rankCounts[i % 13] + 1;
		}
	}

	for (int i = 0; i < 13; ++i) {
		//card count updates
		if (rankCounts[i] == 1) {
			singles = singles + 1;
		}
		if (rankCounts[i] == 2) {
			pairs = pairs + 1;
		}
		if (rankCounts[i] == 3) {
			three = three + 1;
		}
		if (rankCounts[i] == 4) {
			four = four + 1;
		}

	}


	//straight detection
	if (singles == 5) {
		int totalDiff = 0; //math for straight solution
		for (int i = 0; i < 5; ++i) {
			if (!(high->getrank() == aDeck->getCard(i)->getrank())) {
				totalDiff = totalDiff + (high->getrank() - aDeck->getCard(i)->getrank());
			}
		}
		if (totalDiff == 10) {
			straight = true;
		}
		totalDiff = 0;
		if (straight == false && high->getrank() == 0) { //high ace check
			for (int i = 0; i < 5; ++i) {
				if (!(aDeck->getCard(i)->getrank() == 0)) {
					totalDiff = totalDiff + (13 - aDeck->getCard(i)->getrank());
				}
			}
		}
		if (totalDiff == 10) {
			straight = true;
			royal = true;
		}
		totalDiff = 0;
		if (straight == false && high->getrank() == 0) { //low ace check
			for (int i = 0; i < 5; ++i) {
				if (!(aDeck->getCard(i)->getrank() == 4)) {
					totalDiff = totalDiff + (4 - aDeck->getCard(i)->getrank());
				}
			}
		}
		if (totalDiff == 10) {
			straight = true;
		}
	}

	//flush detection
	if (consecutiveSuit >= 5) {
		flush = true;
	}

	//hand detection

	if (straight && flush && royal) {
		cout << "You have a Royal Flush" << endl;
		return 0;
	}
	if (straight && flush) {
		cout << "You have a Straight Flush" << endl;
		return 0;
	}
	if (four >= 1) {
		cout << "You have a Four of a Kind" << endl;
		return 0;
	}
	if (three >= 1 && pairs >= 1) {
		cout << "You have a Full House" << endl;
		return 0;
	}
	if (flush) {
		cout << "You have a Flush" << endl;
		return 0;
	}
	if (straight) {
		cout << "You have a Straight" << endl;
		return 0;
	}
	if (three >= 1) {
		cout << "You have a Three of a Kind" << endl;
		return 0;
	}
	if (pairs == 2) {
		cout << "You have a Two Pair" << endl;
		return 0;
	}
	if (pairs == 1) {
		cout << "You have a Pair" << endl;
		return 0;
	}
	if (high->getrank() == 0) { //seperate condition for ace and eight for grammar and ace rank < 7
		cout << "You have an Ace High" << endl;
		return 0;
	} else if (high->getrank() == 7) {
		cout << "You have an Eight High" << endl;
		return 0;
	} else if (high->getrank() > 6) {

		//gets card name
		string rank = "";
		bool spaceNotFound = true;
		int index = 0;
		while (spaceNotFound) {
			rank += high->getname()[index];
			if (high->getname()[index] == ' ') {
				spaceNotFound = false;
			}
			index = index + 1;
		}

		//sets letters after first to lowercase for appearence
		for (int i = 1; i < rank.length(); ++i) {
			rank[i] = tolower(rank[i]);
		}

		cout << "You have a " << rank << "High" << endl;
		return 0;
	}

	cout << "You have nothing" << endl;

	/*
	PokerHand* aHand = new PokerHand(aDeck);
	aHand->printHand();
	
	cout << endl;
	
	aHand->checkHand();

	cout << endl;
	*/

	delete aDeck;  //delete calls the destructor and then deallocates.
	delete [] cardCounts;
	delete[] rankCounts;
	delete high;
	//delete aHand;
	return 0;
}