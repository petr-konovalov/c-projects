#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

const int INF = 2000000000;

int n;
int len;
int a[100000];
int b[1000];

void calcBlock()
{
    for (int i = 0; i <= len; ++i)
        b[i] = INF;
    for (int i = 0; i < n; ++i)
    {
        int block = i / len;
        b[block] = min(b[block], a[i]);
    }
}

int getMin(int l, int r)
{
    int cl = l / len;
    int cr = r / len;
    int res = a[l];
    if (cl == cr)
    {
        for (int i = l; i <= r; ++i)
            res = min(res, a[i]);
    }
    else
    {
        for (int i = l, end = (cl + 1) * len - 1; i <= end; ++i)
            res = min(res, a[i]);
        for (int i = cl + 1, end = cr - 1; i <= end; ++i)
            res = min(res, b[i]);
        for (int i = cr * len; i <= r; ++i)
            res = min(res, a[i]);
    }
    return res;
}

int main()
{
    scanf("%i", &n);
    len = (int)sqrt(n + .0) + 1;
    for (int i = 0; i < n; ++i)
        scanf("%i", a + i);
    calcBlock();
    int m;
    scanf("%i", &m);
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        scanf("%i %i", &l, &r);
        printf("%i ", getMin(l - 1, r - 1));
    }
    return 0;
}
