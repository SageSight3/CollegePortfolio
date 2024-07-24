#ifndef _PG3_
#define _PG3_

#include <iostream>
#include <string>
#include <cstdlib>
#include "Maze.h"
using namespace std;

int main(int argc, char** argv);
void buildMaze();
void DisposeMaze();
void PrintMaze(char** M);
int height();
int width();
void Solve();
bool isEnd(char** maze);
void findPos(char** maze);
#endif