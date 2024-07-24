#include <iostream>
#include <string>
#include <cstdlib>
#include "JumpingCheckers.h"
using namespace std;

int main(int argc, char** argv) {

	int rows; //row input
	cout << "How many rows does your checker board have? ";
	cin >> rows;

	int columns; //columns input
	cout << "How many columns does it have? ";
	cin >> columns;
	
	char** board = new char* [rows]; //initializes rows for board array, note: parent array for the board array is the row array

	for (int row = 0; row < rows; ++row) { //initializes a column array for each row
		board[row] = new char[columns];
	}

	setBoard(board, rows, columns); //sets an entered board to the array

	cout << "" << endl; //spacing for organization

	int testRow; //initializes test row coord for canJump
	cout << "Enter a row coordinate: ";
	cin >> testRow; //sets testRow to input

	int testCol; //initializes test column coord for canJump
	cout << "Enter a column coordinate: "; 
	cin >> testCol;//sets testCol to input

	cout << "" << endl; //spacing for organization

	//checks if the piece at that coordinate can make a legal jump and prints result
	if (canJump(board, testRow, testCol, rows, columns)) {
		cout << "The piece at coordinate " << testRow << ", " << testCol << " can legally jump." << endl;
	}
	else {
		cout << "The piece at coordinate " << testRow << ", " << testCol << " cannot legally jump." << endl;
	}

	for (int row = 0; row < rows; ++row) { //deletes column arrays from the board array
		delete[] board[row]; 
	}

	delete[] board; //deletes row array

	return 0;
}

//parent method for setting the characters of the board to their respective array indices
void setBoard(char** board, int rows, int columns) {
	cout << "Enter your board state below:" << endl;
	cout << "" << endl;

	string empty;
	getline(cin, empty);

	for (int row = 0; row < rows; ++row) {
		string rowChars; //initializes temporary string to hold each row
		getline(cin, rowChars); //scans input into rowChars

		setRowSpaces(board[row], rowChars, columns);
	}
	
}

//reads through a string and assigns each of its characters to an element of a row array
void setRowSpaces(char* row, string rowTiles, int columns) {

	for (int col = 0; col < columns; ++col) {
		row[col] = setSpace(col, rowTiles);
	}

}

//used to set an array element to a char value
char setSpace(int index, string rowTiles) {
	return rowTiles[index];
}

//checks if a piece on a certain square can make a legal jump
bool canJump(char** board, int row, int col, int totalRows, int totalColumns) {

	//checks square on transformation row + 1, col + 1
	//checks if the target space is on the board
	if (!(row + 2 < 0) && !(row + 2 >= totalRows) && !(col + 2 < 0) && !(col + 2 >= totalColumns)) {

		//checks to see if there's a valid piece that can be jumped
		if (!(board[row][col] == board[row + 1][col + 1]) && !(board[row + 1][col + 1] == ' ')) {

			//checks to see if there's a an open square for the piece being tested to land on
			if (board[row + 2][col + 2] == ' ') {
				return true;
			}
		}
	}

	//checks square on transformation row + 1, col - 1
	if (!(row + 2 < 0) && !(row + 2 >= totalRows) && !(col - 2 < 0) && !(col - 2 >= totalColumns)) {
		if (!(board[row][col] == board[row + 1][col - 1]) && !(board[row + 1][col - 1] == ' ')) {
			if (board[row + 2][col - 2] == ' ') {
				return true;
			}
		}
	}

	//checks square on transformation row - 1, col + 1
	if (!(row - 2 < 0) && !(row - 2 >= totalRows) && !(col + 2 < 0) && !(col + 2 >= totalColumns)) {
		if (!(board[row][col] == board[row - 1][col + 1]) && !(board[row - 1][col + 1] == ' ')) {
			if (board[row - 2][col + 2] == ' ') {
				return true;
			}
		}
	}

	//checks square on transformation row - 1, col - 1
	if (!(row - 2 < 0) && !(row - 2 >= totalRows) && !(col - 2 < 0) && !(col - 2 >= totalColumns)) {
		if (!(board[row][col] == board[row - 1][col - 1]) && !(board[row - 1][col - 1] == ' ')) {
			if (board[row - 2][col - 2] == ' ') {
				return true;
			}
		}
	}

	return false;
}