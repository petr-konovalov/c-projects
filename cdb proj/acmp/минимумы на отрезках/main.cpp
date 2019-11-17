#include <iostream>
#include <stdio.h>

using namespace std;

const int INF = 1000 * 1000 * 1000;

int a[100000];
int t[400010];
int n;

void makeTree(int v, int tl, int tr)
{
    if (tl == tr)
        t[v] = a[tl];
    else
    {
        int tm = (tl + tr) / 2;
        makeTree(v * 2, tl, tm);
        makeTree(v * 2 + 1, tm + 1, tr);
        t[v] = min(t[v * 2], t[v * 2 + 1]);
    }
}

int getMin(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return INF;
    if (tl == l && tr == r)
        return t[v];
    int tm = (tl + tr) / 2;
    return min(getMin(v * 2, tl, tm, l, min(tm, r)), getMin(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r));
}

int main()
{
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i", a + i);
    makeTree(1, 0, n - 1);
    int m;
    scanf("%i", &m);
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        scanf("%i %i", &l, &r);
        printf("%i ", getMin(1, 0, n - 1, l - 1, r - 1));
    }
    return 0;
}
