#include <cstdlib>
#include <string>
#include <iostream>
#include <bitset>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {

	ifstream fileIn("binary.txt", ios::binary);
	ofstream fileOut("char.txt", ios::binary);

	fileIn.seekg(0, fileIn.end);
	int length = fileIn.tellg();
	fileIn.seekg(0, fileIn.beg);

	char* binaryText = new char[length];
	fileIn.read(binaryText, length);

	int strArrSize = 0;
	for (int biTextIndex = 0; biTextIndex < length; ++biTextIndex) {
		if (binaryText[biTextIndex] == ' ' || binaryText[biTextIndex] == '\r') {
			++strArrSize;
		}
	}
	cout << "strArrSize is " << strArrSize << endl;

	string* biStrings = new string[strArrSize];
	int strIndex = 0;
	string biString = "";
	for (int biTextIndex = 0; biTextIndex < length; ++biTextIndex) {

		if (binaryText[biTextIndex] == ' ' || binaryText[biTextIndex] == '\r' || binaryText[biTextIndex] == '\n') {
			continue;
		}

		biString += binaryText[biTextIndex];
		
		if (biString.length() == 8) {
			biStrings[strIndex] = biString;
			//cout << biStrings[strIndex] << endl;
			++strIndex;
			biString = "";
		}
	}
	cout << "The last binary string of the file is " << biStrings[strArrSize-1] << endl;

	bitset<8>* bitsetArr = new bitset<8>[strArrSize];
	for (int index = 0; index < strArrSize; ++index) {
		bitsetArr[index] = bitset<8>(biStrings[index]);
	}
	cout << "The last bitset in bitsetArr is " << bitsetArr[strArrSize - 1] << endl;
	cout << "The last bitset in bitsetArr's int value is " << (int)bitsetArr[strArrSize - 1].to_ulong() << endl;
	cout << "The last bitset in bitsetArr's char value is " << (char)((int)bitsetArr[strArrSize - 1].to_ulong()) << endl;

	char* biToCharArr = new char[strArrSize];
	for (int index = 0; index < strArrSize; ++index) {
		biToCharArr[index] = (char)((int)bitsetArr[index].to_ulong());
	}
	
	fileOut.write(biToCharArr, strArrSize);

	delete[] biToCharArr;
	delete[] bitsetArr;
	delete[] biStrings;
	delete[] binaryText;
	fileIn.close();
	fileOut.close();
}
