#include <iostream>
#include <string>
#include <cstdlib>
#include "Card.h" //will be needed
#include "Deck.h"
#include "PokerHand.h"
using namespace std;


//hand constructor
PokerHand::PokerHand(Deck* deck) {

	hand = new Card* [5];
	dynamicHand = new Card * [5];

	//shuffles the deck before hand is dealt, for the purposes of the assigment, this will randomize
	//the card draws
	deck->Shuffle(); 

	int cardValue; //placeholder variable for the card value at deck[draw]

	for (int draw = 0; draw < 5; ++draw) { //5 iteration loop because the hand is only 5 cards

		cardValue = deck->getCard(draw)->getvalue(); //gets the card value for the drawn card
		hand[draw] = new Card(cardValue); //sets each card in hand to a card "drawn" from the deck

		dynamicHand[draw] = new Card(cardValue); //sets each card in dynamicHand to a card "drawn" from the deck

		/*
		I ran into some deallocation issues originally when I had the code as
		hand[draw] = deck->getCard(draw);
		My guess is that this happened because I didn't initialize hand[draw] with new, so I believe
		it may have been lost out of scope. Though, I'm not fully sure.
		All in all, treating hand[draw] like a copy of the drawn card seems to have resolved the issue. It just
		means more deallocation and memory usage, from I can tell/infer.
		*/
	}
}

//destructor
PokerHand::~PokerHand() {

	for (int card = 0; card < 5; ++card) {
		delete hand[card];
		//cout << "card " << card << " is gone" << endl; //for bugfixing purposes
	}
	delete hand;
	cout << "hand has been deleted" << endl;


	for (int card = 0; card < 5; ++card) {
		delete dynamicHand[card];
		//cout << "card " << card << " is gone" << endl; //for bugfixing purposes
	}
	delete dynamicHand;
	cout << "dynamicHand has been deleted" << endl;
}

void PokerHand::printHand() {
	for (int card = 0; card < 5; ++card) {
		hand[card]->print();
	}
}

void PokerHand::printDynamicHand() {
	for (int card = 0; card < 5; ++card) {
		dynamicHand[card]->print();
	}
}

void PokerHand::resetDynamicHand() {
	for (int card = 0; card < 5; ++card) {
		dynamicHand[card]->setvalue(hand[card]->getvalue());
	}
}

bool PokerHand::royalFlush() {

	resetDynamicHand();

	//check for striaght
	
	//identifies whether a straightflush is royal by if the hand has an ace in it, as well, because if it does, and
	//it's straight and flush, it's royal, as an ace can only be in a straight when it's with the other royal flush
	//cards
	bool royal = false; 
	//sets aces' ranks to 13, as it simplifies the code for how the code identifies straights
	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() == 0) {
			dynamicHand[card]->setrank(13);
			royal = true;
		}
	}

	int highest = -1;
	for (int card = 0; card < 5; ++card) { //gets highest rank card of hand
		if (dynamicHand[card]->getrank() > highest) {
			highest = dynamicHand[card]->getrank();
		}
	}

	int totalCardDifference = 0;
	for (int card = 0; card < 5; ++card) { //gets the sum of differences of highest and the other cards in the hand
		if (!(highest == dynamicHand[card]->getrank())) {
			totalCardDifference = totalCardDifference + (highest - dynamicHand[card]->getrank());
		}
	}

	//checks for reapeating cards
	bool repeatCards = false;
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {
				repeatCards = true;
			}
		}
	}

	bool isStraight = false; //bolean for whether the hand is a straight
	if ((totalCardDifference == 10) && !(repeatCards)) { //checks that the sum is right, and that there were no repeating cards
		isStraight = true;
	}

	//check for flush

	bool isFlush = false; //boolean for whether the hand is a flush
	int suit = dynamicHand[0]->getsuit();
	for (int card = 0; card < 5; ++card) { //checks to see if all cards share the same suit
		if (!(dynamicHand[card]->getsuit() == suit)) {
			return false;
		}
	}

	isFlush = true;

	//check for straight and flush
	if (isStraight && isFlush) {
		for (int card = 0; card < 5; ++card) {
			//checks to see if there's an ace in the hand, becuase if there is and the hand's a straightflush, it's automatically royal
			if (royal) {
				cout << "You have a royal flush" << endl;
				return true;
			}
		}
	}

	return false;
}

