#include <iostream>
#include <string>
#include <cstdlib>
#include "Library.h"
#include "LinkedList.h"
using namespace std;

int main(int arc, char** argv) {

	LinkedList* library = new LinkedList(); //initializes library linked list 

	/*
	string  str = "Robots and turkeys";
	string  str2 = "turk";
	if (!(str.find(str2) == string::npos)) { //string::find and npos found through c++ documentation
		cout << "found it" << endl;			 //sources: https://cplusplus.com/reference/string/string/npos/
											 //https://cplusplus.com/reference/string/string/find/
	}
	else {
		cout << "didn't find it" << endl;
	}
	*/

	string inputString; //initializes inputString
	cout << "Velcoom to libary, plz enter command. type \"HELP\" for list of commands." << endl;

	getline(cin, inputString);

	while (true) {

		//input string will be split into command and argument
		string command = "";
		string argument = "";

		int argumentIndex = 0; //variable to hold starting index of argument in input string

		//finds command
		for (int index = 0; index < inputString.length(); ++index) {
			if (inputString[index] == ' ') {
				argumentIndex = index + 2; //since argument starts after first space of each command, it's index will always be +1 after the space's
				break;
			}
			command += tolower(inputString[index]);
		}
	
		//finds argument
		for (int index = argumentIndex; index < inputString.length()-1; ++index) { //everything after first spacce should be part of the argument
			argument += inputString[index];
		}

		/*
		//converts argument to lower case for case insensitivity
		for (int index = 0; index < argument.length(); ++index) {
			argument[index] = tolower(argument[index]);
		}
		*/

		//cout << library->testComparand() << endl;
		//ran into issue: illegal call of non-static member function, google advised declaring a class object to get around it
		//source: https://stackoverflow.com/questions/9818515/what-does-error-a-nonstatic-member-reference-must-be-relative-to-a-specific-o
		Library librarian;
		librarian.runCommand(command, argument, library);
		
		cout << endl;
		cout << "plz enter command" << endl; //reprompt for command

		getline(cin, inputString);

	}
}