#include <cstdlib>
#include <string>
#include <iostream>
#include <bitset>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {

	ifstream fileIn("imageAsText.txt", ios::binary);
	ofstream fileOut("imageInBinary.txt", ios::binary);

	fileIn.seekg(0, fileIn.end);
	int length = fileIn.tellg();
	fileIn.seekg(0, fileIn.beg);

	char* fileInChar = new char[length];
	fileIn.read(fileInChar, length);
	cout << "The last char in fileInChar is " << fileInChar[length - 1] << endl;

	bitset<8>* fileBitset = new bitset<8>[length];
	string* fileBinary = new string[length];
	cout << "length = " << length << endl;

	for (int index = 0; index < length; ++index) {

		bitset <8> temp(fileInChar[index]);
		fileBitset[index] = temp;

		/*
		fileBinary[index] = temp.to_string();
		fileBinary[index] += " ";
		*/
	}

	for (int index = 0; index < length; ++index) {
		fileBinary[index] = fileBitset[index].to_string();
		fileBinary[index] += " ";
	}

	int element = 1;
	for (int i = 0; i < length; ++i) {
		if (element == 8) {
			fileBinary[i][8] = '\r';
			fileBinary[i] += '\n';
			element = 0;
		}
		fileOut.write(fileBinary[i].c_str(), fileBinary[i].length());
		++element;
	}

	ofstream didItWork("backtochar.txt", ios::binary);

	char* fileOutChar = new char[length];

	for (int index = 0; index < length; ++index) {
		fileOutChar[index] = (char)((int)(fileBitset[index].to_ulong()));
	}

	didItWork.write(fileOutChar, length);

	delete[] fileOutChar;
	delete[] fileBitset;
	delete[] fileBinary;
	delete[] fileInChar;
	fileIn.close();
	fileOut.close();
	didItWork.close();
}
