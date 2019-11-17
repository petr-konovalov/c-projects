#include <iostream>
#include <stdio.h>

using namespace std;

const int p[2] = {2, 3};

void getsq(int n, int &s, int &q)
{
    s = 0;
    q = n;
    while ((q & 1) == 0)
    {
        ++s;
        q >>= 1;
    }
}

int powMod(int a, int deg, int mod)
{
    int res = 1;
    while (deg)
    {
        if (deg & 1)
            res = res * 1ll * a % mod;
        a = a * 1ll * a % mod;
        deg >>= 1;
    }
    return res;
}

bool isPrime(int n)
{
    if (n < 2)
        return false;
    int n_1 = n - 1;
    int s, q;
    getsq(n_1, s, q);
    for (int i = 0; i < 2; ++i)
    {
        if (n == p[i])
            return true;
        if (n % p[i] == 0)
            return false;
        if (powMod(p[i], n_1, n) != 1)
            return false;
        int degn = powMod(p[i], q, n);
        if (degn != 1 && degn != n_1)
        {
            for (int j = 1; j < s && degn != n_1; ++j)
                degn = degn * 1ll * degn % n;
            if (degn != n_1)
                return false;
        }
    }
    return true;
}

int main()
{
    int m, n;
    bool b = true;
    scanf("%i %i", &m, &n);
    for (int i = m; i <= n; ++i)
        if (isPrime(i))
        {
            printf("%i\n", i);
            b = false;
        }
    if (b)
        printf("Absent\n");
    return 0;
}
