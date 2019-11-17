#include <iostream>
#include <stdio.h>

using namespace std;

const int INF = 2000000000;

int n, m, k;
int a[300][300];
int t[1200][1200];

void makeY(int vx, int vy, int txl, int txr, int tyl, int tyr)
{
    if (tyl == tyr)
    {
        if (txl == txr)
            t[vx][vy] = a[txl][tyl];
        else
            t[vx][vy] = min(t[vx * 2][vy], t[vx * 2 + 1][vy]);
    }
    else
    {
        int tm = (tyl + tyr) / 2;
        int tovyl = vy * 2, tovyr = vy * 2 + 1;
        makeY(vx, tovyl, txl, txr, tyl, tm);
        makeY(vx, tovyr, txl, txr, tm + 1, tyr);
        t[vx][vy] = min(t[vx][tovyl], t[vx][tovyr]);
    }
}

void makeX(int vx, int txl, int txr)
{
    if (txl != txr)
    {
        int tm = (txl + txr) / 2;
        makeX(vx * 2, txl, tm);
        makeX(vx * 2 + 1, tm + 1, txr);
    }
    makeY(vx, 1, txl, txr, 0, m - 1);
}

int getY(int vx, int vy, int tyl, int tyr, int ly, int ry)
{
    if (tyl == ly && tyr == ry)
        return t[vx][vy];
    int tm = (tyl + tyr) / 2;
    if (ry <= tm)
        return getY(vx, vy * 2, tyl, tm, ly, ry);
    if (ly >= tm + 1)
        return getY(vx, vy * 2 + 1, tm + 1, tyr, ly, ry);
    return min(getY(vx, vy * 2, tyl, tm, ly, tm),
               getY(vx, vy * 2 + 1, tm + 1, tyr, tm + 1, ry));
}

int getX(int vx, int txl, int txr, int lx, int rx, int ly, int ry)
{
    if (txl == lx && txr == rx)
        return getY(vx, 1, 0, m - 1, ly, ry);
    int tm = (txl + txr) / 2;
    if (rx <= tm)
        return getX(vx * 2, txl, tm, lx, rx, ly, ry);
    if (lx >= tm + 1)
        return getX(vx * 2 + 1, tm + 1, txr, lx, rx, ly, ry);
    return min(getX(vx * 2, txl, tm, lx, tm, ly, ry),
               getX(vx * 2 + 1, tm + 1, txr, tm + 1, rx, ly, ry));
}

int main()
{
    scanf("%i %i %i", &n, &m, &k);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%i", a[i] + j);
    makeX(1, 0, n - 1);
    for (int i = 0; i < k; ++i)
    {
        int lx, rx, ly, ry;
        scanf("%i %i %i %i", &lx, &ly, &rx, &ry);
        printf("%i\n", getX(1, 0, n - 1, lx - 1, rx - 1, ly - 1, ry - 1));
    }
    return 0;
}