bool PokerHand::straightFlush() {

	resetDynamicHand();

	//check for striaght

	//sets aces' ranks to 13, as it simplifies the code for how the code identifies straights
	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() == 0) {
			dynamicHand[card]->setrank(13);
		}
	}

	int highest = -1;
	for (int card = 0; card < 5; ++card) { //gets highest rank card of hand
		if (dynamicHand[card]->getrank() > highest) {
			highest = dynamicHand[card]->getrank();
		}
	}

	int totalCardDifference = 0;
	for (int card = 0; card < 5; ++card) { //gets the sum of differences of highest and the other cards in the hand
		if (!(highest == dynamicHand[card]->getrank())) {
			totalCardDifference = totalCardDifference + (highest - dynamicHand[card]->getrank());
		}
	}

	//checks for reapeating cards
	bool repeatCards = false;
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {
				repeatCards = true;
			}
		}
	}

	//sets aces rank back to 0, to check for lower straights
	if (!(totalCardDifference == 10) && !(repeatCards)) {
		for (int card = 0; card < 5; ++card) {
			if (dynamicHand[card]->getrank() == 13) {
				dynamicHand[card]->setrank(0);
			}
		}

		totalCardDifference = 0;
			for (int card = 0; card < 5; ++card) { //gets the sum of differences of highest and the other cards in the hand
				if (!(highest == dynamicHand[card]->getrank())) {
					totalCardDifference = totalCardDifference + (highest - dynamicHand[card]->getrank());
				}
			}
	}

	bool isStraight = false; //bolean for whether the hand is a straight
	if ((totalCardDifference == 10) && !(repeatCards)) { //checks that the sum is right, and that there were no repeating cards
		isStraight = true;
	}
	
	//check for flush

	bool isFlush = false; //boolean for whether the hand is a flush
	int suit = dynamicHand[0]->getsuit();
	for (int card = 0; card < 5; ++card) { //checks to see if all cards share the same suit
		if (!(dynamicHand[card]->getsuit() == suit)) {
			return false;
		}
	}

	isFlush = true;

	//check for straight and flush
	if (isStraight && isFlush) {
		cout << "You have a straight flush" << endl;
		return true;
	}

	return false;
}

//checks for a four of a kind
bool PokerHand::fourOfAKind() {

	resetDynamicHand();

	int targetRank = -10; //initialized a var to hold the rank of a pair to be compared to the other cards, if one's found 

	//nested four loop to check all cards in the hand against each other
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {
				targetRank = dynamicHand[card1]->getrank(); //sets rank being searched for in next loop

				//changes ranks of first pair so program doesn't mistake one of them as the third card in a three of a kind
				dynamicHand[card1]->setrank(-1);
				dynamicHand[card2]->setrank(-2);
				break;
			}
		}
		if (dynamicHand[card1]->getrank() == -1) {
			break;
		}
	}

	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() == targetRank) {
			dynamicHand[card]->setrank(-3); //sets third found match to -3 so the program doesn't count it twice
			for (int otherCountCard = 0; otherCountCard < 5; ++otherCountCard) {
				if (dynamicHand[otherCountCard]->getrank() == targetRank) {
					cout << "You have a four of a kind" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

//checks for a full house
bool PokerHand::fullHouse() {

	resetDynamicHand();

	int pairRank1 = -11; //initialized a var to hold the rank of a pair to be compared to the other cards, if one's found

	//nested four loop to check all cards in the hand against each other
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {

				pairRank1 = dynamicHand[card1]->getrank();

				//sets the pair to impossible values so they can't be mistaken as part of a potential three of a kind
				dynamicHand[card1]->setrank(-1);
				dynamicHand[card2]->setrank(-2);
				break;
			}
		}
		if (dynamicHand[card1]->getrank() == -1) {
			break;
		}
	}

	int pairRank2 = -10; //for measuring against shoud first three of a kind check fail 

	//nested four loop to check all cards in the hand against each other
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {
				pairRank2 = dynamicHand[card1]->getrank(); //sets rank being searched for in next loop

				//changes ranks of the next pair so program doesn't mistake one of them as the third card in the three of a kind
				dynamicHand[card1]->setrank(-3);
				dynamicHand[card2]->setrank(-4);
				break;
			}
		}
		if (dynamicHand[card1]->getrank() == -3) {
			break;
		}
	}

	
	//With how the function alters dynamicHand, it makes it so that if all cards in it have negative ranks, there's a full house
	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() == pairRank1) {
			dynamicHand[card]->setrank(-5);
			if (fullHouseLoopCheck()) {
				cout << "You have a full house" << endl;
				return true;
			}
		}
	}

	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() == pairRank2) {
			dynamicHand[card]->setrank(-5);
			if (fullHouseLoopCheck()) {
				cout << "You have a full house" << endl;
				return true;
			}
		}
	}

	return false;
}

