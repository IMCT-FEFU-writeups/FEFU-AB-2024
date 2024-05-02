#include <fstream>
#include <string>

using namespace std;
ifstream cin("input.txt");
ofstream cout("output.txt");

void generateBinary(int N) {
    for (int i = 0; i < (1 << N); ++i) {
        string binary = "";
        for (int j = N - 1; j >= 0; --j) {
            if (i & (1 << j)) {
                binary += '1';
            } else {
                binary += '0';
            }
        }
        cout << binary << endl;
    }
}

int main() {
    int N;
    cin >> N;
    generateBinary(N);
    return 0;
}
