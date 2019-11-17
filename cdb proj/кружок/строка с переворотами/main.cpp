#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

int binPow(int a, int b)
{
    int res = 1;

    while (b)
    {
        if (b & 1)
            res = (res * 1ll * a) % MOD;
        a = (a * 1ll * a) % MOD;
        b >>= 1;
    }

    return res;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    gcd(b, a % b);
}

int main()
{
    int n;
    int res = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        res = (res + binPow(2, gcd(i, n))) % MOD;
    if (n & 1)
        res = (res + (n * 1ll * binPow(2, (n >> 1) + 1)) % MOD) % MOD;
    else
        res = (res + (n * 3ll * binPow(2, (n >> 1) - 1)) % MOD) % MOD;
    res = (res * 1ll * binPow(2 * n, MOD - 2)) % MOD;
    cout << res;
    return 0;
}
