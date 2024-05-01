#include <bits/stdc++.h>

using namespace std;
const int SIZE = str.size() + 1;
const int BASE = 2017;
const int MOD = 1000000009;

void init_powers(long long *p, int base, int mod, int SIZE)
{
    p[0] = 1;
    for (int i = 1; i < SIZE; ++i)
    {
        p[i] = p[i - 1] * base % mod;
    }
}

// O(n)
void init_hash(const string &line, long long *h, int base, int mod)
{
    h[0] = 0;
    int n = line.size();
    for (int i = 1; i <= n; ++i)
    {
        h[i] = h[i - 1] * base % mod + line[i - 1];
    }
}
// const
long long get_hash(int l, int r, long long *h, long long *p, int mod)
{
    return (h[r] - h[l] * p[r - l] % mod + mod) % mod;
}

int main()
{
    string str;
    cin >> str;
    long long ahash[SIZE];
    long long powers[SIZE];
    init_powers(powers, BASE, MOD, SIZE);
    init_hash(str, ahash, BASE, MOD);
    int q;
    cin >> q;
    while (q--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (get_hash(a - 1, b, ahash, powers, MOD) == get_hash(c - 1, d, ahash, powers, MOD))
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
}
