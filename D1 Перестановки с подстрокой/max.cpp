#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int f(int n)
{
    unsigned long long result = 1;

    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

bool isValidInput(const string &S, const string &P)
{
    // Проверяем, что длина строки P не превышает длину строки S
    if (P.size() > S.size())
    {
        return false;
    }

    // Проверяем, что все буквы в строке P различны
    vector<short> a(128);
    for (char c : P)
    {
        a[c]++;
        if (a[c] > 1)
        {
            return false;
        }
    }

    // Проверяем, что все буквы в строке P содержатся в строке S
    for (char c : P)
    {
        if (S.find(c) == string::npos)
        {
            return false;
        }
    }

    return true;
}

int countSubstringWords(const string &S, const string &P)
{
    int result = 0;
    int N = S.size();
    int M = P.size();

    for (int i = 0; i <= N - M; i++)
    {
        result += f(N - M) / f(N - M - i) * (i + 1);
    }
    return result;
}

int main()
{
    string S, P;
    fin >> S >> P;
    // Проверяем валидность входных данных
    if (!isValidInput(S, P))
    {
        fout << 0;
        return 0;
    }

    // Подсчитываем количество слов, содержащих подстроку P, и выводим результат
    int count = countSubstringWords(S, P);
    fout << count << endl;

    return 0;
}
