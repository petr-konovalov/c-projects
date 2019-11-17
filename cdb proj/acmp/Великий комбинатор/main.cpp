#include <iostream>
#include <stdio.h>

using namespace std;

typedef int LongNum[30];
const int base = 1000000000;

void mult(LongNum num, int b)
{
    int ost = 0;
    for (int i = 0; i < 30; ++i)
    {
        long long cur = num[i] * 1ll * b + ost;
        num[i] = cur % base;
        ost = cur / base;
    }
}

void div(LongNum num, int b)
{
    long long cur = 0;
    for (int i = 29; i >= 0; --i)
    {
        cur = cur * base + num[i];
        num[i] = cur / b;
        cur %= b;
    }
}

void C(LongNum res, int m, int n)
{
    res[0] = 1;
    for (int i = 1; i < 30; ++i)
        res[i] = 0;
    for (int i = n - m + 1; i <= n; ++i)
        mult(res, i);
    for (int i = 1; i <= m; ++i)
        div(res, i);
}

int main()
{
    int x, k;
    LongNum res;
    scanf("%i%i", &x, &k);
    x /= 5;
    C(res, x, x + k);
    int i = 29;
    while (i > 0 && res[i] == 0)
        --i;
    printf("%i", res[i--]);
    while (i >= 0)
        printf("%09i", res[i--]);
    return 0;
}
