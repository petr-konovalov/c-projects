#include <iostream>
#include <queue>
#include <stdio.h>

using namespace std;

int state[502][502];
char g[502][502];

int dfs(int sx, int sy, int fx, int fy)
{
    queue<pair<int, int> > q;
    q.push(make_pair(sx, sy));
    state[sx][sy] = 1;
    while (!q.empty())
    {
        int cx = q.front().first, cy = q.front().second, k = state[cx][cy];
        q.pop();
        if (fx == cx && fy == cy)
            return k - 1;
        for (int x = cx + 1; g[x][cy] != 'P' && !state[x][cy]; ++x)
            q.push(make_pair(x, cy)), state[x][cy] = k + 1;
        for (int x = cx - 1; g[x][cy] != 'P' && !state[x][cy]; --x)
            q.push(make_pair(x, cy)), state[x][cy] = k + 1;
        for (int y = cy + 1; g[cx][y] != 'P' && !state[cx][y]; ++y)
            q.push(make_pair(cx, y)), state[cx][y] = k + 1;
        for (int y = cy - 1; g[cx][y] != 'P' && !state[cx][y]; --y)
            q.push(make_pair(cx, y)), state[cx][y] = k + 1;
    }
    return -1;
}

int main()
{
    int n, m;
    int sx, sy, fx, fy;
    scanf("%i %i", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", g[i] + 1);
        for (int j = 1; j <= m; ++j)
            if (g[i][j] == 'F')
                fx = i, fy = j;
            else if (g[i][j] == 'S')
                sx = i, sy = j;
    }
    for (int i = 0; i <= n + 1; ++i)
        g[i][0] = g[i][m + 1] = 'P';
    for (int i = 0; i <= m + 1; ++i)
        g[0][i] = g[n + 1][i] = 'P';
    printf("%i\n", dfs(sx, sy, fx, fy));
    return 0;
}