//function for checking hand state at end of fullHouse()
bool PokerHand::fullHouseLoopCheck() {

	//checks to see if all cards in dynamicHand have a negative rank;

	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() >= 0) { 
			return false;
		}
	}
	return true;
}

//checks for a flush
bool PokerHand::flush() {

	resetDynamicHand();

	int suit = dynamicHand[0]->getsuit();
	for (int card = 0; card < 5; ++card) { //checks to see if all cards share the same suit
		if (!(dynamicHand[card]->getsuit() == suit)) {
			return false;
		}
	}

	cout << "You have a flush" << endl;
	return true;
}

//checks for a straight
bool PokerHand::straight() {

	resetDynamicHand();

	//the function works based on the fact that the total sum of the differences between all other cards in a hand and the largest
	//will always be 10 if there's a straight, and a straight can have no repeating cards

	//sets aces' ranks to 13, as it simplifies the code for how the code identifies straights
	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() == 0) {
			dynamicHand[card]->setrank(13);
		}
	}

	int highest = -1;
	for (int card = 0; card < 5; ++card) { //gets highest rank card of hand
		if (dynamicHand[card]->getrank() > highest) {
			highest = dynamicHand[card]->getrank();
		}
	}

	int totalCardDifference = 0;
	for (int card = 0; card < 5; ++card) { //gets the sum of differences of highest and the other cards in the hand
		if (!(highest == dynamicHand[card]->getrank())) {
			totalCardDifference = totalCardDifference + (highest - dynamicHand[card]->getrank());
		}
	}

	//checks for reapeating cards
	bool repeatCards = false;
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {
				repeatCards = true;
			}
		}
	}

	//sets aces rank back to 0, to check for lower straights
	if (!(totalCardDifference == 10) && !(repeatCards)) {
		for (int card = 0; card < 5; ++card) {
			if (dynamicHand[card]->getrank() == 13) {
				dynamicHand[card]->setrank(0);
			}
		}

		totalCardDifference = 0;
		for (int card = 0; card < 5; ++card) { //gets the sum of differences of highest and the other cards in the hand
			if (!(highest == dynamicHand[card]->getrank())) {
				totalCardDifference = totalCardDifference + (highest - dynamicHand[card]->getrank());
			}
		}
	}

	if ((totalCardDifference == 10) && !(repeatCards)) { //checks that the sum is right, and that there were no repeating cards
		cout << "You have a straight" << endl;
		return true;
	}

	return false;
}

