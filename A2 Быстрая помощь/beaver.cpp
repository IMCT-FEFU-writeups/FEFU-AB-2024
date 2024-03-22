#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void bubble_sort(int *arr, int n) {
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++) {
    swapped = false;
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }

    if (swapped == false)
      break;
  }
}

int main() {
  ifstream fin("input.txt");
  ofstream fout("output.txt");
  int n, l, answ = 0;
  fin >> n >> l;
  int speeds[n];

  for (int i = 0; i < n; i++) {
    int a;
    fin >> a;
    speeds[i] = a;
  }
  bubble_sort(speeds, n);

  for (int i = 0; i < n; i++) {
    if (speeds[i] <= answ) {
      answ += l;
    } else {
      answ = speeds[i] + l;
    }
  }

  fout << answ;
  return 0;
}
