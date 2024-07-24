#pragma once

#include <cstdlib>
#include <string>
#include <iostream>
#include "Maze.h"
#include "Queue.h"
#include "QObj.h"
using namespace std;

int moves[][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

Maze::Maze(int colNum, int rowNum) {

	cols = colNum;
	rows = rowNum;

	string empty;
	getline(cin, empty);

	string input;

	maze = new char* [rows];
	for (int row = 0; row < rows; ++row) {
		getline(cin, input);
		maze[row] = new char[cols];
		for (int col = 0; col < cols; ++col) {
			maze[row][col] = input[col];
		}
	}
}

Maze::~Maze() {
	for (int row = 0; row < rows; ++row) {
		delete[] maze[row];
	}
	delete[] maze;
}

bool Maze::isWall(int rowCoord, int colCoord) {
	if (rowCoord < 0 || rowCoord >= rows || colCoord < 0 || colCoord >= cols) {
		return true;
	}
	return maze[rowCoord][colCoord] == '*';
}

bool Maze::isGoal(int rowCoord, int colCoord) {
	return rowCoord == rows && colCoord == cols;
}

int** Maze::getDepthMatrix() {

	int** depthMatrix = new int* [rows];

	for (int row = 0; row < rows; ++row) {
		depthMatrix[row] = new int[cols];
		for (int col = 0; col < cols; ++col) {
			depthMatrix[row][col] = INF;
		}
	}
	depthMatrix[0][0] = 0;

	Queue* solver = new Queue();
	solver->ENQUEUE(0, 0);

	while (!solver->ISEMPTY()) {
		QObj* node = solver->DEQUEUE();

		if (isGoal(node->getr(), node->getc())) {
			return depthMatrix;
		}

		for (int move = 0; move < 4; ++move) {
			int adjr = node->getr() + moves[move][0];
			int adjc = node->getc() + moves[move][1];

			if (isWall(adjr, adjc)) {
				continue;
			}
			
			int currentDepth = depthMatrix[node->getr()][node->getc()];

			if (depthMatrix[adjr][adjc] <= currentDepth+1) { //check against what it would become, because it wouldn't make a difference to recheck that path 
				continue;
			}
			
			depthMatrix[adjr][adjc] = currentDepth + 1;
			solver->ENQUEUE(adjr, adjc);
		}
	}
	return depthMatrix;
}

void Maze::Solve() {
	int** depthMatrix = getDepthMatrix();

	int rowCoord = rows - 1;
	int colCoord = cols - 1;
	int currentDepth = depthMatrix[rows - 1][cols - 1];

	if (currentDepth == INF) {
		cout << "No solution" << endl;
		return;
	}

	maze[0][0] = 'X';
	while (!currentDepth == 0) {
		maze[rowCoord][colCoord] = 'X';

		for (int move = 0; move < 4; ++move) {
			int adjr = rowCoord + moves[move][0];
			int adjc = colCoord + moves[move][1];

			if (isWall(adjr, adjc)) {
				continue;
			}

			if (depthMatrix[adjr][adjc] != currentDepth - 1) {
				continue;
			}

			--currentDepth;
			rowCoord = adjr;
			colCoord = adjc;
			break;
		}
	}

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			cout << maze[row][col];
		}
		cout << endl;
	}

	for (int row = 0; row < rows; ++row) {
		delete[] depthMatrix[row];
	}
	delete[] depthMatrix;
}