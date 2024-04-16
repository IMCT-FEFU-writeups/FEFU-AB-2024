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

vector <string> permutation;

void permute(string a, int l, int r)
{
	if (l == r) {
		if (a[0] != '0') {
			permutation.push_back(a);
		}
	}
	else
	{
		for (int i = l; i <= r; i++)
		{
			swap(a[l], a[i]);
			permute(a, l + 1, r);
			swap(a[l], a[i]);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream f("input.txt");
	ofstream out("output.txt");
	long long a, b, c;
	f >> a >> b >> c;
	string str_a = to_string(a);
	string str_b = to_string(b);
	short number_a_size = str_a.size();
	short number_b_size = str_b.size();
	short flag = 1;

	if (number_a_size >= number_b_size) {
		vector <short> dictionary_b(10);
		for (char digit : str_b) {
			dictionary_b[digit - '0'] += 1;
		}
		permute(str_a, 0, number_a_size - 1);
		for (string number : permutation) {
			long long nessecary_number = c - stoi(number);
			vector <short> dictionary_number(10);
			string str_nessecary_number = to_string(nessecary_number);
			if (str_nessecary_number[0] != '-') {
				for (char digit : str_nessecary_number) {
					dictionary_number[digit - '0'] += 1;
				}
				if (dictionary_number == dictionary_b) {
					out << "YES" << '\n' << number << ' ' << nessecary_number;
					flag = 0;
					break;
				}
			}
		}
	}
	else {
		vector <short> dictionary_a(10);
		for (char digit : str_a) {
			dictionary_a[digit - '0'] += 1;
		}
		permute(str_b, 0, number_b_size - 1);
		for (string number : permutation) {
			long long nessecary_number = c - stoi(number);
			vector <short> dictionary_number(10);
			string str_nessecary_number = to_string(nessecary_number);
			if (str_nessecary_number[0] != '-') {
				for (char digit : str_nessecary_number) {
					dictionary_number[digit - '0'] += 1;
				}
				if (dictionary_number == dictionary_a) {
					out << "YES" << '\n' << nessecary_number << ' ' << number;
					flag = 0;
					break;
				}
			}
		}
	}
	if (flag == 1) {
		out << "NO";
	}
}
