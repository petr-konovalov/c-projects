#include <iostream>
#include <stdio.h>

using namespace std;

typedef int longNum[20];
const int base = 1000000000;

void multLong(longNum num, long long b)
{
    int ost = 0;
    int b1 = b % base;
    int b2 = b / base;
    longNum r;
    r[0] = 0;
    for (int i = 0; i < 19; ++i)
    {
        long long cur = b2 * 1ll * num[i] + ost;
        r[i + 1] = cur % base;
        ost = cur / base;
    }
    for (int i = 0; i < 20; ++i)
    {
        long long cur = b1 * 1ll * num[i] + ost;
        num[i] = cur % base;
        ost = cur / base;
    }
    for (int i = 0; i < 20; ++i)
    {
        long long cur = r[i] + 0ll + num[i] + ost;
        num[i] = cur % base;
        ost = cur / base;
    }
}

int main()
{
    long long a[41][41];
    long long b[41][41];
    for (int i = 0; i < 41; ++i)
    {
        a[i][0] = 1;
        a[0][i] = 1;
        b[i][0] = 1;
        b[0][i] = 1;
    }
    for (int i = 1; i < 41; ++i)
        for (int j = 1; j < 41; ++j)
        {
            if (i < 25 && j < 25 || i == j)
                a[i][j] = a[i - 1][j] + a[i][j - 1];
            else
            {
                if (i > j)
                    a[i][j] = a[i - 1][j];
                else
                    a[i][j] = a[i][j - 1];
            }
            if (i < 15 && j < 15 || i == j)
                b[i][j] = b[i - 1][j] + b[i][j - 1];
            else
            {
                if (i > j)
                    b[i][j] = b[i - 1][j];
                else
                    b[i][j] = b[i][j - 1];
            }
        }
    int n;
    scanf("%i", &n);
    longNum res = {0};
    res[0] = 1;
    int s, t;
    for (int i = 1; i < n; ++i)
    {
        scanf("%i:%i", &s, &t);
        multLong(res, a[s][t]);
    }
    scanf("%i:%i", &s, &t);
    if (n == 5)
        multLong(res, b[s][t]);
    else
        multLong(res, a[s][t]);
    int i = 19;
    while (i > 0 && res[i] == 0)
        --i;
    printf("%i", res[i--]);
    while (i >= 0)
        printf("%09i", res[i--]);
    return 0;
}
