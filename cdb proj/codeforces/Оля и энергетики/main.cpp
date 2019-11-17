#include <bits/stdc++.h>

using namespace std;

char field[1024][1024];
int n, m, k;
int x1, y1, x2, y2;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
int st[1024][1024];
bool used[1024][1024];

void bfs()
{
    queue<pair<int, int> > q;
    q.push(make_pair(x1, y1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            st[i][j] = -1;
    st[x1][y1] = 0;
    while (!q.empty() && st[x2][y2] == -1)
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int tx = x;
            int ty = y;
            for (int j = 0; j < k; ++j)
            {
                tx += dx[i];
                ty += dy[i];
                if ((st[tx][ty] == -1 || st[x][y] + 1 <= st[tx][ty]) && field[tx][ty] == '.')
                {
                    if (!used[tx][ty])
                    {
                        q.push(make_pair(tx, ty));
                        used[tx][ty] = true;
                    }
                    st[tx][ty] = st[x][y] + 1;
                }
                else
                    break;
            }
        }
    }
}

int main()
{
    scanf("%i %i %i", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%s", field[i] + 1);
    for (int i = 0; i <= n; ++i)
    {
        field[i][0] = '#';
        field[i][m + 1] = '#';
    }
    for (int i = 0; i <= m; ++i)
    {
        field[0][i] = '#';
        field[n + 1][i] = '#';
    }
    scanf("%i %i %i %i", &x1, &y1, &x2, &y2);
    bfs();
    printf("%i", st[x2][y2]);
    return 0;
}
