#include <iostream>
#include <string>
#include <cstdlib>
#include "Card.h"
#include "Deck.h" //will be needed for PokerHand's constructor's parameter
using namespace std;

/*
I was unsure the extent you wanted us to use the classes made in class, so I added
and modified them where needed to meet the needs of the program, check Deck and Cards
I also commented out the print statement in Card's destructor for console organization
*/

class Deck;
class Card;
class PokerHand { //us responsible for dealing the hand and seeing what it has

private:

	Card** hand; //will hold array of cards in the hand
	Card** dynamicHand; //can be altered for some checks without affecting real hand and being easy to reset for other checks

public:
	PokerHand(Deck* deck);
	~PokerHand();
	void resetDynamicHand();
	void printHand();
	void printDynamicHand();
	void checkHand(); //parent method running all hand type checks

	/*
	individual case checks

	checkHand will avoid returning multiple cases based
	off case check order in the function

	will attempt to use different case checks to help define others where it can be done
	ex. Full house will check for a three of a kind, which if it finds, will then check for a two pair
	in the remaining cards
	*/
	bool royalFlush();
	bool straightFlush();
	bool fourOfAKind();
	bool fullHouse();
	bool fullHouseLoopCheck();
	bool flush();
	bool straight();
	bool threeOfAKind();
	bool twoPair();
	bool pair();
	bool cardHigh();
};