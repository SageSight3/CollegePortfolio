//Sage Anbar
//This program will request a list of strings and tehn sort them through insertion sort

//main and input for list
#include <string>
#include <cstdlib>
#include <iostream>
#include "LLMain.h";

using namespace std;

int main(int argc, char** argv) {
	
	LL* list = new LL();
	string input = "3";

	while (!(input == "")) {
		cout << "What's a word you want in the list? " << endl;
		getline(cin, input);

		if (!(input == "")) {
			list->addFront(input);
		}
	}

	list->insertionSort();
	list->print();

	delete list;


}
