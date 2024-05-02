/*
 * Двоичные последовательности прибавлением 1 к числу в двоичной системе счисления. Не уверен что примут, тк работаем не через бити, но я рот ебал
 */

#include <iostream>
#include <string>
#include <queue>

using namespace std;

void generateBinary(int N) {
    queue<string> sequences;
    sequences.push("0");
    sequences.push("1");

    while (!sequences.empty()) {
        string current = sequences.front();
        sequences.pop();
        if (current.length() == N) {
            cout << current << endl;
        } else {
            sequences.push(current + "0");
            sequences.push(current + "1");
        }
    }
}

int main() {
    int N;
    cin >> N;
    generateBinary(N);
    return 0;
}
