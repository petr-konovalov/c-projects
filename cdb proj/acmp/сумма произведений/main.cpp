#include <iostream>
#include <stdio.h>

using namespace std;

const int base = 1000000000;
typedef int lnum[400];

void printLnum(lnum a)
{
    int n = 399;
    while (a[n] == 0 && n > 0)
        --n;
    if (n == 0 && a[n] == 0)
        printf("0");
    else
    {
        printf("%i", a[n]);
        for (int i = n - 1; i >= 0; --i)
            printf("%09i", a[i]);
    }
}

void multLnum(lnum a, lnum b)
{
    lnum r = {0};
    long long curr = 0;
    int ost = 0;
    for (int i = 0; i < 200; ++i)
        for (int j = 0; j < 200; ++j)
        {
            curr = r[i + j] + a[i] * 1ll * b[j] + ost;
            r[i + j] = curr % base;
            ost = curr / base;
        }
    for (int i = 0; i < 400; ++i)
        a[i] = r[i];
}

void binPow(lnum a, int deg)
{
    lnum r = {0};
    r[0] = 1;
    while (deg)
    {
        if (deg & 1)
            multLnum(r, a);
        multLnum(a, a);
        deg >>= 1;
    }
    for (int i = 0; i < 400; ++i)
        a[i] = r[i];
}

int main()
{
    lnum a = {45};
    int n;
    cin >> n;
    binPow(a, n);
    printLnum(a);
    return 0;
}
