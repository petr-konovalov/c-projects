#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    const int INF = 1000000000;
    int d[300][300];
    int n, m;
    scanf("%i %i", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            d[i][j] = INF;
    for (int i = 0; i < n; ++i)
        d[i][i] = 0;
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        scanf("%i %i", &l, &r);
        --l;
        --r;
        d[l][r] = 0;
        d[r][l] = min(d[r][l], 1);
    }
    for (int a = 0; a < n; ++a)
        for (int b = 0; b < n; ++b)
            for (int c = 0; c < n; ++c)
                d[b][c] = min(d[b][c], d[b][a] + d[a][c]);
    int res = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (d[i][j] != INF && d[i][j] > res)
                res = d[i][j];
    printf("%i", res);
    return 0;
}
