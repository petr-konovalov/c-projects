#include <bits/stdc++.h>

using namespace std;

char field[1024][1024];

int sx, sy;
int fx, fy;

struct Point
{
    int x, y;
    Point(int x, int y): x(x), y(y){}
};

int st[1024][1024];
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
int n, m, k;

void bfs()
{
    queue<Point> q;
    q.push(Point(sx, sy));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            st[i][j] = -1;
    st[sx][sy] = 0;
    while (!q.empty())
    {
        int x = q.front().x;
        int y = q.front().y;
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int tx = x;
            int ty = y;
            for (int j = 0; j < k; ++j)
            {
                tx += dx[i];
                ty += dy[i];
                if (0 <= tx && tx < n && 0 <= ty && ty < m && st[tx][ty] == -1 && field[tx][ty] == '.')
                {
                    st[tx][ty] = st[x][y] + 1;
                    q.push(Point(tx, ty));
                }
                else
                    break;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m >> k;
    k = min(k, max(m, n) - 1);
    for (int i = 0; i < n; ++i)
        cin >> field[i];
    cin >> sx >> sy >> fx >> fy;
    --sx;
    --sy;
    --fx;
    --fy;
    bfs();
    cout << st[fx][fy];
    return 0;
}
