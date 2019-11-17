#include <stdio.h>

using namespace std;

typedef int LongNum[30];
const int base = 1000000000;
LongNum C[101][101];

void sum(LongNum a, LongNum b)
{
    int ost = 0;
    for (int i = 0; i < 30; ++i)
    {
        int cur = a[i] + b[i] + ost;
        a[i] = cur % base;
        ost = cur / base;
    }
}

void mult(LongNum a, int b)
{
    int ost = 0;
    for (int i = 0; i < 30; ++i)
    {
        long long cur = a[i] * 1ll * b + ost;
        a[i] = cur % base;
        ost = cur / base;
    }
}

void mult(LongNum a, LongNum b)
{
    LongNum res = {0};
    int ost = 0;
    for (int i = 0; i < 30; ++i)
        for (int j = 0; i + j < 30; ++j)
        {
            long long cur = a[i] * 1ll * b[j] + res[i + j] +  ost;
            res[i + j] = cur % base;
            ost = cur / base;
        }
    for (int i = 0; i < 30; ++i)
        a[i] = res[i];
}

void dec(LongNum a, LongNum b)
{
    for (int i = 0; i < 30; ++i)
    {
        a[i] -= b[i];
        if (a[i] < 0)
        {
            a[i] += base;
            a[i + 1] -= 1;
        }
    }
}

void init(LongNum num, int v = 1)
{
    num[0] = v;
    for (int i = 1; i < 30; ++i)
        num[i] = 0;
}

void copyL(LongNum a, LongNum b)
{
    for (int i = 0; i < 30; ++i)
        a[i] = b[i];
}

void initC()
{
    for (int n = 0; n <= 100; ++n)
        init(C[n][0]);
    for (int n = 0; n <= 100; ++n)
        for (int k = 1; k <= 100; ++k)
            if (k > n)
                init(C[n][k], 0);
            else
            {
                copyL(C[n][k], C[n - 1][k]);
                sum(C[n][k], C[n - 1][k - 1]);
            }
}

int main()
{
    initC();
    LongNum a[101];
    LongNum fact;
    init(a[0]);
    init(fact);
    int n;
    scanf("%i", &n);
    for (int i = 1; i <= n; ++i)
    {
        mult(fact, i);
        copyL(a[i], fact);
        for (int k = 0; k < i; ++k)
        {
            LongNum temp;
            copyL(temp, C[i][k]);
            mult(temp, a[k]);
            dec(a[i], temp);
        }
    }
    int i = 29;
    while (i > 0 && a[n][i] == 0)
        --i;
    printf("%i", a[n][i--]);
    while (i >= 0)
        printf("%09i", a[n][i--]);
    return 0;
}
