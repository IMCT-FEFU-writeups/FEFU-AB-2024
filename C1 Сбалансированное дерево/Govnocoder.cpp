#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <set>
using namespace std;
int main() {
	ifstream f("input.txt");
	ofstream out("output.txt");
	set <long long> numbers;
	long long number;
	f >> number;
	while (number != 0) {
		if (number > 0) {
			numbers.insert(number);
		}
		if (number < 0) {
			numbers.erase(-number);
		}
		f >> number;
	}
	for (auto const number : numbers) {
		out << number << ' ';
	}
}
