#pragma once

#include <cstdlib>
#include <string>
#include <iostream>
#include "Queue.h"
using namespace std;

#define INF INT_MAX //define learned from tutor

class Maze {
	
private:
	char** maze;
	int rows;
	int cols;

	int** getDepthMatrix(); //returns depth matrix with path
public:
	Maze(int rowNum, int colNum);
	~Maze();
	bool isWall(int rowCoord, int colCoord); //returns true if tile is a wall
	bool isGoal(int rowCoord, int colCoord); //returns true if end of maze
	void Solve(); //parent maze solver
};