//checks for a three of a kind
bool PokerHand::threeOfAKind() {

	resetDynamicHand();

	int pairRank1 = -11; //initialized a var to hold the rank of a pair to be compared to the other cards, if one's found

//nested four loop to check all cards in the hand against each other
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {

				pairRank1 = dynamicHand[card1]->getrank();

				//sets the pair to impossible values so they can't be mistaken as part of a potential three of a kind
				dynamicHand[card1]->setrank(-1);
				dynamicHand[card2]->setrank(-2);
				break;
			}
		}
		if (dynamicHand[card1]->getrank() == -1) {
			break;
		}
	}

	int pairRank2 = -10; //for measuring against shoud first three of a kind check fail 

	//nested four loop to check all cards in the hand against each other
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) { //<-- problem line
				pairRank2 = dynamicHand[card1]->getrank(); //sets rank being searched for in next loop

				//changes ranks of the next pair so program doesn't mistake one of them as the third card in a three of a kind
				dynamicHand[card1]->setrank(-3);
				dynamicHand[card2]->setrank(-4);
				break;
			}
		}
		if (dynamicHand[card1]->getrank() == -1) {
			break;
		}
	}

	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() == pairRank1) {
			cout << "You have a three of a kind" << endl;
			return true;
		}
	}
	
	for (int card = 0; card < 5; ++card) {
		if (dynamicHand[card]->getrank() == pairRank2) {
			cout << "You have a three of a kind" << endl;
			return true;
		}
	}
	

	return false;
}

//checks for two pairs
bool PokerHand::twoPair() {

	resetDynamicHand();

	//finds first pair
	//nested four loop to check all cards in the hand against each other
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {

				//sets the first pair to impossible ranks so that the program doesn't mistake them as part of a second pair
				dynamicHand[card1]->setrank(-1);
				dynamicHand[card2]->setrank(-2);
				break;
			}
		}
		if (dynamicHand[card1]->getrank() == -1) {
			break;
		}
	}

	for (int card1 = 4; card1 > 0; --card1) { 
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {
				cout << "You have two pairs" << endl;
				return true;
			}
		}
	}

	return false;
}

//checks for a pair
bool PokerHand::pair() {

	resetDynamicHand();

	//nested four loop to check all cards in the hand against each other
	for (int card1 = 4; card1 > 0; --card1) { //will go through cards from last to first
		//checks cards against another until the next check would be against itself or a card it would've already been checked against
		for (int card2 = 0; card2 < card1; ++card2) {
			if (dynamicHand[card1]->getrank() == dynamicHand[card2]->getrank()) {
				cout << "You have a pair." << endl;
				return true;
			}
		}
	}

	return false;
}

//checks if there's a card high
bool PokerHand::cardHigh() { //will cover all card high cases

	resetDynamicHand();

	Card* highest = dynamicHand[0]; //variable to hold highest value card in the hand

	for (int card = 0; card < 5; ++card) {
		//cout << hand[card]->getrank() << endl; //for bugfixing purposes
		if (!(card - 1 < 0) && !(highest->getrank() == 0)) { //prevents comparison operator from going out of bounds

			//compares the rank of the current card and previous
			if ((dynamicHand[card]->getrank() >= dynamicHand[card - 1]->getrank()) || (dynamicHand[card]->getrank() == 0)) { 
				highest = dynamicHand[card]; //if current card has the higher rank, highest becomes it
			}
		}
	}

	if (highest->getrank() == 0) {
		cout << "You have an Ace high." << endl;
		return true;
	}

	if (highest->getrank() == 6) {
		cout << "You have a seven high." << endl;
		return true;
	}

	if (highest->getrank() == 7) {
		cout << "You have an eight high." << endl;
		return true;
	}

	if (highest->getrank() == 8) {
		cout << "You have a nine high." << endl;
		return true;
	}

	if (highest->getrank() == 9) {
		cout << "You have a ten high." << endl;
		return true;
	}

	if (highest->getrank() == 10) {
		cout << "You have a Jack high." << endl;
		return true;
	}

	if (highest->getrank() == 11) {
		cout << "You have a Queen high." << endl;
		return true;
	}

	if (highest->getrank() == 12) {
		cout << "You have a King high." << endl;
		return true;
	}

	return false;
}

void PokerHand::checkHand() {
	if (royalFlush()) { 
		return; 
	} else if (straightFlush()) { 
		return;
	} else if (flush()) {
		return; 
	} else if (straight()) { 
		return; 
	} else if (fourOfAKind()) { 
		return;
	} else if (fullHouse()) { 
		return; 
	} else if (threeOfAKind()) {
		return; 
	} else if (twoPair()) {
		return; 
	} else if (pair()) { 
		return; 
	} else if (cardHigh()) { 
		return; 
	} else {
		cout << "You have nothing" << endl;
	}
}