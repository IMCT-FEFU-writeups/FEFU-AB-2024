#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>

using namespace std;

ifstream f("input.txt");
ofstream out("output.txt");

set <string> permutations;

void check_ip(string ip) {
	vector <string> ip_numbers;
	string number = "";
	short count_true_check = 0;
	for (char digit : ip) {
		if (digit != '.') {
			number += digit;
		}
		else {
			if (number.size() >= 1) {
				ip_numbers.push_back(number);
				number = "";
			}
		}
	}
	if (!number.empty()) {
		ip_numbers.push_back(number);
	}
	for (string number : ip_numbers) {
		//cout << number << ' ';
		if ((stoi(number) < 256) and ((number.size() > 1 and number[0] != '0') or (number.size() == 1))) {
			count_true_check += 1;
		}
	}
	//cout << '\n' << ip << '\n';
	if (count_true_check == 4) {
		permutations.insert(ip);
	}
}

void permute(vector <string> dictionary, short l, short r, string ip) {
	if (l == r) {
		check_ip(ip);
	}
	else {
		for (int i = l; i < r; i++) {
			swap(dictionary[i], dictionary[l]);
			permute(dictionary, l + 1, r, ip + dictionary[l]);
			swap(dictionary[i], dictionary[l]);
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	vector <string> dictionary(4);
	string ip_char;
	for (int i = 0; i < 4; i++) {
		f >> ip_char;
		dictionary[i] = ip_char;
	}
	permute(dictionary, 0, 4, "");
	for (auto const ip: permutations) {
		out << ip << '\n';
	}
}
