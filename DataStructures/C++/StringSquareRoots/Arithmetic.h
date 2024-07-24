#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Arithmetic {

public:
	static string add(string a, string b);
	static string subtract(string a, string b);
	static void trim(string& a);
	static string multiply(string a, string b);
	static string sqrt(string num); //uses an algorithm made from basic arithmetic to find the square roots of 
									//numbers bigger than the integer limits
	static string* buildFoursArray(int size, string num); //will buid fours array based off num
	static int cmp(string a, string b); //will return 1 if a > b, 0 if a = b, and -1 if a < b
};