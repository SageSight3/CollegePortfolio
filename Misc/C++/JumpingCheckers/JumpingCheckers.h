#ifndef _JUMPINGCHECKERS_
#define _JUMPINGCHECKERS_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv);

void setBoard(char** board, int rows, int columns);
void setRowSpaces(char* row, string rowTiles, int columns);
char setSpace(int index, string rowTiles); //is unneccessary but helps with legibility
bool canJump(char** board, int row, int col, int totalRows, int totalColumns);


#endif /* JumpingCheckers.h */
