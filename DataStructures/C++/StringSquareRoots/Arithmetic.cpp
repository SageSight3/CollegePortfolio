#include <iostream>
#include <string>
#include <cstdlib>
#include "Arithmetic.h"
using namespace std;

string Arithmetic::add(string a, string b) {

	trim(a);
	trim(b);
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	a = "0" + a; //We put an extra zero at the beginning just in case
	b = "0" + b; //we end with a carry
	string ans = "";
	int carry = 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		int sum = (a[i] - '0') + (b[i] - '0') + carry;
		ans = (char)(sum % 10 + '0') + ans;
		carry = sum / 10;
	}
	trim(ans);
	return ans;
}

string Arithmetic::subtract(string a, string b) {

	trim(a);
	trim(b);
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	for (int i = 0; i < b.length(); i++)
		b[i] = (char)('9' - b[i] + '0'); //Finding 9's complement
	string diff = add(add(a, b), "1");

	//tests for negative
	if (diff.length() == b.length()+1) {
		diff = diff.substr(1);
	}
	else {
		string negationPoint = "1"; //the 0 point translated to where it allows for negatives to exist on the positive axis
		for (int index = 0; index < b.length(); ++index) {
			negationPoint += "0"; //translates 0 respective to the digits of diff based off certainties of the algorithm
		}

		diff =  subtract(negationPoint, diff); //converts diff to distance from the translated 0 line

		diff = "-" + diff;
	}
	trim(diff);
	return diff;
}


void Arithmetic::trim(string& a) {  //The & means any change made to a is reflected in the original variable

	while (a.length() > 1 && a[0] == '0') a = a.substr(1);
	//Remember that a.substr(1) is everything in a from position 1 to end.
	//In other words, everything except the character at position 0.
	//Removing the first character of a
}

string Arithmetic::multiply(string a, string b) {

	trim(a);
	trim(b);
	string sum = "0";
	for (int i = 0; i < a.length(); i++)
		for (int j = 0; j < b.length(); j++) {
			int prod = (a[i] - '0') * (b[j] - '0');
			string addend = to_string(prod);
			for (int k = 0; k < a.length() - 1 - i + b.length() - 1 - j; k++)
				addend += "0";
			sum = add(sum, addend);
		}
	return sum;
}


string Arithmetic::sqrt(string num) {
	int foursSize = 1; //fours size is dynamic in case it needs to allocated for more memory
	string* fours = buildFoursArray(foursSize, num);

	int startingIndex = 0;
	while (cmp(fours[startingIndex], num) == -1) {
		//cout << "fours at index " << startingIndex << " is " << fours[startingIndex] << endl;
		startingIndex = startingIndex + 1;

		if (startingIndex > foursSize) { //check for memory shortage and allocation of larger fours array
			string* temp = fours; //holds old fours array for deletion
			foursSize = foursSize * 2;
			fours = buildFoursArray(foursSize, num);
			delete[] temp;
			//cout << "fours at index " << startingIndex << " is " << fours[startingIndex] << endl;
		}
	}

	//cout << "The starting index is " << startingIndex << endl;

	string ans = "0";
	string n = num;

	//for readability
	string addend;
	string subtrahend;

	for (int step = startingIndex; step >= 0; --step) {

		 //subtrahend and addend defined in loop to keep updating each step
		addend = add(multiply("4", ans), "1");
		subtrahend = multiply(fours[step], addend);
		//cout << "fours is " << fours[step] << " and addend is " << addend << endl;

		if (cmp(subtract(n, subtrahend), "0") >= 0) {
			ans = add(multiply("2", ans), "1");
			//cout << n << " - " << subtrahend << " is " << subtract(n, subtrahend) << endl;
			n = subtract(n, subtrahend);
		}
		else {
			ans = multiply("2", ans);
		}
		//cout << "ans is " << ans << endl;
	}

	//cout << "The square root of " << num << " is " << ans << endl;
	//cout << endl;
	delete[] fours;
	return ans;
}

string* Arithmetic::buildFoursArray(int size, string num) {

	string* fours = new string[size*2]; //return array
	fours[0] = "1"; //starting value of fours

	for (int index = 1; index < size * 2; ++index) { //builds array
		fours[index] = multiply(fours[index - 1], "4");

		//checks if fours[index] is larger than num and exits method if so, since that means
		//the array is large enough
		if (cmp(fours[index], num) == 1) {
			return fours;
		}
	}
	return fours;
}


int Arithmetic::cmp(string a, string b) {
	string difference = subtract(a, b); //uses difference between a and b for comparison
	if (difference > "0") {
		return 1;
	} else if (difference == "0") {
		return 0;
	}
	else if (difference[0] == '-') {
		return -1;
	}
}