#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

int g[128][128];
int state[128][128];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int dfs()
{
    queue<pair<int, int> > q;
    q.push(make_pair(1, 1));
    state[1][1] = 1;
    while (!q.empty())
    {
        int cx = q.front().first, cy = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int tx = cx + dx[i], ty = cy + dy[i];
            while (g[tx][ty] == 0)
                tx += dx[i], ty += dy[i];
            if (g[tx][ty] == 2)
                return state[cx][cy];
            tx -= dx[i], ty -= dy[i];
            if (!state[tx][ty])
                state[tx][ty] = state[cx][cy] + 1, q.push(make_pair(tx, ty));
        }
    }
    return -1;
}

int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%i", &g[i][j]);
    for (int i = 0; i <= n + 1; ++i)
        g[i][0] = g[i][m + 1] = 1;
    for (int j = 0; j <= m + 1; ++j)
        g[0][j] = g[n + 1][j] = 1;
    printf("%i\n", dfs());
    return 0;
}
