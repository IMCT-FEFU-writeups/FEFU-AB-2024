#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <set>
#include <vector>
using namespace std;

ifstream f("input.txt");
ofstream out("output.txt");

void numbers(string number, int number_lenght ,int number_max_lenght) {
	if (number_lenght < number_max_lenght) {
		string number1 = number + "0";
		string number2 = number + "1";
		number_lenght += 1;
		numbers(number1, number_lenght, number_max_lenght);
		numbers(number2, number_lenght, number_max_lenght);
	}
	else {
		out << number << '\n';
	}
}

int main() {
	ifstream f("input.txt");
	ofstream out("output.txt");
	short n;
	f >> n;;
	string number = "";
	numbers(number, 0, n);
}
