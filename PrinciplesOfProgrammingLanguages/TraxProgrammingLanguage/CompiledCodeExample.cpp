#include <iostream>

//variables

int x;
int y;
int z;
std::string msg;
bool success;
std::string reply;

//methods

bool _opTest(int num, int d, int a) {
	bool opTest;
	//variables

	int sum;
	int product;
	int quotient;
	int difference;
	int fraction;
	int group;

	//body
	sum = num + d;
	difference = sum - num;
	quotient = difference / sum;
	product = a * d;
	fraction = sum % product;
	group = a * d + num / a - ((d * num) / a) % (product - sum - quotient % product);
	if ((sum < d)) {
		std::cout << fraction;
	}
	if (((sum < d) && (d > product))) {
		std::cout << "fly";
	}
	if (((sum - num) == d)) {
		std::cout << msg;
	}
	if (((reply > msg) || (group > fraction))) {
		std::cout << reply;
	}
	if ((((sum == group) && (group + 6 < product)) || (((group + 6) == difference) && (difference > sum)))) {
		opTest = true;
	}
	else {
		opTest = false;
	}
	//end of body

	return opTest;
}

int main(int argc, char* argv[]) {
	//body
	x = 7;
	y = 9;
	z = 22;
	msg = "u smel";
	reply = "no u";
	success = _opTest(x, y, z);
	if ((!(success))) {
		std::cout << "howdy";
	}
	//end of body


}