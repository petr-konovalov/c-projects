#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;

int sum[1001][1001];
int sdc[1001][1001];
int t[1001][4005];
int m, n, a, b, c, d;

void buildY(int x, int vy, int yl, int yr)
{
    if (yl == yr)
        t[x][vy] = sdc[x][yl];
    else
    {
        int mid = (yl + yr) / 2;
        buildY(x, vy * 2, yl, mid);
        buildY(x, vy * 2 + 1, mid + 1, yr);
        t[x][vy] = min(t[x][vy * 2], t[x][vy * 2 + 1]);
    }
}

void buildX()
{
    int ey = m - c + 1;
    for (int x = 1, ex = n - d + 1; x <= ex; ++x)
        buildY(x, 1, 1, ey);
}

const int INF = 1000000000;

int getMinY(int x, int vy, int pyl, int pyr, int yl, int yr)
{
    if (pyl > pyr)
        return INF;
    if (yl == pyl && yr == pyr)
        return t[x][vy];
    int mid = (yl + yr) / 2;
    return min(getMinY(x, vy * 2, pyl, min(mid, pyr), yl, mid),
               getMinY(x, vy * 2 + 1, max(mid + 1, pyl), pyr, mid + 1, yr));
}

deque<int> q;

void add(int value)
{
    while (!q.empty() && value < q.back())
        q.pop_back();
    q.push_back(value);
}

int get(int value)
{
    int res = q.front();
    if (!q.empty() && q.front() == value)
        q.pop_front();
    return res;
}

int getMinX(int pxl, int pxr, int pyl, int pyr)
{
    int ey = m - c + 1;
    if (q.empty())
    {
        for (int x = pxl; x <= pxr; ++x)
            add(getMinY(x, 1, pyl, pyr, 1, ey));
    }
    else
        add(getMinY(pxr, 1, pyl, pyr, 1, ey));
    return get(getMinY(pxl, 1, pyl, pyr, 1, ey));
}

int main()
{
    scanf("%i %i %i %i %i %i", &m, &n, &a, &b, &c, &d);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int cur;
            scanf("%i", &cur);
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + cur - sum[i - 1][j - 1];
        }
    for (int i = 1, ei = n - d + 1; i <= ei; ++i)
        for (int j = 1, ej = m - c + 1; j <= ej; ++j)
        {
            int ti = i + d - 1, tj = j + c - 1;
            sdc[i][j] = sum[ti][tj] + sum[i - 1][j - 1] - sum[ti][j - 1] - sum[i - 1][tj];
        }
    buildX();
    int res = 0;
    for (int j = 1, ej = m - a + 1; j <= ej; ++j)
    {
        q.clear();
        for (int i = 1, ei = n - b + 1; i <= ei; ++i)
        {
            int ti = i + b - 1, tj = j + a - 1;
            int cur = sum[ti][tj] + sum[i - 1][j - 1] -
                      sum[ti][j - 1] - sum[i - 1][tj] -
                      getMinX(i + 1, ti - d, j + 1, tj - c);
            if (cur > res)
                res = cur;
        }
    }
    printf("%i\n", res);
    return 0;
}
