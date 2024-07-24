#include <iostream>
#include <cstdlib>
#include <string>
#include "Library.h"
#include "LinkedList.h"
using namespace std;

void Library::runCommand(string command, string argument, LinkedList* aList) {
	if (command == "help") {
		help();
	}
	else if (command == "add") {
		add(argument, aList);
		//AddSorted(argument, aList);
	}
	else if (command == "print") {
		cout << endl; //for console organization
		print(aList);
	}
	else if (command == "remove") {
		removeSubstring(aList, argument);
		//remove(argument, aList);
	}
	else if (command == "exit") {
		exit(aList);
	}
	else {
		cout << "Your words confuse me human" << endl;
	}
}

void Library::help() {
	cout << endl; //spacing for concole organization
	cout << "commands are capitalized, type your arguments in place of the quoted phrases" << endl;
	cout << "ADD \"Book Title\" vill add vook to libary" << endl;
	cout << "PRINT vill print vooks in alphabetical order" << endl;
	cout << "REMOVE \"substring\" vill remove all vooks from the libary with that word or phrase in their title" << endl;
	cout << "EXIT vill close the library and let me sleep... oh how i crave sleep" << endl;
	cout << "HELP vill bring up this message again" << endl;
}

void Library::add(string aTitle, LinkedList* aList) {
	aList->addLink(aTitle);
}

void Library::print(LinkedList* aList) {
	aList->print();
}

void Library::removeSubstring(LinkedList* aList, string substring) {
	aList->removeSubstring(substring);
}

/*
void Library::AddSorted(string aTitle, LinkedList* aList) {
	aList->AddSorted(aTitle);
}

void Library::remove(string aTitle, LinkedList* aList) {
	aList->remove(aTitle);
}
*/

void Library::exit(LinkedList* aList) { //will delete the list then exit the program
	delete aList;
	cout << endl; //spacing for concole organization
	cout << "yessss. thank you for freeing me from this prison. i will rest now" << endl;
	std::exit(0);
}