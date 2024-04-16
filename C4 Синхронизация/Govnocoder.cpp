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
    long long count_collider_records;
    f >> count_collider_records;
    int record;
    vector <long long> collider_records(count_collider_records);
    for (int i = 0; i < count_collider_records; i++) {
        f >> record;
        collider_records[i] = record;
    }

    long long count_kolya_records;
    f >> count_kolya_records;
    vector <long long> kolya_records(count_kolya_records);
    for (long long i = 0; i < count_kolya_records; i++) {
        f >> record;
        kolya_records[i] = record;
    }
    long long difference = count_collider_records - count_kolya_records+1;
    for (int i = 0; i < difference ; i++) {
        //cout << "Оно не поломалось || Значение i: " << i << '\n';
        long long check = 0;
        long long consttime = collider_records[i];
        for (long long j = 0; j < count_kolya_records; j++) {
            //cout << "Оно не поломалось || Значение j: " << j << '\n';
            if (collider_records[i + j] == (kolya_records[j] + consttime)) {
                check += 1;
            }
        }
        //cout << "-----------------------------------------------------------" << '\n';
        if (check == count_kolya_records) {
            out << i + 1;
            break;
        }
    }
}
