#include <iostream>
#include <queue>
#include <stdio.h>

using namespace std;

char g[64][64][64];
int state[64][64][64];

int sx, sy, sz, fx, fy, fz;
const int dx[5] = {0, 0, 0 ,0, 1};
const int dy[5] = {1, 0, -1, 0, 0};
const int dz[5] = {0, 1, 0, -1, 0};

int dfs()
{
    queue<pair<int, pair<int, int> > > q;
    q.push(make_pair(sx, make_pair(sy, sz)));
    state[sx][sy][sz] = 1;
    while (!q.empty())
    {
        int cx = q.front().first;
        int cy = q.front().second.first;
        int cz = q.front().second.second;
        q.pop();
        if (cx == fx && cy == fy && cz == fz)
            return (state[cx][cy][cz] - 1) * 5;
        for (int i = 0; i < 5; ++i)
        {
            int tx = cx + dx[i], ty = cy + dy[i], tz = cz + dz[i];
            if (g[tx][ty][tz] != 'o' && !state[tx][ty][tz])
            {
                state[tx][ty][tz] = state[cx][cy][cz] + 1;
                q.push(make_pair(tx, make_pair(ty, tz)));
            }
        }
    }
    return -1;
}

int main()
{
    int h, m, n;
    scanf("%i %i %i", &h, &m, &n);
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%s", g[i][j] + 1);
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= n; ++k)
                if (g[i][j][k] == '1')
                    sx = i, sy = j, sz = k;
                else if (g[i][j][k] == '2')
                    fx = i, fy = j, fz = k;
    for (int i = 0; i <= h + 1; ++i)
        for (int j = 0; j <= m + 1; ++j)
            g[i][j][0] = g[i][j][n + 1] = 'o';
    for (int i = 0; i <= h + 1; ++i)
        for (int k = 0; k <= n + 1; ++k)
            g[i][0][k] = g[i][m + 1][k] = 'o';
    for (int j = 0; j <= m + 1; ++j)
        for (int k = 0; k <= n + 1; ++k)
            g[0][j][k] = g[h + 1][j][k] = 'o';
    printf("%i\n", dfs());
    return 0;
}
