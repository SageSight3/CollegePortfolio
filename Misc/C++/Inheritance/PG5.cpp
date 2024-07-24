#include <iostream>
#include <string>
#include <cstdlib>
#include "Comparable.h"
#include "ComparableArray.h"
#include "ComparableInt.h"
#include "ComparableString.h"
using namespace std;

int main(int argc, char** argv) {

	//int code

	ComparableArray* compIntArray; //initializes array
	int size; //CA size

	cout << "How many integers? "; //size input
	cin >> size;

	compIntArray = new ComparableArray(size); //constructor call

	int intInput; //initialized int input var

	for (int i = 0; i < size; ++i) { //gets input for each int in array
		cout << "Enter an integer: ";
		cin >> intInput;
		ComparableInt* cmpIntInput = new ComparableInt(intInput); //initializes ComparableInt from intInput
		compIntArray->seti(i, cmpIntInput); //adds cmpIntInput to the array
	}

	//console output
	cout << "The largest integer is "; 
	compIntArray->largest()->print();
	cout << " and the smallest is ";
	compIntArray->smallest()->print();

	delete compIntArray; //deallocates compIntArrray since it isn't being used again

	cout << endl; //space for console organization

	//string code

	ComparableArray* compStringArray; //initializes array

	cout << "How many strings? "; 
	cin >> size; //size input

	compStringArray = new ComparableArray(size); //constructor call

	string stringInput; //initialized int input var

	//prevents issues with getline
	string empty;
	getline(cin, empty);

	for (int i = 0; i < size; ++i) { //gets input for each int in array
		cout << "Enter a string: ";
		getline(cin, stringInput);
		ComparableString* cmpStringInput = new ComparableString(stringInput); //initializes ComparableString from stringInput
		compStringArray->seti(i, cmpStringInput); //adds cmpStringInput to the array
	}

	//console output
	cout << "The largest string is ";
	compStringArray->largest()->print();
	cout << " and the smallest is ";
	compStringArray->smallest()->print();

	delete compStringArray;
}