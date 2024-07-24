#include <iostream>
#include <string>
#include <cstdlib>
#include "PG3.h"
#include "Queue.h"
#include "Maze.h"
using namespace std;

int main(int argc, char** argv) {

	int rows;
	cout << "What's the maze's width? ";
	cin >> rows;

	int cols;
	cout << "What's the maze's height? ";
	cin >> cols;

	cout << "Enter a maze below" << endl;

	Maze* maze = new Maze(rows, cols);

	maze->Solve();

	delete maze;
}