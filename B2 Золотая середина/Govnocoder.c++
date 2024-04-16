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
#include <stack>  
#include <cmath> 
#include <ctime>
#include <set>
#include <iterator> 

using namespace std;

ifstream f("input.txt");
ofstream out("output.txt");


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    multiset <int> numbers;
    int numbers_count;
    f >> numbers_count;
    int number;
    f >> number;
    numbers.insert(number);
    auto iter = numbers.begin();
    out << *iter << ' ';
    for (int i = 1; i < numbers_count; i++) {
        f >> number;
        numbers.insert(number);
        if (number < *iter) {
            iter--;
        }
        if (i % 2 == 0) {
            iter++;
        }
        out << *iter << ' ';
    }
    //cout << '\n';
    //for (auto const number : numbers) {
    //    cout << number << ' ';
    //}
}
