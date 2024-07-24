#pragma once
//
//  card.h
//  DeckOfCards
//
//  Created by Andrew Poe on 9/14/22.
//

#ifndef card_h
#define card_h

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Card {

private:
    int rank; //A and K
    int suit; //Hearts, Clubs, Diamonds, Spaces
    int value; //A value between 0 and 51 (so the computer can easily identify the card
    string name; //A human-readable name for the card
public:
    Card(int v);
    ~Card();
    void print();
    int getrank(); //accessors or "getters" or "gets"
    int getsuit();
    int getvalue();
    string getname();
    void setrank(int i);//mutators or "setters" or "sets"
    void setsuit(int i);
    void setvalue(int i);
    void setname(string s);
};
#endif /* card_h */