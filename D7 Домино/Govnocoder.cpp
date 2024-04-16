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

bool sequence_check(string sequence) {
	short sequence_size = sequence.size();
	short true_check = 0;
	for (int i = 0; i < sequence_size; i+=2) {
		if (sequence[i + 1] == sequence[i + 2]) {
			true_check += 1;
		}
	}
	if (true_check == (sequence_size / 2) - 1) {
		return true;
	}
	else {
		return false;
	}
}

void permute(vector <string> dictionary, short l, short r , string sequence, short sequence_size) {
	if (l == r) {
		if (sequence_check(sequence) == true) {
			string domino_sequence = "";
			for (int i = 0; i < r - 2; i += 2) {
				domino_sequence += sequence[i];
				domino_sequence += sequence[i + 1];
				domino_sequence += '-';
			}
			domino_sequence += sequence[r - 2];
			domino_sequence += sequence[r - 1];
			out << domino_sequence;
			exit(0);
		}
	}
	else {
		for (int i = l; i < r; i++) {
			if (sequence_size > 2) {
				if (sequence[sequence_size - 2] != sequence[sequence_size - 3]) {
					break;
				}
			}
			if (i % 2 == 0) {
				swap(dictionary[i], dictionary[l]);
				swap(dictionary[i + 1], dictionary[l + 1]);
				permute(dictionary, l + 2, r, sequence + dictionary[l], sequence_size + 2);
				permute(dictionary, l + 2, r, sequence + dictionary[l + 1], sequence_size + 2);
				swap(dictionary[i], dictionary[l]);
				swap(dictionary[i + 1], dictionary[l + 1]);
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	string dominos;
	f >> dominos;
	short dominos_size = dominos.size();
	short dominos_count = dominos_size;
	vector <string> dictionary(dominos_count);
	string domino1 = "";
	string domino2 = "";
	for (int i = 0; i < dominos_size; i+=2) {
		domino1 += dominos[i];
		domino1 += dominos[i + 1];
		domino2 += dominos[i + 1];
		domino2 += dominos[i];
		dictionary[i] = domino1;
		dictionary[i + 1] = domino2;
		domino1 = "";
		domino2 = "";
	}
	permute(dictionary, 0, dominos_count, "", 0);
	out << "NO";
}
