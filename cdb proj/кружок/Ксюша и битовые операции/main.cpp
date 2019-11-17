#include <bits/stdc++.h>

using namespace std;

#define MAXSIZE 1024*128

int t[MAXSIZE * 4 + 100];
int a[MAXSIZE + 1];

void build(int v, int tl, int tr, bool op)
{
    if (tl == tr)
        t[v] = a[tl];
    else
    {
        int m = (tl + tr) >> 1;
        build(v * 2, tl, m, !op);
        build(v * 2 + 1, m + 1, tr, !op);
        if (op)
            t[v] = t[v * 2] | t[v * 2 + 1];
        else
            t[v] = t[v * 2] ^ t[v * 2 + 1];
    }
}

void changeItem(int v, int id, int nVal, int tl, int tr, bool op)
{
    if (id == tl && id == tr)
        t[v] = nVal;
    else
    {
        int m = (tl + tr) >> 1;
        if (id <= m)
            changeItem(v * 2, id, nVal, tl, m, !op);
        else
            changeItem(v * 2 + 1, id, nVal, m + 1, tr, !op);
        if (op)
            t[v] = t[v * 2] | t[v * 2 + 1];
        else
            t[v] = t[v * 2] ^ t[v * 2 + 1];
    }
}

int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    int size = 1 << n;
    for (int i = 1; i <= size; ++i)
        scanf("%i", a + i);
    build(1, 1, size, (n & 1) == 1);
    for (int i = 0; i < m; ++i)
    {
        int id, nVal;
        scanf("%i %i", &id, &nVal);
        changeItem(1, id, nVal, 1, size, (n & 1) == 1);
        printf("%i\n", t[1]);
    }
    return 0;
}
