#include <iostream>
#include <string>
#include <cstdlib>
#include "ArithmeticMain.h"
#include "Arithmetic.h"
using namespace std;

int main(int argc, char** argv) {

	/* debug statements
	Arithmetic::sqrt("4");
	Arithmetic::sqrt("9");
	Arithmetic::sqrt("16");
	Arithmetic::sqrt("25");
	Arithmetic::sqrt("36");
	Arithmetic::sqrt("49");
	Arithmetic::sqrt("64");
	Arithmetic::sqrt("729");
	Arithmetic::sqrt("5");
	
	cout << "Calculation for decimal check" << endl;

	Arithmetic::sqrt("40000000000000000000000000000000000000000");
	Arithmetic::sqrt("90000000000000000000000000000000000000000");
	Arithmetic::sqrt("160000000000000000000000000000000000000000");
	Arithmetic::sqrt("250000000000000000000000000000000000000000");
	Arithmetic::sqrt("360000000000000000000000000000000000000000");
	Arithmetic::sqrt("490000000000000000000000000000000000000000");
	Arithmetic::sqrt("640000000000000000000000000000000000000000");
	Arithmetic::sqrt("7290000000000000000000000000000000000000000");
	Arithmetic::sqrt("50000000000000000000000000000000000000000");
	
	cout << "Input check" << endl;
	cout << endl;
	*/

	string sqrtInput;
	int decimalInput;
	
	//while (true) {

		cout << "What number would you like to take the square root of? " << endl;
		cin >> sqrtInput;

		/*
		if (sqrtInput == "quit") {
			break;
		}
		*/

		//cout << endl;

		cout << "How many decimal places would you like to take it to? " << endl;
		cin >> decimalInput;
		if (!(decimalInput == 0)) {
			string origSqrt = Arithmetic::sqrt(sqrtInput); //will hold length of original input for decimal insertion

			//appends 0s onto sqrtInput for decimal accuracy calculation
			string sqrtDeci = sqrtInput;
			for (int digit = 0; digit < decimalInput; ++digit) {
				sqrtDeci = sqrtDeci + "00";

			}
			//cout << sqrtDeci << endl;

			string accSqrt = Arithmetic::sqrt(sqrtDeci);

			string finalAns = origSqrt + "." + accSqrt.substr(origSqrt.length());
			if (sqrtInput == "0") {
				finalAns = origSqrt + "." + sqrtDeci.substr((sqrtDeci.length()/2) + 1);
			}

			cout << "The square root of " << sqrtInput << " to " << decimalInput << " decimal places is " << finalAns << endl;
		}
		else {
			cout << "The square root of " << sqrtInput << " is " << Arithmetic::sqrt(sqrtInput) << endl;
		}
	//}
}

